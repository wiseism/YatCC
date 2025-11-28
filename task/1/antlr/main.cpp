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
    int oldLine;
    int skipLine;
};

LocationInfo currentLocation = {"unknown", 0, 1000, 0};

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
  {"Div", "slash"},
  {"Mod", "percent"},
  {"EqualEqual", "equalequal"},
  { "Less", "less" },
  { "While", "while" },
  { "Break", "break" },
  { "Continue", "continue" },
  { "Not", "exclaim" },
  { "NotEqual", "exclaimequal" },
  { "GreaterEqual", "greaterequal" },
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

    if (tokenType==SYsULexer::LineDirective) {
      if (currentLocation.filename.empty()) {

      }
      std::regex pattern(R"(#\s*(\d+)\s+\"([^\"]+)\"( \d)*)");
      std::smatch matches;
      if (std::regex_match(text, matches, pattern)) {
        // std::string s0 = matches[0].str();
        // std::string s1 = matches[1].str();
        // std::string s3 = matches[3].str();
        std::string filename = matches[2].str();
        if (filename.find('<') == std::string::npos) {
          currentLocation.filename = filename;
        }
      }
      currentLocation.line++;
      if (line>currentLocation.oldLine+1) {
        currentLocation.skipLine = currentLocation.skipLine+(line-currentLocation.oldLine-2);
      }
      currentLocation.oldLine = line;
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
          << ":" << line-currentLocation.line-currentLocation.skipLine << ":" << (col + 1) << ">";

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
  currentLocation.oldLine = 1000;
  currentLocation.skipLine = 0;
  antlr4::ANTLRInputStream input(inFile);
  SYsULexer lexer(&input);

  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();

  for (auto&& token : tokens.getTokens()) {
    print_token(token, tokens, outFile, lexer);
  }

  return 0;
}