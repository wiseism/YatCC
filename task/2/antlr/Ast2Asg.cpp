#include "Ast2Asg.hpp"
#include <unordered_map>

#define self (*this)

namespace asg {

// 符号表，保存当前作用域的所有声明
struct Ast2Asg::Symtbl : public std::unordered_map<std::string, Decl*>
{
  Ast2Asg& m;
  Symtbl* mPrev;

  Symtbl(Ast2Asg& m)
    : m(m)
    , mPrev(m.mSymtbl)
  {
    m.mSymtbl = this;
  }

  ~Symtbl() { m.mSymtbl = mPrev; }

  Decl* resolve(const std::string& name);
};

Decl*
Ast2Asg::Symtbl::resolve(const std::string& name)
{
  auto iter = find(name);
  if (iter != end())
    return iter->second;
  ASSERT(mPrev != nullptr); // 标识符未定义
  return mPrev->resolve(name);
}

TranslationUnit*
Ast2Asg::operator()(ast::TranslationUnitContext* ctx)
{
  auto ret = make<asg::TranslationUnit>();
  if (ctx == nullptr)
    return ret;

  Symtbl localDecls(self);

  for (auto&& i : ctx->externalDeclaration()) {
    if (auto p = i->declaration()) {
      auto decls = self(p);
      ret->decls.insert(ret->decls.end(),
                        std::make_move_iterator(decls.begin()),
                        std::make_move_iterator(decls.end()));
    }

    else if (auto p = i->functionDefinition()) {
      auto funcDecl = self(p);
      ret->decls.push_back(funcDecl);

      // 添加到声明表
      localDecls[funcDecl->name] = funcDecl;
    }

    else
      ABORT();
  }

  return ret;
}

//==============================================================================
// 类型
//==============================================================================

Ast2Asg::SpecQual
Ast2Asg::operator()(ast::DeclarationSpecifiersContext* ctx)
{
  SpecQual ret = { Type::Spec::kINVALID, Type::Qual() };

  for (auto&& i : ctx->declarationSpecifier()) {
    if (auto p = i->typeSpecifier()) {
      if (ret.first == Type::Spec::kINVALID) {
        if (p->Int())
          ret.first = Type::Spec::kInt;
        else if (p->Void())
          ret.first = Type::Spec::kVoid;
        else
          ABORT(); // 未知的类型说明符
      }

      else
        ABORT(); // 未知的类型说明符
    }

    else if (i->Const()) {
      // 处理const限定符
      ret.second.const_ = true;
    }

    else
      ABORT();
  }

  return ret;
}

std::pair<TypeExpr*, std::string>
Ast2Asg::operator()(ast::DeclaratorContext* ctx, TypeExpr* sub)
{
  return self(ctx->directDeclarator(), sub);
}

static int
eval_arrlen(Expr* expr)
{
  if (auto p = expr->dcst<IntegerLiteral>())
    return p->val;

  if (auto p = expr->dcst<DeclRefExpr>()) {
    if (p->decl == nullptr)
      ABORT();

    auto var = p->decl->dcst<VarDecl>();
    if (!var || !var->type->qual.const_)
      ABORT(); // 数组长度必须是编译期常量

    switch (var->type->spec) {
      case Type::Spec::kChar:
      case Type::Spec::kInt:
      case Type::Spec::kLong:
      case Type::Spec::kLongLong:
        return eval_arrlen(var->init);

      default:
        ABORT(); // 长度表达式必须是数值类型
    }
  }

  if (auto p = expr->dcst<UnaryExpr>()) {
    auto sub = eval_arrlen(p->sub);

    switch (p->op) {
      case UnaryExpr::kPos:
        return sub;

      case UnaryExpr::kNeg:
        return -sub;

      default:
        ABORT();
    }
  }

  if (auto p = expr->dcst<BinaryExpr>()) {
    auto lft = eval_arrlen(p->lft);
    auto rht = eval_arrlen(p->rht);

    switch (p->op) {
      case BinaryExpr::kAdd:
        return lft + rht;

      case BinaryExpr::kSub:
        return lft - rht;

      case BinaryExpr::kMul:
        return lft * rht;

      case BinaryExpr::kDiv:
        return lft / rht;

      case BinaryExpr::kMod:
        return lft % rht;

      default:
        ABORT();
    }
  }

  if (auto p = expr->dcst<InitListExpr>()) {
    if (p->list.empty())
      return 0;
    return eval_arrlen(p->list[0]);
  }

  ABORT();
}

std::pair<TypeExpr*, std::string>
Ast2Asg::operator()(ast::DirectDeclaratorContext* ctx, TypeExpr* sub)
{
  if (auto p = ctx->Identifier())
    return { sub, p->getText() };

  if (ctx->LeftBracket()) {
    auto arrayType = make<ArrayType>();
    arrayType->sub = sub;

    if (auto p = ctx->assignmentExpression())
      arrayType->len = eval_arrlen(self(p));
    else
      arrayType->len = ArrayType::kUnLen;

    return self(ctx->directDeclarator(), arrayType);
  }

  if (ctx->LeftParen()) {
    // 函数声明符：创建FunctionType，处理参数列表
    auto [texp, name] = self(ctx->directDeclarator(), sub);
    
    // 创建FunctionType
    auto funcType = make<FunctionType>();
    funcType->sub = texp;
    
    // 处理参数列表
    if (auto paramList = ctx->parameterList()) {
      for (auto paramDecl : paramList->parameterDeclaration()) {
        auto paramSq = self(paramDecl->declarationSpecifiers());
        auto [paramTexp, paramName] = self(paramDecl->declarator(), nullptr);
        
        auto paramType = make<Type>();
        paramType->spec = paramSq.first;
        paramType->qual = paramSq.second;
        paramType->texp = paramTexp;
        
        funcType->params.push_back(paramType);
        funcType->paramNames.push_back(std::move(paramName));
      }
    }
    
    return { funcType, name };
  }

  ABORT();
}

//==============================================================================
// 表达式
//==============================================================================

Expr*
Ast2Asg::operator()(ast::ExpressionContext* ctx)
{
  auto list = ctx->assignmentExpression();
  Expr* ret = self(list[0]);

  for (unsigned i = 1; i < list.size(); ++i) {
    auto node = make<BinaryExpr>();
    node->op = node->kComma;
    node->lft = ret;
    node->rht = self(list[i]);
    ret = node;
  }

  return ret;
}

Expr*
Ast2Asg::operator()(ast::AssignmentExpressionContext* ctx)
{
  if (auto p = ctx->logicalOrExpression())
    return self(p);

  auto ret = make<BinaryExpr>();
  ret->op = ret->kAssign;
  ret->lft = self(ctx->unaryExpression());
  ret->rht = self(ctx->assignmentExpression());
  setLoc(ret, ctx);
  return ret;
}

Expr*
Ast2Asg::operator()(ast::LogicalOrExpressionContext* ctx)
{
  auto list = ctx->logicalAndExpression();
  Expr* ret = self(list[0]);

  for (unsigned i = 1; i < list.size(); ++i) {
    auto node = make<BinaryExpr>();
    node->op = node->kOr;
    node->lft = ret;
    node->rht = self(list[i]);
    ret = node;
  }

  return ret;
}

Expr*
Ast2Asg::operator()(ast::LogicalAndExpressionContext* ctx)
{
  auto list = ctx->equalityExpression();
  Expr* ret = self(list[0]);

  for (unsigned i = 1; i < list.size(); ++i) {
    auto node = make<BinaryExpr>();
    node->op = node->kAnd;
    node->lft = ret;
    node->rht = self(list[i]);
    ret = node;
  }

  return ret;
}

Expr*
Ast2Asg::operator()(ast::EqualityExpressionContext* ctx)
{
  auto children = ctx->children;
  Expr* ret = self(dynamic_cast<ast::RelationalExpressionContext*>(children[0]));

  for (unsigned i = 1; i < children.size(); i += 2) {
    auto node = make<BinaryExpr>();

    auto token = dynamic_cast<antlr4::tree::TerminalNode*>(children[i])
                   ->getSymbol()
                   ->getType();
    switch (token) {
      case ast::EqualEqual:
        node->op = node->kEq;
        break;

      case ast::NotEqual:
        node->op = node->kNe;
        break;

      default:
        ABORT();
    }

    node->lft = ret;
    node->rht = self(dynamic_cast<ast::RelationalExpressionContext*>(children[i + 1]));
    ret = node;
  }

  return ret;
}

Expr*
Ast2Asg::operator()(ast::RelationalExpressionContext* ctx)
{
  auto children = ctx->children;
  Expr* ret = self(dynamic_cast<ast::AdditiveExpressionContext*>(children[0]));

  for (unsigned i = 1; i < children.size(); i += 2) {
    auto node = make<BinaryExpr>();

    auto token = dynamic_cast<antlr4::tree::TerminalNode*>(children[i])
                   ->getSymbol()
                   ->getType();
    switch (token) {
      case ast::Less:
        node->op = node->kLt;
        break;

      case ast::Greater:
        node->op = node->kGt;
        break;

      case ast::LessEqual:
        node->op = node->kLe;
        break;

      case ast::GreaterEqual:
        node->op = node->kGe;
        break;

      default:
        ABORT();
    }

    node->lft = ret;
    node->rht = self(dynamic_cast<ast::AdditiveExpressionContext*>(children[i + 1]));
    ret = node;
  }

  return ret;
}

Expr*
Ast2Asg::operator()(ast::AdditiveExpressionContext* ctx)
{
  auto children = ctx->children;
  Expr* ret = self(dynamic_cast<ast::MultiplicativeExpressionContext*>(children[0]));

  for (unsigned i = 1; i < children.size(); i += 2) {
    auto node = make<BinaryExpr>();

    auto token = dynamic_cast<antlr4::tree::TerminalNode*>(children[i])
                   ->getSymbol()
                   ->getType();
    switch (token) {
      case ast::Plus:
        node->op = node->kAdd;
        break;

      case ast::Minus:
        node->op = node->kSub;
        break;

      default:
        ABORT();
    }

    node->lft = ret;
    node->rht = self(dynamic_cast<ast::MultiplicativeExpressionContext*>(children[i + 1]));
    ret = node;
  }

  return ret;
}

Expr*
Ast2Asg::operator()(ast::MultiplicativeExpressionContext* ctx)
{
  auto children = ctx->children;
  Expr* ret = self(dynamic_cast<ast::UnaryExpressionContext*>(children[0]));

  for (unsigned i = 1; i < children.size(); i += 2) {
    auto node = make<BinaryExpr>();

    auto token = dynamic_cast<antlr4::tree::TerminalNode*>(children[i])
                   ->getSymbol()
                   ->getType();
    switch (token) {
      case ast::Star:
        node->op = node->kMul;
        break;

      case ast::Div:
        node->op = node->kDiv;
        break;

      case ast::Mod:
        node->op = node->kMod;
        break;

      default:
        ABORT();
    }

    node->lft = ret;
    node->rht = self(dynamic_cast<ast::UnaryExpressionContext*>(children[i + 1]));
    ret = node;
  }

  return ret;
}

Expr*
Ast2Asg::operator()(ast::UnaryExpressionContext* ctx)
{
  if (auto p = ctx->postfixExpression())
    return self(p);

  if (ctx->Not()) {
    auto ret = make<UnaryExpr>();
    ret->op = ret->kNot;
    ret->sub = self(ctx->unaryExpression());
    return ret;
  }

  auto ret = make<UnaryExpr>();

  switch (
    dynamic_cast<antlr4::tree::TerminalNode*>(ctx->unaryOperator()->children[0])
      ->getSymbol()
      ->getType()) {
    case ast::Plus:
      ret->op = ret->kPos;
      break;

    case ast::Minus:
      ret->op = ret->kNeg;
      break;

    default:
      ABORT();
  }

  ret->sub = self(ctx->unaryExpression());

  return ret;
}

Expr*
Ast2Asg::operator()(ast::PostfixExpressionContext* ctx)
{
  if (auto p = ctx->primaryExpression())
    return self(p);

  // 数组访问
  if (ctx->LeftBracket()) {
    auto arrayExpr = self(ctx->postfixExpression());
    auto indexExpr = self(ctx->expression());
    
    auto ret = make<BinaryExpr>();
    ret->op = ret->kIndex;
    ret->lft = arrayExpr;
    ret->rht = indexExpr;
    return ret;
  }

  // 函数调用
  auto funcExpr = self(ctx->postfixExpression());
  auto ret = make<CallExpr>();
  ret->head = funcExpr;

  if (auto p = ctx->argumentExpressionList()) {
    for (auto&& arg : p->assignmentExpression())
      ret->args.push_back(self(arg));
  }

  return ret;
}

Expr*
Ast2Asg::operator()(ast::PrimaryExpressionContext* ctx)
{

  if (auto p = ctx->Identifier()) {
    auto name = p->getText();
    auto ret = make<DeclRefExpr>();
    ret->decl = mSymtbl->resolve(name);
    
    // 设置类型和值类别
    if (ret->decl) {
      ret->type = ret->decl->type;
      ret->cate = Expr::Cate::kLValue;  // 变量引用是左值
      
      // 标记变量被使用
      if (auto varDecl = ret->decl->dcst<VarDecl>()) {
        varDecl->isUsed = true;
      }
    }
    
    // 设置位置信息
    setLoc(ret, ctx);
    
    return ret;
  }

  if (auto p = ctx->Constant()) {
    auto text = p->getText();

    auto ret = make<IntegerLiteral>();

    ASSERT(!text.empty());
    if (text[0] != '0')
      ret->val = std::stoll(text);

    else if (text.size() == 1)
      ret->val = 0;

    else if (text[1] == 'x' || text[1] == 'X')
      ret->val = std::stoll(text.substr(2), nullptr, 16);

    else
      ret->val = std::stoll(text.substr(1), nullptr, 8);

    // 设置位置信息
    setLoc(ret, ctx);

    return ret;
  }

  // 括号表达式
  if (ctx->LeftParen()) {
    return self(ctx->expression());
  }

  ABORT();
}

Expr*
Ast2Asg::operator()(ast::InitializerContext* ctx)
{
  if (auto p = ctx->assignmentExpression())
    return self(p);

  auto ret = make<InitListExpr>();

  if (auto p = ctx->initializerList()) {
    for (auto&& i : p->initializer()) {
      // 将初始化列表展平
      auto expr = self(i);
      if (auto p = expr->dcst<InitListExpr>()) {
        for (auto&& sub : p->list)
          ret->list.push_back(sub);
      } else {
        ret->list.push_back(expr);
      }
    }
  }

  return ret;
}

//==============================================================================
// 语句
//==============================================================================

Stmt*
Ast2Asg::operator()(ast::StatementContext* ctx)
{
  if (auto p = ctx->compoundStatement())
    return self(p);

  if (auto p = ctx->expressionStatement())
    return self(p);

  if (auto p = ctx->selectionStatement())
    return self(p);

  if (auto p = ctx->iterationStatement())
    return self(p);

  if (auto p = ctx->jumpStatement())
    return self(p);

  ABORT();
}

CompoundStmt*
Ast2Asg::operator()(ast::CompoundStatementContext* ctx)
{
  auto ret = make<CompoundStmt>();

  if (auto p = ctx->blockItemList()) {
    Symtbl localDecls(self);

    for (auto&& i : p->blockItem()) {
      if (auto q = i->declaration()) {
        auto sub = make<DeclStmt>();
        sub->decls = self(q);
        setRange(sub, q);
        ret->subs.push_back(sub);
      }

      else if (auto q = i->statement())
        ret->subs.push_back(self(q));

      else
        ABORT();
    }
  }

  return ret;
}

Stmt*
Ast2Asg::operator()(ast::ExpressionStatementContext* ctx)
{
  if (auto p = ctx->expression()) {
    auto ret = make<ExprStmt>();
    ret->expr = self(p);
    return ret;
  }

  return make<NullStmt>();
}

Stmt*
Ast2Asg::operator()(ast::SelectionStatementContext* ctx)
{
  auto ret = make<IfStmt>();
  ret->cond = self(ctx->expression());
  ret->then = self(ctx->statement(0));
  if (ctx->Else())
    ret->else_ = self(ctx->statement(1));
  return ret;
}

Stmt*
Ast2Asg::operator()(ast::IterationStatementContext* ctx)
{
  auto ret = make<WhileStmt>();
  ret->cond = self(ctx->expression());
  ret->body = self(ctx->statement());
  return ret;
}

Stmt*
Ast2Asg::operator()(ast::JumpStatementContext* ctx)
{
  if (ctx->Return()) {
    auto ret = make<ReturnStmt>();
    ret->func = mCurrentFunc;
    if (auto p = ctx->expression())
      ret->expr = self(p);
    return ret;
  }

  if (ctx->Break()) {
    return make<BreakStmt>();
  }

  if (ctx->Continue()) {
    return make<ContinueStmt>();
  }

  ABORT();
}

//==============================================================================
// 声明
//==============================================================================

std::vector<Decl*>
Ast2Asg::operator()(ast::DeclarationContext* ctx)
{
  std::vector<Decl*> ret;

  auto specs = self(ctx->declarationSpecifiers());

  if (auto p = ctx->initDeclaratorList()) {
    for (auto&& j : p->initDeclarator())
      ret.push_back(self(j, specs));
  }

  // 如果 initDeclaratorList 为空则这行声明语句无意义
  return ret;
}

FunctionDecl*
Ast2Asg::operator()(ast::FunctionDefinitionContext* ctx)
{
  auto ret = make<FunctionDecl>();
  mCurrentFunc = ret;

  auto type = make<Type>();
  ret->type = type;

  auto sq = self(ctx->declarationSpecifiers());
  type->spec = sq.first, type->qual = sq.second;

  auto [texp, name] = self(ctx->declarator(), nullptr);
  
  // declarator现在返回FunctionType，直接使用
  if (auto funcTypeFromDecl = dynamic_cast<FunctionType*>(texp)) {
    type->texp = funcTypeFromDecl;
  } else {
    // 如果没有参数列表，创建一个空的FunctionType
    auto funcType = make<FunctionType>();
    funcType->sub = texp;
    type->texp = funcType;
  }
  
  ret->name = std::move(name);

  // 函数定义在签名之后就加入符号表，以允许递归调用
  // 注意：这里添加到当前符号表（应该是TranslationUnit的符号表）
  (*mSymtbl)[ret->name] = ret;

  // 创建函数作用域
  Symtbl localDecls(self);
  
  // 从declarator中重新解析参数列表，获取参数名
  // 获取directDeclarator
  if (auto declarator = ctx->declarator()) {
    if (auto directDeclarator = declarator->directDeclarator()) {
      // 找到包含参数列表的directDeclarator
      // 对于func(int p)，结构是：directDeclarator -> directDeclarator LeftParen parameterList RightParen
      while (directDeclarator && !directDeclarator->LeftParen()) {
        directDeclarator = directDeclarator->directDeclarator();
      }
      
      if (directDeclarator && directDeclarator->LeftParen()) {
        if (auto paramList = directDeclarator->parameterList()) {
          for (auto paramDecl : paramList->parameterDeclaration()) {
            auto paramSq = self(paramDecl->declarationSpecifiers());
            auto [paramTexp, paramName] = self(paramDecl->declarator(), nullptr);
            
            auto paramType = make<Type>();
            paramType->spec = paramSq.first;
            paramType->qual = paramSq.second;
            paramType->texp = paramTexp;
            
            auto varDecl = make<VarDecl>();
            varDecl->type = paramType;
            varDecl->name = std::move(paramName);
            
            ret->params.push_back(varDecl);
            
            // 添加参数到符号表
            localDecls[varDecl->name] = varDecl;
          }
        }
      }
    }
  }

  ret->body = self(ctx->compoundStatement());

  return ret;
}

Decl*
Ast2Asg::operator()(ast::InitDeclaratorContext* ctx, SpecQual sq)
{
  auto [texp, name] = self(ctx->declarator(), nullptr);
  Decl* ret;

  if (auto funcType = texp->dcst<FunctionType>()) {
    auto fdecl = make<FunctionDecl>();
    auto type = make<Type>();
    fdecl->type = type;

    type->spec = sq.first;
    type->qual = sq.second;
    type->texp = funcType;

    fdecl->name = std::move(name);
    for (size_t i = 0; i < funcType->params.size(); ++i) {
      auto paramDecl = make<VarDecl>();
      paramDecl->type = funcType->params[i];
      if (i < funcType->paramNames.size()) {
        paramDecl->name = funcType->paramNames[i];
      }
      fdecl->params.push_back(paramDecl);
    }

    // 设置函数声明的位置信息
    setLoc(fdecl, ctx);

    if (ctx->initializer())
      ABORT();
    fdecl->body = nullptr;

    ret = fdecl;
  }

  else {
    auto vdecl = make<VarDecl>();
    auto type = make<Type>();
    vdecl->type = type;

    type->spec = sq.first;
    type->qual = sq.second;
    type->texp = texp;
    vdecl->name = std::move(name);

    if (auto p = ctx->initializer())
      vdecl->init = self(p);
    else
      vdecl->init = nullptr;

    // 设置位置信息
    setLoc(vdecl, ctx);

    ret = vdecl;
  }

  // 这个实现允许符号重复定义，新定义会取代旧定义
  (*mSymtbl)[ret->name] = ret;
  return ret;
}

void
Ast2Asg::setLoc(Decl* decl, antlr4::ParserRuleContext* ctx)
{
  if (!ctx || !ctx->start)
    return;

  auto start = ctx->start;
  auto stop = ctx->stop ? ctx->stop : start;

  // loc使用变量名的位置
  decl->loc.line = start->getLine();
  decl->loc.col = start->getCharPositionInLine();
  decl->loc.offset = start->getStartIndex() + 1;
  decl->loc.tokLen = start->getStopIndex() - start->getStartIndex() + 1;

  // range.begin使用类型说明符的位置（假设在变量名前4个字符）
  decl->range.begin.line = start->getLine();
  decl->range.begin.col = start->getCharPositionInLine() - 4;
  decl->range.begin.offset = start->getStartIndex() + 1 - 4;
  decl->range.begin.tokLen = 3;  // "int"的长度

  // range.end使用变量名的位置
  decl->range.end.line = start->getLine();
  decl->range.end.col = start->getCharPositionInLine();
  decl->range.end.offset = start->getStartIndex() + 1;
  decl->range.end.tokLen = start->getStopIndex() - start->getStartIndex() + 1;
}

void
Ast2Asg::setLoc(Expr* expr, antlr4::ParserRuleContext* ctx)
{
  if (!ctx || !ctx->start)
    return;

  auto start = ctx->start;
  auto stop = ctx->stop ? ctx->stop : start;

  expr->loc.line = start->getLine();
  expr->loc.col = start->getCharPositionInLine();
  expr->loc.offset = start->getStartIndex() + 1;
  expr->loc.tokLen = start->getStopIndex() - start->getStartIndex() + 1;

  expr->range.begin.line = start->getLine();
  expr->range.begin.col = start->getCharPositionInLine();
  expr->range.begin.offset = start->getStartIndex() + 1;
  expr->range.begin.tokLen = start->getStopIndex() - start->getStartIndex() + 1;

  expr->range.end.line = stop->getLine();
  expr->range.end.col = stop->getCharPositionInLine();
  expr->range.end.offset = stop->getStartIndex() + 1;
  expr->range.end.tokLen = stop->getStopIndex() - stop->getStartIndex() + 1;
}

void
Ast2Asg::setRange(Stmt* stmt, antlr4::ParserRuleContext* ctx)
{
  if (!ctx || !ctx->start)
    return;

  auto start = ctx->start;
  auto stop = ctx->stop ? ctx->stop : start;

  stmt->range.begin.line = start->getLine();
  stmt->range.begin.col = start->getCharPositionInLine();
  stmt->range.begin.offset = start->getStartIndex() + 1;
  stmt->range.begin.tokLen = start->getStopIndex() - start->getStartIndex() + 1;

  stmt->range.end.line = stop->getLine();
  stmt->range.end.col = stop->getCharPositionInLine();
  stmt->range.end.offset = stop->getStartIndex() + 1;
  stmt->range.end.tokLen = stop->getStopIndex() - stop->getStartIndex() + 1;
}

} // namespace asg
