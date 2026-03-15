#include "EmitIR.hpp"
#include <llvm/Transforms/Utils/ModuleUtils.h>

#define self (*this)

using namespace asg;

EmitIR::EmitIR(Obj::Mgr& mgr, llvm::LLVMContext& ctx, llvm::StringRef mid)
  : mMgr(mgr)
  , mMod(mid, ctx)
  , mCtx(ctx)
  , mIntTy(llvm::Type::getInt32Ty(ctx))
  , mI1Ty(llvm::Type::getInt1Ty(ctx))
  , mCurIrb(std::make_unique<llvm::IRBuilder<>>(ctx))
  , mCtorTy(llvm::FunctionType::get(llvm::Type::getVoidTy(ctx), false))
  , mLoopBreakBb(nullptr)
  , mLoopContinueBb(nullptr)
{
}

llvm::Module&
EmitIR::operator()(asg::TranslationUnit* tu)
{
  for (auto&& i : tu->decls)
    self(i);
  return mMod;
}

//==============================================================================
// 类型
//==============================================================================

llvm::Type*
EmitIR::operator()(const Type* type)
{
  if (type->texp == nullptr) {
    switch (type->spec) {
      case Type::Spec::kVoid:
        return llvm::Type::getVoidTy(mCtx);
      case Type::Spec::kChar:
        return llvm::Type::getInt8Ty(mCtx);
      case Type::Spec::kInt:
        return llvm::Type::getInt32Ty(mCtx);
      case Type::Spec::kLong:
      case Type::Spec::kLongLong:
        return llvm::Type::getInt64Ty(mCtx);
      default:
        ABORT();
    }
  }

  Type subt;
  subt.spec = type->spec;
  subt.qual = type->qual;
  subt.texp = type->texp->sub;

  if (auto p = type->texp->dcst<ArrayType>()) {
    auto elemTy = self(&subt);
    return llvm::ArrayType::get(elemTy, p->len);
  }

  if (type->texp->dcst<PointerType>()) {
    return llvm::PointerType::get(mCtx, 0);
  }

  if (auto p = type->texp->dcst<FunctionType>()) {
    std::vector<llvm::Type*> pty;
    for (auto&& param : p->params)
      pty.push_back(self(param));
    return llvm::FunctionType::get(self(&subt), std::move(pty), false);
  }

  ABORT();
}

//==============================================================================
// 表达式
//==============================================================================

llvm::Value*
EmitIR::operator()(Expr* obj)
{
  // 在此添加对更多表达式处理的跳转

  if (auto p = obj->dcst<IntegerLiteral>())
    return self(p);
  if (auto p = obj->dcst<DeclRefExpr>())
    return self(p);
  if (auto p = obj->dcst<BinaryExpr>())
    return self(p);
  if (auto p = obj->dcst<UnaryExpr>())
    return self(p);
  if (auto p = obj->dcst<ParenExpr>())
    return self(p);
  if (auto p = obj->dcst<ImplicitCastExpr>())
    return self(p);
  if (auto p = obj->dcst<CallExpr>())
    return self(p);
  if (auto p = obj->dcst<InitListExpr>())
    return self(p);
  if (auto p = obj->dcst<ImplicitInitExpr>())
    return self(p);
  if (auto p = obj->dcst<ArraySubscriptExpr>())
    return self(p);
  ABORT();
}

bool
EmitIR::hasInsertionPoint() const
{
  return mCurFunc && mCurIrb && mCurIrb->GetInsertBlock();
}

llvm::Value*
EmitIR::toBool(llvm::Value* v)
{
  auto ty = v->getType();
  if (ty->isIntegerTy(1))
    return v;
  if (ty->isIntegerTy())
    return mCurIrb->CreateICmpNE(v, llvm::ConstantInt::get(ty, 0));
  if (ty->isPointerTy())
    return mCurIrb->CreateICmpNE(
      v, llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(ty)));
  return v;
}

