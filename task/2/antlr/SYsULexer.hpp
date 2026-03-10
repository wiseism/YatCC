#pragma once

#include <antlr4-runtime.h>
#include <deque>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <utility>

class SYsULexer : public antlr4::TokenSource
{
public:
  SYsULexer(antlr4::CharStream* input);

  std::unique_ptr<antlr4::Token> nextToken() override;

  size_t getLine() const override;

  size_t getCharPositionInLine() override;

  antlr4::CharStream* getInputStream() override;

  std::string getSourceName() override;

  template<typename T1>
  void setTokenFactory(antlr4::TokenFactory<T1>* tokenFactory)
  {
    mFactory = tokenFactory;
  }

  antlr4::TokenFactory<antlr4::CommonToken>* getTokenFactory() override;

private:
  antlr4::CharStream* mInput;
  std::pair<TokenSource*, antlr4::CharStream*> mSource;
  antlr4::TokenFactory<antlr4::CommonToken>* mFactory;

  std::string mSourceName;
  size_t mLine = 1, mColumn = 0;
  size_t mTokenIndex = 0;
  
  // 从（行，列）到offset的映射
  std::map<std::pair<size_t, size_t>, size_t> mOffsetMap;
  
  // 构建offset映射
  void buildOffsetMap(const std::string& sourcePath);

  std::unique_ptr<antlr4::CommonToken> common_token(ssize_t type,
                                                    size_t start,
                                                    size_t stop,
                                                    std::string text = {},
                                                    size_t line = 0,
                                                    size_t column = 0)
  {
    return mFactory->create(mSource,
                            type,
                            std::move(text),
                            antlr4::Token::DEFAULT_CHANNEL,
                            start,
                            stop,
                            line == 0 ? mLine : line,
                            column == 0 ? mColumn : column);
  }
};
