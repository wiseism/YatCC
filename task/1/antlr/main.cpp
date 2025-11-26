#include "SYsULexer.h" // 确保这里的头文件名与您生成的词法分析器匹配
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>
// 映射定义，将ANTLR的tokenTypeName映射到clang的格式
std::unordered_map<std::string, std::string> tokenTypeMapping = {
    { "Int", "int" },
    { "Identifier", "identifier" },
    { "LeftParen", "l_paren" },
    { "RightParen", "r_paren" },
    { "LeftBrace", "l_brace" },
    { "RightBrace", "r_brace" },
    { "LeftBracket", "l_square" },
    { "RightBracket", "r_square" },
    { "Constant", "numeric_constant" },
    { "Return", "return" },
    { "Semi", "semi" },
    { "EOF", "eof" },
    { "Equal", "equal" },
    { "Plus", "plus" },
    { "Minus", "minus" },
    { "Star", "star" },
    { "Div", "div" },
    { "Mod", "mod" },
    { "Comma", "comma" },
    { "EqualEqual", "eq" },
    { "NotEqual", "neq" },
    { "Less", "lt" },
    { "Greater", "gt" },
    { "LessEqual", "le" },
    { "GreaterEqual", "ge" },
    { "AndAnd", "andand" },
    { "OrOr", "oror" },
    { "Not", "not" }
};

struct LocationInfo {
    std::string filename;
    int line;
};

LocationInfo currentLocation = {"unknown", 0};

// 映射到 clang 风格名字
static const std::unordered_map<std::string, std::string> mapping = {
  {"Int", "int"}, {"Return", "return"},{"Const", "const"},{"Greater", "greater"},
  {"If", "if"},
  {"Minus", "minus"},
  {"Pipepipe", "pipepipe"},
  {"Else", "else"},
  {"Star", "star"},
  {"Void", "void"},
  {"AmpAmp", "ampamp"},
  {"Equalequal", "equalequal"},
  {"LeftParen", "l_paren"}, {"RightParen", "r_paren"},
  {"LeftBrace", "l_brace"}, {"RightBrace", "r_brace"},
  {"LeftBracket", "l_square"}, {"RightBracket", "r_square"},
  {"Constant", "numeric_constant"}, {"Identifier", "identifier"},
  {"Semi", "semi"}, {"Plus", "plus"}, {"Comma", "comma"}, {"Equal", "equal"},
  {"EOF", "eof"}
};

void print_token(const antlr4::Token* token,
                 const antlr4::CommonTokenStream& tokens,
                 std::ofstream& outFile,
                 const antlr4::Lexer& lexer)
{
    static int lastLine = -1;
    static bool afterNewline = true;
    static bool hasWhiteSpace = false;

    auto tokenType = token->getType();
    auto line = token->getLine();
    auto col = token->getCharPositionInLine();
    auto text = token->getText();

    if (tokenType==SYsULexer::LineAfterPreprocessing) {
      if (currentLocation.filename.empty()) {

      }
      std::regex pattern(R"(#\s*(\d+)\s+\"([^\"]+)\".*)");
      std::smatch matches;
      if (std::regex_match(text, matches, pattern)) {
        std::string filename = matches[2].str();
        if (filename.find('<') == std::string::npos) {
          currentLocation.filename = filename;
        }
      }
      currentLocation.line++;
      return;
    }
    if (tokenType==SYsULexer::Whitespace) {
      hasWhiteSpace = true;
      return;
    }
    // 更新状态
    if (line != lastLine) {
        afterNewline = true;
        lastLine = line;
    }

  std::string tokenTypeName = std::string(lexer.getVocabulary().getSymbolicName(tokenType));
    if (tokenTypeName.empty()) tokenTypeName = "<UNKNOWN>";

  if (tokenTypeName.find("qual") != std::string::npos) {
    std::cout << tokenTypeName << std::endl;
  }
    auto it = mapping.find(tokenTypeName);
    if (it != mapping.end()) tokenTypeName = it->second;

    // 输出 token 名字和文本
    if (tokenType != antlr4::Token::EOF) {
        outFile << tokenTypeName << " '" << text << "'	";
    } else {
        outFile << tokenTypeName << " ''	";
    }

    // 添加 [StartOfLine]
    if (afterNewline && tokenType != antlr4::Token::EOF) {
        outFile << " [StartOfLine]";
    }

    // 添加 [LeadingSpace]
    if (hasWhiteSpace) {
      outFile << " [LeadingSpace]";
      hasWhiteSpace = false;
    }
    outFile << "	Loc=<" << currentLocation.filename
          << ":" << line-currentLocation.line << ":" << (col + 1) << ">";

    outFile << std::endl;

    // 更新状态
    afterNewline = false;
    if (text.find('\n') != std::string::npos) {
        afterNewline = true;
    }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <input> <output>\n";
    return -1;
  }

  std::ifstream inFile(argv[1]);
  if (!inFile) {
    std::cout << "Error: unable to open input file: " << argv[1] << '\n';
    return -2;
  }

  std::ofstream outFile(argv[2]);
  if (!outFile) {
    std::cout << "Error: unable to open output file: " << argv[2] << '\n';
    return -3;
  }
  currentLocation.line = 0;
  antlr4::ANTLRInputStream input(inFile);
  SYsULexer lexer(&input);

  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();

  for (auto&& token : tokens.getTokens()) {
    print_token(token, tokens, outFile, lexer);
  }

  return 0;
}