llvm::Value*
EmitIR::toInt32(llvm::Value* v)
{
  auto ty = v->getType();
  if (ty->isIntegerTy(32))
    return v;
  if (ty->isIntegerTy(1))
    return mCurIrb->CreateZExt(v, mIntTy);
  if (ty->isIntegerTy() && ty->getIntegerBitWidth() < 32)
    return mCurIrb->CreateZExt(v, mIntTy);
  if (ty->isIntegerTy() && ty->getIntegerBitWidth() > 32)
    return mCurIrb->CreateTrunc(v, mIntTy);
  return v;
}

llvm::Value*
EmitIR::castTo(llvm::Value* v, llvm::Type* dstTy)
{
  if (v->getType() == dstTy)
    return v;
  if (dstTy->isIntegerTy(32))
    return toInt32(v);
  if (dstTy->isIntegerTy(1))
    return toBool(v);
  if (dstTy->isPointerTy() && v->getType()->isPointerTy())
    return mCurIrb->CreateBitCast(v, dstTy);
  return v;
}

llvm::Type*
EmitIR::getElemType(const asg::Type* type)
{
  if (!type || !type->texp)
    return nullptr;

  Type subt;
  subt.spec = type->spec;
  subt.qual = type->qual;
  subt.texp = type->texp->sub;
  return self(&subt);
}

void
EmitIR::collectArrayDims(const asg::Type* type, std::vector<std::uint32_t>& dims)
{
  auto texp = type ? type->texp : nullptr;
  while (texp) {
    if (auto arr = texp->dcst<ArrayType>()) {
      dims.push_back(arr->len);
      texp = arr->sub;
    } else {
      break;
    }
  }
}

void
EmitIR::flattenInitList(asg::InitListExpr* init, std::vector<asg::Expr*>& out)
{
  if (!init)
    return;
  for (auto* e : init->list) {
    if (!e)
      continue;
    if (auto inner = e->dcst<InitListExpr>()) {
      flattenInitList(inner, out);
    } else {
      out.push_back(e);
    }
  }
}

bool
EmitIR::evalConstInt(asg::Expr* expr, std::int64_t& out)
{
  if (!expr)
    return false;
  if (auto lit = expr->dcst<IntegerLiteral>()) {
    out = static_cast<std::int64_t>(lit->val);
    return true;
  }
  if (auto paren = expr->dcst<ParenExpr>())
    return evalConstInt(paren->sub, out);
  if (auto cast = expr->dcst<ImplicitCastExpr>())
    return evalConstInt(cast->sub, out);
  if (auto unary = expr->dcst<UnaryExpr>()) {
    std::int64_t v;
    if (!evalConstInt(unary->sub, v))
      return false;
    switch (unary->op) {
      case UnaryExpr::kPos:
        out = v;
        return true;
      case UnaryExpr::kNeg:
        out = -v;
        return true;
      case UnaryExpr::kNot:
        out = (v == 0) ? 1 : 0;
        return true;
      default:
        return false;
    }
  }
  if (auto binary = expr->dcst<BinaryExpr>()) {
    std::int64_t l, r;
    if (!evalConstInt(binary->lft, l))
      return false;
    // short-circuit for logical ops
    if (binary->op == BinaryExpr::kAnd) {
      if (l == 0) {
        out = 0;
        return true;
      }
      if (!evalConstInt(binary->rht, r))
        return false;
      out = (r != 0) ? 1 : 0;
      return true;
    }
    if (binary->op == BinaryExpr::kOr) {
      if (l != 0) {
        out = 1;
        return true;
      }
      if (!evalConstInt(binary->rht, r))
        return false;
      out = (r != 0) ? 1 : 0;
      return true;
    }
    if (!evalConstInt(binary->rht, r))
      return false;
    switch (binary->op) {
      case BinaryExpr::kAdd:
        out = l + r;
        return true;
      case BinaryExpr::kSub:
        out = l - r;
        return true;
      case BinaryExpr::kMul:
        out = l * r;
        return true;
      case BinaryExpr::kDiv:
        if (r == 0)
          return false;
        out = l / r;
        return true;
      case BinaryExpr::kMod:
        if (r == 0)
          return false;
        out = l % r;
        return true;
      case BinaryExpr::kLt:
        out = (l < r) ? 1 : 0;
        return true;
      case BinaryExpr::kGt:
        out = (l > r) ? 1 : 0;
        return true;
      case BinaryExpr::kLe:
        out = (l <= r) ? 1 : 0;
        return true;
      case BinaryExpr::kGe:
        out = (l >= r) ? 1 : 0;
        return true;
      case BinaryExpr::kEq:
        out = (l == r) ? 1 : 0;
        return true;
      case BinaryExpr::kNe:
        out = (l != r) ? 1 : 0;
        return true;
      default:
        return false;
    }
  }
  if (auto ref = expr->dcst<DeclRefExpr>()) {
    if (auto var = ref->decl->dcst<VarDecl>()) {
      if (var->init)
        return evalConstInt(var->init, out);
    }
  }
  return false;
}

