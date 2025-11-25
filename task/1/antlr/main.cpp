#include "SYsULexer.h" // 确保这里的头文件名与您生成的词法分析器匹配
#include <fstream>
#include <iostream>
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
    int column;
};

LocationInfo currentLocation = {"", 1, 1};

void updateLocationInfo(const antlr4::Token* token) {
    // 这里可以根据预处理信息更新位置信息
    currentLocation.line = token->getLine();
    currentLocation.column = token->getCharPositionInLine() + 1;
}

void print_token(const antlr4::Token* token,
                const antlr4::CommonTokenStream& tokens,
                std::ofstream& outFile,
                const antlr4::Lexer& lexer) {
    auto& vocabulary = lexer.getVocabulary();
    auto tokenTypeName = std::string(vocabulary.getSymbolicName(token->getType()));

    if (tokenTypeName.empty()) {
        tokenTypeName = "<UNKNOWN>";
    }

    if (tokenTypeMapping.find(tokenTypeName) != tokenTypeMapping.end()) {
        tokenTypeName = tokenTypeMapping[tokenTypeName];
    }

    updateLocationInfo(token);

    std::string tokenText = token->getText();
    if (token->getType() == antlr4::Token::EOF) {
        tokenText = "";
    }

    // 处理特殊符号的显示
    if (tokenTypeName == "semi") {
        tokenText = "';'";
    } else if (tokenTypeName == "l_paren") {
        tokenText = "'('";
    } else if (tokenTypeName == "r_paren") {
        tokenText = "')'";
    } else if (tokenTypeName == "l_brace") {
        tokenText = "'{'";
    } else if (tokenTypeName == "r_brace") {
        tokenText = "'}'";
    }

    outFile << tokenTypeName << " '" << tokenText << "'";

    // 添加位置信息
    outFile << "\tLoc=<" << currentLocation.filename << ":"
            << currentLocation.line << ":" << currentLocation.column << ">";

    // 检查是否在行首
    if (token->getCharPositionInLine() == 0 && token->getText() != "<EOF>") {
        outFile << "\t[StartOfLine]";
    }

    // 检查是否有前导空格
    size_t leadingSpaces = token->getText().find_first_not_of(" \t");
    if (leadingSpaces != 0 && leadingSpaces != std::string::npos) {
        outFile << "\t[LeadingSpace]";
    }

    outFile << std::endl;
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

    antlr4::ANTLRInputStream input(inFile);
    SYsULexer lexer(&input);

    // 设置源文件名
    currentLocation.filename = argv[1];

    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();

    for (auto&& token : tokens.getTokens()) {
        print_token(token, tokens, outFile, lexer);
    }

    return 0;
}