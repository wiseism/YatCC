#include "EmitIR.hpp"
#include <llvm/Transforms/Utils/ModuleUtils.h>

#define self (*this)

using namespace asg;

EmitIR::EmitIR(Obj::Mgr& mgr, llvm::LLVMContext& ctx, llvm::StringRef mid)
  : mMgr(mgr)
  , mMod(mid, ctx)
  , mCtx(ctx)
  , mIntTy(llvm::Type::getInt32Ty(ctx))
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
      case Type::Spec::kInt:
        return llvm::Type::getInt32Ty(mCtx);
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

llvm::Constant*
EmitIR::operator()(IntegerLiteral* obj)
{
  return llvm::ConstantInt::get(self(obj->type), obj->val);
}

// 变量引用表达式处理
llvm::Value*
EmitIR::operator()(DeclRefExpr* obj)
{
  if (auto var = obj->decl->dcst<VarDecl>()) {
    if (var->type->texp->dcst<ArrayType>()) {
      // 数组名作为指针
      return static_cast<llvm::Value*>(var->any);
    }
    if (mCurFunc) {
      // 局部变量或函数内引用全局变量
      return mCurIrb->CreateLoad(self(obj->type), static_cast<llvm::Value*>(var->any));
    } else {
      // 全局变量初始化时引用其他全局变量，直接返回全局变量指针
      // 但我们需要确保返回的是一个Constant
      auto global = static_cast<llvm::GlobalVariable*>(var->any);
      return global;
    }
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
  auto rht = self(obj->rht);
  
  switch (obj->op) {
    case BinaryExpr::kAdd:
      return mCurIrb->CreateAdd(lft, rht);
    case BinaryExpr::kSub:
      return mCurIrb->CreateSub(lft, rht);
    case BinaryExpr::kMul:
      return mCurIrb->CreateMul(lft, rht);
    case BinaryExpr::kDiv:
      return mCurIrb->CreateSDiv(lft, rht);
    case BinaryExpr::kMod:
      return mCurIrb->CreateSRem(lft, rht);
    case BinaryExpr::kLt:
      return mCurIrb->CreateICmpSLT(lft, rht);
    case BinaryExpr::kGt:
      return mCurIrb->CreateICmpSGT(lft, rht);
    case BinaryExpr::kLe:
      return mCurIrb->CreateICmpSLE(lft, rht);
    case BinaryExpr::kGe:
      return mCurIrb->CreateICmpSGE(lft, rht);
    case BinaryExpr::kEq:
      return mCurIrb->CreateICmpEQ(lft, rht);
    case BinaryExpr::kNe:
      return mCurIrb->CreateICmpNE(lft, rht);
    case BinaryExpr::kAnd:
      return mCurIrb->CreateAnd(lft, rht);
    case BinaryExpr::kOr:
      return mCurIrb->CreateOr(lft, rht);
    case BinaryExpr::kAssign:
      if (auto ref = obj->lft->dcst<DeclRefExpr>()) {
        auto var = ref->decl->dcst<VarDecl>();
        mCurIrb->CreateStore(rht, static_cast<llvm::Value*>(var->any));
        return rht;
      }
      ABORT();
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
      return sub;
    case UnaryExpr::kNeg:
      return mCurIrb->CreateNeg(sub);
    case UnaryExpr::kNot:
      return mCurIrb->CreateNot(sub);
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
  return self(obj->sub);
}

// 数组下标访问处理
llvm::Value*
EmitIR::operator()(ArraySubscriptExpr* obj)
{
  auto baseVal = self(obj->base);
  auto idxVal = self(obj->idx);
  
  // 检查是否在函数上下文中
  if (mCurFunc && mCurIrb->GetInsertBlock()) {
    // 创建GEP指令获取元素指针
    auto ptr = mCurIrb->CreateGEP(mIntTy, baseVal, idxVal);
    
    // 检查表达式类型是否为指针类型
    // 如果是指针类型，返回指针（用于嵌套数组访问）
    // 否则，加载值并返回
    auto exprType = self(obj->type);
    if (llvm::dyn_cast<llvm::PointerType>(exprType)) {
      return ptr;
    } else {
      return mCurIrb->CreateLoad(mIntTy, ptr);
    }
  } else {
    // 在全局变量初始化时，我们需要返回一个常量
    // 对于复杂的数组访问，暂时返回0
    return llvm::ConstantInt::get(mIntTy, 0);
  }
}

// 函数调用处理
llvm::Value*
EmitIR::operator()(CallExpr* obj)
{
  ABORT();
}

// 初始化列表处理
llvm::Value*
EmitIR::operator()(InitListExpr* obj)
{
  if (obj->list.empty())
    ABORT();
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
  llvm::Value* condBool;
  
  auto condTy = condVal->getType();
  if (condTy->isIntegerTy(1)) {
    condBool = condVal;
  } else if (condTy->isIntegerTy()) {
    condBool = mCurIrb->CreateICmpNE(condVal, llvm::ConstantInt::get(condTy, 0));
  } else if (condTy->isPointerTy()) {
    condBool = mCurIrb->CreateICmpNE(condVal, llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(condTy)));
  } else {
    condBool = condVal;
  }
  
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
  llvm::Value* condBool;
  
  auto condTy = condVal->getType();
  if (condTy->isIntegerTy(1)) {
    condBool = condVal;
  } else if (condTy->isIntegerTy()) {
    condBool = mCurIrb->CreateICmpNE(condVal, llvm::ConstantInt::get(condTy, 0));
  } else if (condTy->isPointerTy()) {
    condBool = mCurIrb->CreateICmpNE(condVal, llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(condTy)));
  } else {
    condBool = condVal;
  }
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
  llvm::Value* condBool;
  
  auto condTy = condVal->getType();
  if (condTy->isIntegerTy(1)) {
    condBool = condVal;
  } else if (condTy->isIntegerTy()) {
    condBool = mCurIrb->CreateICmpNE(condVal, llvm::ConstantInt::get(condTy, 0));
  } else if (condTy->isPointerTy()) {
    condBool = mCurIrb->CreateICmpNE(condVal, llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(condTy)));
  } else {
    condBool = condVal;
  }
  mCurIrb->CreateCondBr(condBool, bodyBb, mergeBb);
  
  // 处理循环体
  mCurIrb->SetInsertPoint(bodyBb);
  self(obj->body);
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
  mCurIrb->CreateBr(mLoopBreakBb);
}

