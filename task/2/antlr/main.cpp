#include "Asg2Json.hpp"
#include "Ast2Asg.hpp"
#include "SYsULexer.hpp"
#include "Typing.hpp"
#include "asg.hpp"
#include <fstream>
#include <iostream>

int
main(int argc, char* argv[])
{
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <input> <output>\n";
    return -1;
  }

  std::ifstream inFile(argv[1]);
  if (!inFile) {
    std::cout << "Error: unable to open input file: " << argv[1] << '\n';
    return -2;
  }

  std::error_code ec;
  llvm::StringRef outPath(argv[2]);
  llvm::raw_fd_ostream outFile(outPath, ec);
  if (ec) {
    std::cout << "Error: unable to open output file: " << argv[2] << '\n';
    return -3;
  }

  std::cout << "程序 " << argv[0] << std::endl;
  std::cout << "输入 " << argv[1] << std::endl;
  std::cout << "输出 " << argv[2] << std::endl;

  // 从task1的输出文件路径中推导出task0的输出文件路径
  // 例如：/.../task1/functional-1/024_op_priority2.sysu.c/answer.txt -> /.../task0/functional-1/024_op_priority2.sysu.c
  std::string preprocessedFile(argv[1]);
  size_t lastSlash = preprocessedFile.find_last_of("/\\");
  if (lastSlash != std::string::npos) {
    // 去掉/answer.txt
    preprocessedFile = preprocessedFile.substr(0, lastSlash);
    // 找到task1，替换为task0
    size_t task1Pos = preprocessedFile.find("/task1/");
    if (task1Pos != std::string::npos) {
      preprocessedFile.replace(task1Pos + 1, 5, "task0");
    }
  }
  std::cout << "预处理文件 " << preprocessedFile << std::endl;

  antlr4::ANTLRInputStream input(inFile);
  SYsULexer lexer(&input, preprocessedFile);

  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();
  
  std::cout << "生成的 token 数量: " << tokens.size() << std::endl;
  for (size_t i = 0; i < tokens.size(); ++i) {
    auto token = tokens.get(i);
    std::cout << "Token " << i << ": type=" << token->getType() 
              << ", text='" << token->getText() << "'"
              << ", start=" << token->getStartIndex()
              << ", stop=" << token->getStopIndex()
              << ", line=" << token->getLine()
              << ", col=" << token->getCharPositionInLine() << std::endl;
  }
  
  SYsUParser parser(&tokens);

  auto ast = parser.compilationUnit();
  Obj::Mgr mgr;

  asg::Ast2Asg ast2asg(mgr);
  auto asg = ast2asg(ast->translationUnit());
  mgr.mRoot = asg;
  mgr.gc();

  asg::Typing inferType(mgr);
  inferType(asg);
  mgr.gc();

  asg::Asg2Json asg2json;
  llvm::json::Value json = asg2json(asg);

  outFile << json << '\n';
}
