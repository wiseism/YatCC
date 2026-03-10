#include "SYsULexer.h" // 确保这里的头文件名与您生成的词法分析器匹配
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>
#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <iostream>

class FileNode {
public:
    std::string filename;
    int startLine;
    int currentLine;
    int totalLines;  // 新增：该文件的总行数
    std::vector<std::shared_ptr<FileNode>> children;
    std::weak_ptr<FileNode> parent;

    FileNode(const std::string& name, int line, std::shared_ptr<FileNode> parentNode = nullptr)
        : filename(name), startLine(line), currentLine(line), totalLines(0), parent(parentNode) {}

    // 计算总行数（当前行号 - 起始行号 + 1）
    int calculateTotalLines() const {
        return currentLine - startLine + 1;
    }

    // 递归计算该节点及其所有子节点的总行数
    int calculateTotalLinesRecursive() const {
        int total = calculateTotalLines();
        for (const auto& child : children) {
            total += child->calculateTotalLinesRecursive();
        }
        return total;
    }
};

class PreprocTree {
private:
    std::shared_ptr<FileNode> root;
    std::shared_ptr<FileNode> currentNode;
    std::stack<std::shared_ptr<FileNode>> nodeStack;
    int globalLineCounter;  // 全局行号计数器

public:
    PreprocTree() : root(nullptr), currentNode(nullptr), globalLineCounter(0) {}

    void processLineDirective(int lineNum, const std::string& filename, int flags) {
        globalLineCounter++;

        if (flags == 1) {
            // 新文件开始
            auto newNode = std::make_shared<FileNode>(filename, lineNum, currentNode);
            if (currentNode) {
                currentNode->children.push_back(newNode);
                nodeStack.push(currentNode);
            } else {
                root = newNode;
            }
            currentNode = newNode;
        } else if (flags == 2) {
            // 返回原文件，计算结束文件的总行数
            if (currentNode) {
                currentNode->totalLines = currentNode->calculateTotalLines();
                std::cout << "文件 " << currentNode->filename
                          << " 总行数: " << currentNode->totalLines << std::endl;
            }

            if (!nodeStack.empty()) {
                currentNode = nodeStack.top();
                nodeStack.pop();
            }
        }

        if (currentNode) {
            currentNode->currentLine = lineNum;
        }
    }

    // 处理普通行（非预处理指令）
    void processNormalLine() {
        globalLineCounter++;
        if (currentNode) {
            currentNode->currentLine++;
        }
    }

    // 获取整个预处理文件的总行数
    int getTotalLines() const {
        return globalLineCounter;
    }

    // 获取特定文件的总行数
    int getFileTotalLines(const std::string& filename) const {
        auto node = findFileNode(root, filename);
        return node ? node->totalLines : 0;
    }

    // 打印详细的统计信息
    void printStatistics(std::shared_ptr<FileNode> node = nullptr, int depth = 0) {
        if (!node) node = root;
        if (!node) return;

        std::string indent(depth * 2, ' ');
        int fileLines = node->calculateTotalLines();
        int recursiveLines = node->calculateTotalLinesRecursive();

        std::cout << indent << node->filename
                  << " [起始行: " << node->startLine
                  << ", 当前行: " << node->currentLine
                  << ", 文件行数: " << fileLines
                  << ", 递归行数: " << recursiveLines << "]" << std::endl;

        for (const auto& child : node->children) {
            printStatistics(child, depth + 1);
        }
    }

private:
    std::shared_ptr<FileNode> findFileNode(std::shared_ptr<FileNode> node,
                                          const std::string& filename) const {
        if (!node) return nullptr;
        if (node->filename == filename) return node;

        for (const auto& child : node->children) {
            auto found = findFileNode(child, filename);
            if (found) return found;
        }

        return nullptr;
    }
};

// 映射定义，将ANTLR的tokenTypeName映射到clang的格式
std::unordered_map<std::string, std::string> tokenTypeMapping = {
    { "Int", "int" },
    { "LineComment", "comment" },
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
    { "AmpAmp", "andand" },
    { "Pipepipe", "oror" },
    { "Not", "not" }
};