// continue语句处理
 void
 EmitIR::operator()(ContinueStmt* obj)
 {
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
    
    if (!mCurFunc || !mCurIrb->GetInsertBlock()) {
      // 全局数组
      llvm::Constant* initVal = nullptr;
      
      if (obj->init) {
        // 处理初始化列表
        if (auto initList = obj->init->dcst<InitListExpr>()) {
          std::vector<llvm::Constant*> elems;
          for (size_t i = 0; i < initList->list.size() && i < arrSize; ++i) {
            if (auto intLit = initList->list[i]->dcst<IntegerLiteral>()) {
              elems.push_back(llvm::ConstantInt::get(elemTy, intLit->val));
            } else {
              elems.push_back(llvm::ConstantInt::get(elemTy, 0));
            }
          }
          // 补齐剩余元素为0
          while (elems.size() < arrSize) {
            elems.push_back(llvm::ConstantInt::get(elemTy, 0));
          }
          initVal = llvm::ConstantArray::get(llvm::ArrayType::get(elemTy, elems.size()), elems);
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
          for (size_t i = 0; i < initList->list.size() && i < arrSize; ++i) {
            auto idx = llvm::ConstantInt::get(mIntTy, i);
            auto ptr = mCurIrb->CreateInBoundsGEP(elemTy, alloca, {llvm::ConstantInt::get(mIntTy, 0), idx});
            auto val = self(initList->list[i]);
            mCurIrb->CreateStore(val, ptr);
          }
        }
      }
    }
    return;
  }
  
  if (mCurFunc && mCurIrb->GetInsertBlock()) {
    // 局部变量分配（在函数内部，有有效的插入点）
    auto alloca = mCurIrb->CreateAlloca(self(obj->type), nullptr, obj->name);
    obj->any = alloca;
    
    // 变量初始化
    if (obj->init) {
      auto val = self(obj->init);
      mCurIrb->CreateStore(val, alloca);
    }
  } else {
    // 全局变量处理
    llvm::GlobalVariable* global;
    if (obj->init) {
      // 有初始化器，创建带初始化器的全局变量
      global = new llvm::GlobalVariable(mMod, self(obj->type), false, llvm::GlobalVariable::ExternalLinkage, nullptr, obj->name);
      // 对于简单的全局变量初始化（只有IntegerLiteral），我们可以直接处理
      if (auto intLit = obj->init->dcst<IntegerLiteral>()) {
        auto val = llvm::ConstantInt::get(self(obj->type), intLit->val);
        global->setInitializer(val);
      } else {
        // 对于复杂的初始化表达式（引用其他全局变量等），跳过
      }
    } else {
      // 没有初始化器，创建外部全局变量声明
      global = new llvm::GlobalVariable(mMod, self(obj->type), false, llvm::GlobalVariable::ExternalLinkage, nullptr, obj->name);
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
    obj->params[i]->any = &arg;
    i++;
  }
  self(obj->body);
  auto& exitIrb = *mCurIrb;

  if (fty->getReturnType()->isVoidTy())
    exitIrb.CreateRetVoid();
  else
    exitIrb.CreateUnreachable();
}