llvm::Constant*
EmitIR::constFromExpr(asg::Expr* expr, llvm::Type* ty)
{
  std::int64_t v;
  if (evalConstInt(expr, v))
    return llvm::ConstantInt::get(ty, v);
  return llvm::ConstantInt::get(ty, 0);
}

llvm::Constant*
EmitIR::operator()(IntegerLiteral* obj)
{
  return llvm::ConstantInt::get(self(obj->type), obj->val);
}

// 声明引用处理
llvm::Value*
EmitIR::operator()(DeclRefExpr* obj)
{
  if (auto var = obj->decl->dcst<VarDecl>()) {
    // 返回变量地址（lvalue），由 ImplicitCast 负责加载
    return static_cast<llvm::Value*>(var->any);
  }
  if (auto func = obj->decl->dcst<FunctionDecl>()) {
    return static_cast<llvm::Value*>(func->any);
  }
  ABORT();
}

// 二元表达式处理
llvm::Value*
EmitIR::operator()(BinaryExpr* obj)
{
  auto lft = self(obj->lft);
  
  switch (obj->op) {
    case BinaryExpr::kAdd:
      return mCurIrb->CreateAdd(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kSub:
      return mCurIrb->CreateSub(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kMul:
      return mCurIrb->CreateMul(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kDiv:
      return mCurIrb->CreateSDiv(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kMod:
      return mCurIrb->CreateSRem(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kLt:
      return mCurIrb->CreateICmpSLT(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kGt:
      return mCurIrb->CreateICmpSGT(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kLe:
      return mCurIrb->CreateICmpSLE(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kGe:
      return mCurIrb->CreateICmpSGE(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kEq:
      return mCurIrb->CreateICmpEQ(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kNe:
      return mCurIrb->CreateICmpNE(toInt32(lft), toInt32(self(obj->rht)));
    case BinaryExpr::kAnd: {
      auto lhsBb = mCurIrb->GetInsertBlock();
      auto lhsBool = toBool(lft);
      auto rhsBb = llvm::BasicBlock::Create(mCtx, "land.rhs", mCurFunc);
      auto mergeBb = llvm::BasicBlock::Create(mCtx, "land.merge", mCurFunc);
      mCurIrb->CreateCondBr(lhsBool, rhsBb, mergeBb);

      mCurIrb->SetInsertPoint(rhsBb);
      auto rhsBool = toBool(self(obj->rht));
      auto rhsEndBb = mCurIrb->GetInsertBlock();
      if (!mCurIrb->GetInsertBlock()->getTerminator())
        mCurIrb->CreateBr(mergeBb);

      mCurIrb->SetInsertPoint(mergeBb);
      auto phi = mCurIrb->CreatePHI(mI1Ty, 2);
      phi->addIncoming(llvm::ConstantInt::get(mI1Ty, 0), lhsBb);
      phi->addIncoming(rhsBool, rhsEndBb);
      return mCurIrb->CreateZExt(phi, mIntTy);
    }
    case BinaryExpr::kOr: {
      auto lhsBb = mCurIrb->GetInsertBlock();
      auto lhsBool = toBool(lft);
      auto rhsBb = llvm::BasicBlock::Create(mCtx, "lor.rhs", mCurFunc);
      auto mergeBb = llvm::BasicBlock::Create(mCtx, "lor.merge", mCurFunc);
      mCurIrb->CreateCondBr(lhsBool, mergeBb, rhsBb);

      mCurIrb->SetInsertPoint(rhsBb);
      auto rhsBool = toBool(self(obj->rht));
      auto rhsEndBb = mCurIrb->GetInsertBlock();
      if (!mCurIrb->GetInsertBlock()->getTerminator())
        mCurIrb->CreateBr(mergeBb);

      mCurIrb->SetInsertPoint(mergeBb);
      auto phi = mCurIrb->CreatePHI(mI1Ty, 2);
      phi->addIncoming(llvm::ConstantInt::get(mI1Ty, 1), lhsBb);
      phi->addIncoming(rhsBool, rhsEndBb);
      return mCurIrb->CreateZExt(phi, mIntTy);
    }
    case BinaryExpr::kAssign:
    {
      auto addr = getLValueAddr(obj->lft);
      auto dstTy = self(obj->lft->type);
      auto val = castTo(self(obj->rht), dstTy);
      mCurIrb->CreateStore(val, addr);
      return val;
    }
    case BinaryExpr::kComma:
      self(obj->lft);
      return self(obj->rht);
    default:
      ABORT();
  }
}

// 一元表达式处理
llvm::Value*
EmitIR::operator()(UnaryExpr* obj)
{
  auto sub = self(obj->sub);
  
  switch (obj->op) {
    case UnaryExpr::kPos:
      return toInt32(sub);
    case UnaryExpr::kNeg:
      return mCurIrb->CreateNeg(toInt32(sub));
    case UnaryExpr::kNot:
      return mCurIrb->CreateZExt(
        mCurIrb->CreateNot(toBool(sub)), mIntTy);
    default:
      ABORT();
  }
}

// 括号表达式处理
llvm::Value*
EmitIR::operator()(ParenExpr* obj)
{
  return self(obj->sub);
}

// 隐式类型转换处理
llvm::Value*
EmitIR::operator()(ImplicitCastExpr* obj)
{
  auto val = self(obj->sub);
  
  switch (obj->kind) {
    case ImplicitCastExpr::kLValueToRValue:
      if (hasInsertionPoint()) {
        if (obj->sub->type && obj->sub->type->texp &&
            obj->sub->type->texp->dcst<ArrayType>()) {
          return val;
        }
        auto loadTy = self(obj->sub->type);
        return mCurIrb->CreateLoad(loadTy, val);
      }
      return val;
    case ImplicitCastExpr::kArrayToPointerDecay: {
      if (!obj->sub->type || !obj->sub->type->texp ||
          !obj->sub->type->texp->dcst<ArrayType>())
        return val;
      auto arrTy = self(obj->sub->type);
      if (!hasInsertionPoint())
        return val;
      return mCurIrb->CreateInBoundsGEP(
        arrTy, val,
        { llvm::ConstantInt::get(mIntTy, 0),
          llvm::ConstantInt::get(mIntTy, 0) });
    }
    case ImplicitCastExpr::kFunctionToPointerDecay:
      return val;
    case ImplicitCastExpr::kIntegralCast: {
      auto dstTy = self(obj->type);
      return castTo(val, dstTy);
    }
    case ImplicitCastExpr::kNoOp:
      return val;
    default:
      return val;
  }
}

// 数组下标访问处理
llvm::Value*
EmitIR::operator()(ArraySubscriptExpr* obj)
{
  auto baseVal = self(obj->base);
  auto idxVal = self(obj->idx);
  if (!hasInsertionPoint())
    return llvm::ConstantInt::get(mIntTy, 0);

  // 根据基底类型决定 GEP 形式
  if (obj->base->type && obj->base->type->texp &&
      obj->base->type->texp->dcst<ArrayType>()) {
    auto arrTy = self(obj->base->type);
    return mCurIrb->CreateInBoundsGEP(
      arrTy, baseVal,
      { llvm::ConstantInt::get(mIntTy, 0), toInt32(idxVal) });
  }

  auto elemTy = getElemType(obj->base->type);
  if (!elemTy)
    elemTy = mIntTy;
  return mCurIrb->CreateInBoundsGEP(elemTy, baseVal, toInt32(idxVal));
}

// 函数调用处理
llvm::Value*
EmitIR::operator()(CallExpr* obj)
{
  // 获取函数
  auto funcVal = self(obj->head);
  auto callee = llvm::dyn_cast<llvm::Function>(funcVal);
  if (!callee) {
    llvm::errs() << "CallExpr: callee is not a function\n";
    ABORT();
  }
  
  // 处理参数
  std::vector<llvm::Value*> args;
  auto fty = callee->getFunctionType();
  for (std::size_t i = 0; i < obj->args.size(); ++i) {
    auto argVal = self(obj->args[i]);
    if (i < fty->getNumParams()) {
      argVal = castTo(argVal, fty->getParamType(i));
    }
    args.push_back(argVal);
  }
  
  // 调用函数
  auto call = mCurIrb->CreateCall(callee, args);
  return call;
}

// 初始化列表处理
llvm::Value*
EmitIR::operator()(InitListExpr* obj)
{
  if (obj->list.empty())
    return llvm::ConstantInt::get(mIntTy, 0);
  return self(obj->list.front());
}

// 隐式初始化表达式处理
llvm::Value*
EmitIR::operator()(ImplicitInitExpr* obj)
{
  auto ty = self(obj->type);
  if (auto arrTy = llvm::dyn_cast<llvm::ArrayType>(ty)) {
    auto elemTy = arrTy->getElementType();
    auto numElems = arrTy->getNumElements();
    std::vector<llvm::Constant*> elems(numElems, llvm::ConstantInt::get(elemTy, 0));
    return llvm::ConstantArray::get(llvm::ArrayType::get(elemTy, numElems), elems);
  }
  return llvm::ConstantInt::get(ty, 0);
}

//==============================================================================
// 语句
//==============================================================================

void
EmitIR::operator()(Stmt* obj)
{
  // 在此添加对更多Stmt类型的处理的跳转

  if (auto p = obj->dcst<CompoundStmt>())
    return self(p);

  if (auto p = obj->dcst<ReturnStmt>())
    return self(p);

  if (auto p = obj->dcst<ExprStmt>())
    return self(p);

  if (auto p = obj->dcst<NullStmt>())
    return self(p);

  if (auto p = obj->dcst<IfStmt>())
    return self(p);

  if (auto p = obj->dcst<WhileStmt>())
    return self(p);
  if (auto p = obj->dcst<DoStmt>())
    return self(p);
  if (auto p = obj->dcst<BreakStmt>())
    return self(p);
  if (auto p = obj->dcst<ContinueStmt>())
    return self(p);
  if (auto p = obj->dcst<DeclStmt>())
    return self(p);

  ABORT();
}

// 表达式语句处理
void
EmitIR::operator()(ExprStmt* obj)
{
  if (obj->expr)
    self(obj->expr);
}

// 空语句处理
void
EmitIR::operator()(NullStmt* obj)
{
  // 空语句不需要处理
}

// 条件语句处理
void
EmitIR::operator()(IfStmt* obj)
{
  auto condVal = self(obj->cond);
  llvm::Value* condBool = toBool(condVal);
  
  auto thenBb = llvm::BasicBlock::Create(mCtx, "then", mCurFunc);
  auto elseBb = llvm::BasicBlock::Create(mCtx, "else", mCurFunc);
  auto mergeBb = llvm::BasicBlock::Create(mCtx, "merge", mCurFunc);
  
  mCurIrb->CreateCondBr(condBool, thenBb, elseBb);
  
  // 处理then分支
  mCurIrb->SetInsertPoint(thenBb);
  self(obj->then);
  if (!mCurIrb->GetInsertBlock()->getTerminator()) {
    mCurIrb->CreateBr(mergeBb);
  }
  
  // 处理else分支
  mCurIrb->SetInsertPoint(elseBb);
  if (obj->else_)
    self(obj->else_);
  if (!mCurIrb->GetInsertBlock()->getTerminator()) {
    mCurIrb->CreateBr(mergeBb);
  }
  
  // 设置合并块为当前插入点
  mCurIrb->SetInsertPoint(mergeBb);
}

// do-while语句处理
void
EmitIR::operator()(DoStmt* obj)
{
  auto bodyBb = llvm::BasicBlock::Create(mCtx, "body", mCurFunc);
  auto condBb = llvm::BasicBlock::Create(mCtx, "cond", mCurFunc);
  auto mergeBb = llvm::BasicBlock::Create(mCtx, "merge", mCurFunc);
  
  auto oldBreakBb = mLoopBreakBb;
  auto oldContinueBb = mLoopContinueBb;
  mLoopBreakBb = mergeBb;
  mLoopContinueBb = condBb;
  
  mCurIrb->CreateBr(bodyBb);
  
  // 处理循环体
  mCurIrb->SetInsertPoint(bodyBb);
  self(obj->body);
  if (!mCurIrb->GetInsertBlock()->getTerminator()) {
    mCurIrb->CreateBr(condBb);
  }
  
  // 处理条件判断
  mCurIrb->SetInsertPoint(condBb);
  auto condVal = self(obj->cond);
  llvm::Value* condBool = toBool(condVal);
  mCurIrb->CreateCondBr(condBool, bodyBb, mergeBb);
  
  // 设置合并块为当前插入点
  mCurIrb->SetInsertPoint(mergeBb);
  
  mLoopBreakBb = oldBreakBb;
  mLoopContinueBb = oldContinueBb;
}

// DeclStmt处理
void
EmitIR::operator()(DeclStmt* obj)
{
  for (auto decl : obj->decls) {
    self(decl);
  }
}

// 循环语句处理
void
EmitIR::operator()(WhileStmt* obj)
{
  auto condBb = llvm::BasicBlock::Create(mCtx, "cond", mCurFunc);
  auto bodyBb = llvm::BasicBlock::Create(mCtx, "body", mCurFunc);
  auto mergeBb = llvm::BasicBlock::Create(mCtx, "merge", mCurFunc);
  
  auto oldBreakBb = mLoopBreakBb;
  auto oldContinueBb = mLoopContinueBb;
  mLoopBreakBb = mergeBb;
  mLoopContinueBb = condBb;
  
  mCurIrb->CreateBr(condBb);
  
  // 处理条件判断
  mCurIrb->SetInsertPoint(condBb);
  auto condVal = self(obj->cond);
  llvm::Value* condBool = toBool(condVal);
  mCurIrb->CreateCondBr(condBool, bodyBb, mergeBb);
  
  // 处理循环体
  mCurIrb->SetInsertPoint(bodyBb);
  self(obj->body);
  if (!mCurIrb->GetInsertBlock()->getTerminator())
    mCurIrb->CreateBr(condBb);
  
  // 设置合并块为当前插入点
  mCurIrb->SetInsertPoint(mergeBb);
  
  mLoopBreakBb = oldBreakBb;
  mLoopContinueBb = oldContinueBb;
}

// break语句处理
void
EmitIR::operator()(BreakStmt* obj)
{
  if (mLoopBreakBb)
    mCurIrb->CreateBr(mLoopBreakBb);
}

// continue语句处理
 void
 EmitIR::operator()(ContinueStmt* obj)
 {
   if (mLoopContinueBb)
     mCurIrb->CreateBr(mLoopContinueBb);
 }
 
 // DeclStmt处理
 void
 EmitIR::operator()(CompoundStmt* obj)
{
  // TODO: 可以在此添加对符号重名的处理
  for (auto&& stmt : obj->subs)
    self(stmt);
}

void
EmitIR::operator()(ReturnStmt* obj)
{
  auto& irb = *mCurIrb;

  llvm::Value* retVal;
  if (!obj->expr)
    retVal = nullptr;
  else
    retVal = self(obj->expr);

  if (retVal && mCurFunc)
    retVal = castTo(retVal, mCurFunc->getReturnType());

  if (!mCurIrb->GetInsertBlock()->getTerminator())
    mCurIrb->CreateRet(retVal);

  auto exitBb = llvm::BasicBlock::Create(mCtx, "return_exit", mCurFunc);
  mCurIrb->SetInsertPoint(exitBb);
}

//==============================================================================
// 声明
//==============================================================================

void
EmitIR::operator()(Decl* obj)
{
  // 添加变量声明处理的跳转

  if (auto p = obj->dcst<FunctionDecl>())
    return self(p);

  if (auto p = obj->dcst<VarDecl>())
    return self(p);

  ABORT();
}

// 辅助函数：递归创建默认数组初始化器
llvm::Constant*
EmitIR::createDefaultArrayInit(llvm::Type* ty)
{
  if (auto arrTy = llvm::dyn_cast<llvm::ArrayType>(ty)) {
    auto elemTy = arrTy->getElementType();
    auto count = arrTy->getNumElements();
    std::vector<llvm::Constant*> elems;
    for (uint32_t i = 0; i < count; ++i) {
      elems.push_back(createDefaultArrayInit(elemTy));
    }
    return llvm::ConstantArray::get(arrTy, elems);
  }
  return llvm::ConstantInt::get(ty, 0);
}

llvm::Constant*
EmitIR::createArrayConstantInit(const asg::Type* type, asg::InitListExpr* init)
{
  auto llTy = self(type);
  auto arrTy = llvm::dyn_cast<llvm::ArrayType>(llTy);
  if (!arrTy)
    return llvm::ConstantInt::get(mIntTy, 0);

  auto elemTy = arrTy->getElementType();
  auto count = arrTy->getNumElements();

  std::vector<llvm::Constant*> values;
  std::vector<asg::Expr*> flat;
  flattenInitList(init, flat);
  for (std::size_t i = 0; i < count; ++i) {
    if (i < flat.size()) {
      values.push_back(constFromExpr(flat[i], elemTy));
    } else {
      values.push_back(createDefaultArrayInit(elemTy));
    }
  }
  return llvm::ConstantArray::get(arrTy, values);
}

llvm::Value*
EmitIR::getLValueAddr(asg::Expr* expr)
{
  if (auto ref = expr->dcst<DeclRefExpr>()) {
    auto var = ref->decl->dcst<VarDecl>();
    return static_cast<llvm::Value*>(var->any);
  }
  if (auto sub = expr->dcst<ArraySubscriptExpr>()) {
    return self(sub);
  }
  ABORT();
}

// 变量声明处理
void
EmitIR::operator()(VarDecl* obj)
{
  if (obj->type->texp->dcst<ArrayType>()) {
    auto llTy = self(obj->type);
    auto arrTy = llvm::dyn_cast<llvm::ArrayType>(llTy);
    if (!arrTy) {
      llvm::errs() << "VarDecl: type is not ArrayType: " << *llTy << "\n";
      ABORT();
    }
    auto elemTy = arrTy->getElementType();
    auto arrSize = arrTy->getNumElements();
    
    if (!hasInsertionPoint()) {
      // 全局数组
      llvm::Constant* initVal = nullptr;
      
      if (obj->init) {
        // 处理初始化列表
        if (auto initList = obj->init->dcst<InitListExpr>()) {
          initVal = createArrayConstantInit(obj->type, initList);
        } else if (auto intLit = obj->init->dcst<IntegerLiteral>()) {
          // 单个值初始化整个数组为相同值
          std::vector<llvm::Constant*> elems(arrSize, llvm::ConstantInt::get(elemTy, intLit->val));
          initVal = llvm::ConstantArray::get(llvm::ArrayType::get(elemTy, arrSize), elems);
        }
      }
      
      if (!initVal) {
        // 默认初始化为0
        initVal = createDefaultArrayInit(arrTy);
      }
      
      auto global = new llvm::GlobalVariable(mMod, arrTy, false, 
                                              llvm::GlobalVariable::InternalLinkage, 
                                              initVal, obj->name);
      obj->any = global;
    } else {
      // 局部数组 - 使用alloca
      auto alloca = mCurIrb->CreateAlloca(arrTy, nullptr, obj->name);
      obj->any = alloca;
      
      // 初始化数组
      if (obj->init) {
        if (auto initList = obj->init->dcst<InitListExpr>()) {
          std::vector<std::uint32_t> dims;
          collectArrayDims(obj->type, dims);
          std::vector<asg::Expr*> flat;
          flattenInitList(initList, flat);
          std::uint32_t total = 1;
          for (auto d : dims)
            total *= d;

          for (std::uint32_t linear = 0; linear < total; ++linear) {
            std::vector<llvm::Value*> indices;
            indices.push_back(llvm::ConstantInt::get(mIntTy, 0));
            std::uint32_t remain = linear;
            for (std::size_t di = 0; di < dims.size(); ++di) {
              std::uint32_t stride = 1;
              for (std::size_t dj = di + 1; dj < dims.size(); ++dj)
                stride *= dims[dj];
              std::uint32_t idx = remain / stride;
              remain = remain % stride;
              indices.push_back(llvm::ConstantInt::get(mIntTy, idx));
            }
            auto elemPtr = mCurIrb->CreateInBoundsGEP(arrTy, alloca, indices);
            llvm::Value* val = llvm::ConstantInt::get(mIntTy, 0);
            if (linear < flat.size()) {
              val = self(flat[linear]);
              val = toInt32(val);
            }
            mCurIrb->CreateStore(val, elemPtr);
          }
        }
      }
    }
    return;
  }
  
  if (hasInsertionPoint()) {
    // 局部变量分配（在函数内部，有有效的插入点）
    auto alloca = mCurIrb->CreateAlloca(self(obj->type), nullptr, obj->name);
    obj->any = alloca;
    
    // 变量初始化
    if (obj->init) {
      auto val = self(obj->init);
      val = castTo(val, self(obj->type));
      mCurIrb->CreateStore(val, alloca);
    }
  } else {
    // 全局变量处理
    llvm::GlobalVariable* global;
    if (obj->init) {
      // 有初始化器，创建带初始化器的全局变量
      global = new llvm::GlobalVariable(mMod, self(obj->type), false, llvm::GlobalVariable::ExternalLinkage, nullptr, obj->name);
      auto val = constFromExpr(obj->init, self(obj->type));
      global->setInitializer(val);
    } else {
      // 没有初始化器，创建全局变量，默认值为0
      auto zeroVal = llvm::ConstantInt::get(self(obj->type), 0);
      global = new llvm::GlobalVariable(mMod, self(obj->type), false, 
                                        llvm::GlobalVariable::CommonLinkage, 
                                        zeroVal, obj->name);
    }
    obj->any = global;
  }
}

void
EmitIR::operator()(FunctionDecl* obj)
{
  // 创建函数
  auto fty = llvm::dyn_cast<llvm::FunctionType>(self(obj->type));
  auto func = llvm::Function::Create(
    fty, llvm::GlobalVariable::ExternalLinkage, obj->name, mMod);

  obj->any = func;

  if (obj->body == nullptr)
    return;
  auto entryBb = llvm::BasicBlock::Create(mCtx, "entry", func);
  mCurIrb->SetInsertPoint(entryBb);
  auto& entryIrb = *mCurIrb;
  
  // 翻译函数体
  mCurFunc = func;
  
  // 添加对函数参数的处理
  unsigned i = 0;
  for (auto&& arg : func->args()) {
    arg.setName(obj->params[i]->name);
    auto* paramDecl = obj->params[i]->dcst<VarDecl>();
    if (paramDecl) {
      auto alloca = mCurIrb->CreateAlloca(self(paramDecl->type), nullptr, paramDecl->name);
      mCurIrb->CreateStore(castTo(&arg, self(paramDecl->type)), alloca);
      paramDecl->any = alloca;
    } else {
      obj->params[i]->any = &arg;
    }
    i++;
  }
  self(obj->body);
  auto& exitIrb = *mCurIrb;

  if (!exitIrb.GetInsertBlock()->getTerminator()) {
    if (fty->getReturnType()->isVoidTy())
      exitIrb.CreateRetVoid();
    else
      exitIrb.CreateUnreachable();
  }

  mCurFunc = nullptr;
  mCurIrb->ClearInsertionPoint();
}