struct LocationInfo {
    std::string filename;
    std::string sourceFileName;
    int lineOffset;
};

LocationInfo currentLocation = {"unknown", "unknown", 0};

// 映射到 clang 风格名字
static const std::unordered_map<std::string, std::string> mapping = {
  {"Int", "int"}, {"Return", "return"},{"Const", "const"},{"Greater", "greater"},
  {"If", "if"},
  {"LineComment", "comment"},
  {"Minus", "minus"},
  {"Pipepipe", "pipepipe"},
  {"Else", "else"},
  {"Star", "star"},
  {"Void", "void"},
  {"AmpAmp", "ampamp"},
  {"Div", "slash"},
  {"Mod", "percent"},
  {"EqualEqual", "equalequal"},
  { "Less", "less" },
  { "While", "while" },
  { "Break", "break" },
  { "Continue", "continue" },
  { "Not", "exclaim" },
  {"LeftParen", "l_paren"}, {"RightParen", "r_paren"},
  {"LeftBrace", "l_brace"}, {"RightBrace", "r_brace"},
  {"LeftBracket", "l_square"}, {"RightBracket", "r_square"},
  {"Constant", "numeric_constant"}, {"Identifier", "identifier"},
  {"Semi", "semi"}, {"Plus", "plus"}, {"Comma", "comma"},
  {"Equal", "equal"},
  { "NotEqual", "exclaimequal" },
{ "GreaterEqual", "greaterequal" },
{ "LessEqual", "lessequal" },
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

    if (tokenType==SYsULexer::LineDirective) {
      // 匹配 # 数字 "文件名" [数字] 格式
      std::regex pattern1(R"(#\s*(\d+)\s+\"([^\"]+)\"(\s+\d+)*)");
      // 匹配 # 数字 <文件名> [数字] 格式
      std::regex pattern2(R"(#\s*(\d+)\s+<([^>]+)>(\s+\d+)*)");
      // 匹配 # include "文件名" 格式
      std::regex pattern3(R"(#\s*include\s+\"([^\"]+)\")");
      // 匹配 # include <文件名> 格式
      std::regex pattern4(R"(#\s*include\s+<([^>]+)>)");
      
      std::smatch matches;
      std::string filename;
      int lineNum = 1;
      bool isInclude = false;
      
      if (std::regex_match(text, matches, pattern1)) {
        lineNum = std::stoi(matches[1].str());
        filename = matches[2].str();
      } else if (std::regex_match(text, matches, pattern2)) {
        lineNum = std::stoi(matches[1].str());
        filename = matches[2].str();
      } else if (std::regex_match(text, matches, pattern3)) {
        filename = matches[1].str();
        isInclude = true;
      } else if (std::regex_match(text, matches, pattern4)) {
        filename = matches[1].str();
        isInclude = true;
      }
      
      // 更新文件名
      if (!filename.empty()) {
        currentLocation.filename = filename;
        if (line == 1) {
          currentLocation.sourceFileName = filename;
        }
      }
      
      // 处理 include 指令
      if (isInclude) {
        return;
      }
      
      // 关键修复：记录 LineDirective 指令中的行号
      // 这个行号表示 LineDirective 之后的代码应该在原始文件的哪一行
      // 所以对于预处理文件的第 (line + 1) 行，对应的原始文件行号是 lineNum
      // 因此 lineOffset = lineNum - (line + 1)
      currentLocation.lineOffset = lineNum - line - 1;
      
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
    
    // 计算正确的行号 - 使用 lineOffset 来处理注释行被跳过的情况
    int resultStr = line + currentLocation.lineOffset;
    
    // 确保行号不为负数
    if (resultStr < 1) resultStr = 1;
    
    outFile << "	Loc=<" << currentLocation.filename
          << ":" << resultStr << ":" << (col + 1) << ">";

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
  currentLocation.lineOffset = 0;
  antlr4::ANTLRInputStream input(inFile);
  SYsULexer lexer(&input);

  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();

  for (auto&& token : tokens.getTokens()) {
    print_token(token, tokens, outFile, lexer);
  }

  return 0;
}