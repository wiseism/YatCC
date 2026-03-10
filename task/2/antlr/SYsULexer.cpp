#include "SYsULexer.hpp"
#include "SYsULexer.tokens.hpp"
#include <unordered_map>
#include <vector>

using antlr4::ParseCancellationException;
using std::make_pair;

namespace {

using namespace SYsULexerTokens;

static const std::unordered_map<std::string, size_t> kClangTokens{
  { "eof", antlr4::Token::EOF },
  { "int", kInt },
  { "identifier", kIdentifier },
  { "const", kConst },
  { "l_paren", kLeftParen },
  { "r_paren", kRightParen },
  { "return", kReturn },
  { "r_brace", kRightBrace },
  { "l_brace", kLeftBrace },
  { "numeric_constant", kConstant },
  { "semi", kSemi },
  { "equal", kEqual },
  { "plus", kPlus },
  { "minus", kMinus },
  { "comma", kComma },
  { "l_square", kLeftBracket },
  { "r_square", kRightBracket },
  { "star", kStar },
  { "slash", kDiv },
  { "percent", kMod },
  { "equalequal", kEqualEqual },
  { "exclaimequal", kNotEqual },
  { "less", kLess },
  { "greater", kGreater },
  { "lessequal", kLessEqual },
  { "greaterequal", kGreaterEqual },
  { "ampamp", kAmpAmp },
  { "pipepipe", kPipePipe },
  { "exclaim", kNot },
  { "if", kIf },
  { "else", kElse },
  { "while", kWhile },
  { "break", kBreak },
  { "continue", kContinue },
  { "void", kVoid }
};

} // namespace

SYsULexer::SYsULexer(antlr4::CharStream* input)
  : mInput(input)
  , mSource(make_pair(this, input))
  , mFactory(antlr4::CommonTokenFactory::DEFAULT.get())
  , mSourceName(input->getSourceName())
{
}

std::unique_ptr<antlr4::Token>
SYsULexer::nextToken()
{
  auto c = mInput->LA(1);
  if (c == antlr4::Token::EOF) {
    // 到达文件末尾，退出循环
    return common_token(antlr4::Token::EOF, mInput->index(), mInput->index());
  }

  auto start = mInput->index();
  std::string line;
  std::unique_ptr<antlr4::CommonToken> token;
  
  while (true) {
    mInput->consume();
    if (c == U'\n') {
      if (mInput->LA(1) == U'\r')
        mInput->consume();
      break;
    }
    if (c == U'\r') {
      if (mInput->LA(1) == U'\n')
        mInput->consume();
      break;
    }
    line.push_back(c);
    c = mInput->LA(1);
    if (c == antlr4::Token::EOF)
      return common_token(antlr4::Token::INVALID_TYPE, start, mInput->index());
  }
  auto stop = mInput->index();

  std::size_t typeEnd;
  ssize_t type;
  std::size_t textEnd;
  std::string text;
  size_t tokenLine = 0, tokenColumn = 0;
  std::string tokenSourceName;
  bool parseSuccess = false;

  // 提取类型段
  {
    decltype(kClangTokens)::const_iterator typeIter;
    typeEnd = line.find(' ');
    if (typeEnd == std::string::npos)
      goto FAIL;
    typeIter = kClangTokens.find(line.substr(0, typeEnd));
    if (typeIter == kClangTokens.end())
      goto FAIL;
    type = static_cast<ssize_t>(typeIter->second);
  }

  // 提取文本段
  {
    textEnd = line.find('\t', typeEnd + 1);
    if (textEnd == std::string::npos ||
        textEnd < typeEnd + 2 // 至少要有一对空引号 ''
    )
      goto FAIL;
    text = line.substr(typeEnd + 2, textEnd - typeEnd - 3);
    // 跳过连续的 tab 字符
    while (textEnd + 1 < line.length() && line[textEnd + 1] == '\t')
      textEnd++;
  }

  // 提取位置段
  {
    std::size_t locStart, locEnd, colStart, rowStart;

    locStart = line.find("Loc=<", textEnd + 1);
    if (locStart == std::string::npos)
      goto FAIL;
    locEnd = line.find(">", locStart);
    if (locEnd == std::string::npos)
      goto FAIL;
    
    // 从右向左查找冒号，避免文件路径中的冒号干扰
    // 格式: Loc=<filename:line:col>
    // 最后一个冒号是行号和列号之间的分隔符
    // 倒数第二个冒号是文件名和行号之间的分隔符
    // 注意：Windows 路径中可能有多个冒号（如 D:\path\to\file）
    // 所以需要从右向左查找，确保找到的是正确的冒号
    colStart = line.rfind(':', locEnd);
    if (colStart == std::string::npos)
      goto FAIL;
    
    // 从 colStart 向左查找倒数第二个冒号
    // 限制搜索范围到 locStart 之后，避免找到文件路径中的其他冒号
    rowStart = line.rfind(':', colStart - 1);
    if (rowStart == std::string::npos || rowStart < locStart)
      goto FAIL;

    tokenSourceName = line.substr(locStart + 5, rowStart - locStart - 5);
    tokenLine = std::stoul(line.substr(rowStart + 1, colStart - rowStart - 1));
    tokenColumn = std::stoul(line.substr(colStart + 1, locEnd - colStart - 1));
    parseSuccess = true;
  }

  // 解析成功
  // 如果 type 是 EOF，直接返回 EOF token
  if (type == antlr4::Token::EOF) {
    return common_token(antlr4::Token::EOF, mInput->index(), mInput->index(), "", tokenLine, tokenColumn);
  }
  token = common_token(type, mTokenIndex, mTokenIndex + text.length(), text, tokenLine, tokenColumn);
  mTokenIndex += text.length() + 1;
  // 更新成员变量以便后续调用
  mLine = tokenLine;
  mColumn = tokenColumn;
  mSourceName = tokenSourceName;
  return token;

FAIL: // 解析失败
  assert(false);
}

size_t
SYsULexer::getLine() const
{
  return mLine;
}

size_t
SYsULexer::getCharPositionInLine()
{
  return mColumn;
}

antlr4::CharStream*
SYsULexer::getInputStream()
{
  return mInput;
}

std::string
SYsULexer::getSourceName()
{
  return mSourceName;
}

antlr4::TokenFactory<antlr4::CommonToken>*
SYsULexer::getTokenFactory()
{
  return mFactory;
}
