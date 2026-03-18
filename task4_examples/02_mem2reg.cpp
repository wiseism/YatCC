#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>

// 简化的值类型
class Value {
public:
    enum class Type { CONSTANT, VARIABLE, PHI };
    
    Value(Type type, const std::string& name = "")
        : type_(type), name_(name) {}
    
    Type getType() const { return type_; }
    std::string getName() const { return name_; }
    
    virtual ~Value() = default;
    
protected:
    Type type_;
    std::string name_;
};

// 常量值
class Constant : public Value {
public:
    Constant(int value) : Value(Type::CONSTANT, std::to_string(value)), value_(value) {}
    int getValue() const { return value_; }
    
private:
    int value_;
};

// 变量
class Variable : public Value {
public:
    Variable(const std::string& name) : Value(Type::VARIABLE, name) {}
};

// PHI节点（用于SSA形式）
class PhiNode : public Value {
public:
    PhiNode(const std::string& name) : Value(Type::PHI, name) {}
    
    void addIncoming(Value* value, const std::string& block) {
        incoming_[block] = value;
    }
    
    const std::unordered_map<std::string, Value*>& getIncoming() const {
        return incoming_;
    }
    
private:
    std::unordered_map<std::string, Value*> incoming_;
};

// 指令类型
enum class InstructionType {
    ALLOCA,    // 分配栈内存
    STORE,     // 存储到内存
    LOAD,      // 从内存加载
    ADD, SUB, MUL, DIV  // 算术运算
};

// 指令
class Instruction : public Value {
public:
    Instruction(InstructionType type, const std::string& name = "")
        : Value(Type::VARIABLE, name), type_(type) {}
    
    InstructionType getOpcode() const { return type_; }
    
    void addOperand(Value* operand) {
        operands_.push_back(operand);
    }
    
    const std::vector<Value*>& getOperands() const { return operands_; }
    
private:
    InstructionType type_;
    std::vector<Value*> operands_;
};

// 基本块
class BasicBlock {
public:
    BasicBlock(const std::string& name) : name_(name) {}
    
    void addInstruction(Instruction* inst) {
        instructions_.push_back(inst);
    }
    
    const std::vector<Instruction*>& getInstructions() const {
        return instructions_;
    }
    
    void addPredecessor(BasicBlock* pred) {
        predecessors_.push_back(pred);
    }
    
    const std::vector<BasicBlock*>& getPredecessors() const {
        return predecessors_;
    }
    
    std::string getName() const { return name_; }
    
private:
    std::string name_;
    std::vector<Instruction*> instructions_;
    std::vector<BasicBlock*> predecessors_;
};

// 函数
class Function {
public:
    Function(const std::string& name) : name_(name) {}
    
    void addBasicBlock(BasicBlock* bb) {
        basicBlocks_.push_back(bb);
    }
    
    const std::vector<BasicBlock*>& getBasicBlocks() const {
        return basicBlocks_;
    }
    
    std::string getName() const { return name_; }
    
private:
    std::string name_;
    std::vector<BasicBlock*> basicBlocks_;
};

// 内存到寄存器提升优化
class Mem2Reg {
public:
    void run(Function& func) {
        std::cout << "=== 内存到寄存器提升优化开始 ===" << std::endl;
        std::cout << "处理函数: " << func.getName() << std::endl;
        
        // 第一步：识别可以提升的alloca指令
        std::vector<Instruction*> allocasToPromote;
        identifyPromotableAllocas(func, allocasToPromote);
        
        std::cout << "找到 " << allocasToPromote.size() 
                  << " 个可提升的alloca指令" << std::endl;
        
        // 第二步：为每个alloca插入PHI节点
        for (auto* alloca : allocasToPromote) {
            insertPhiNodes(alloca, func);
        }
        
        // 第三步：重命名变量（SSA重命名）
        performSSARename(func, allocasToPromote);
        
        // 第四步：删除alloca和相关的load/store指令
        removeAllocasAndMemOps(allocasToPromote);
        
        std::cout << "=== 内存到寄存器提升优化完成 ===" << std::endl << std::endl;
    }
    
private:
    // 识别可以提升的alloca指令
    void identifyPromotableAllocas(Function& func, 
                                   std::vector<Instruction*>& allocas) {
        for (auto* bb : func.getBasicBlocks()) {
            for (auto* inst : bb->getInstructions()) {
                if (inst->getOpcode() == InstructionType::ALLOCA) {
                    // 检查这个alloca是否只被简单的load/store使用
                    if (isAllocaPromotable(inst)) {
                        allocas.push_back(inst);
                        std::cout << "  可提升的alloca: " << inst->getName() << std::endl;
                    }
                }
            }
        }
    }
    
    // 检查alloca是否可以提升
    bool isAllocaPromotable(Instruction* alloca) {
        // 在实际实现中，这里会检查：
        // 1. 所有使用都是load/store指令
        // 2. 没有取地址操作
        // 3. 不是volatile的
        // 这里简化处理，假设所有alloca都可以提升
        return true;
    }
    
    // 插入PHI节点
    void insertPhiNodes(Instruction* alloca, Function& func) {
        std::cout << "  为alloca " << alloca->getName() 
                  << " 插入PHI节点" << std::endl;
        
        // 在实际实现中，这里会：
        // 1. 计算支配边界
        // 2. 在需要的基本块中插入PHI节点
        // 3. PHI节点合并来自不同前驱块的值
        
        // 简化版本：在函数入口创建一个PHI节点
        auto* phi = new PhiNode(alloca->getName() + "_phi");
        phiNodes_[alloca] = phi;
    }
    
    // 执行SSA重命名
    void performSSARename(Function& func, 
                      const std::vector<Instruction*>& allocas) {
        std::cout << "  执行SSA重命名" << std::endl;
        
        // 为每个alloca维护一个版本号栈
        std::unordered_map<Instruction*, std::stack<Value*> > versionStacks;
        
        // 初始化版本栈
        for (auto* alloca : allocas) {
            versionStacks[alloca].push(new Constant(0)); // 初始值为0
        }
        
        // 遍历所有基本块，重命名load/store
        for (auto* bb : func.getBasicBlocks()) {
            // 在块开始时，处理PHI节点
            for (auto* inst : bb->getInstructions()) {
                if (auto* phi = dynamic_cast<PhiNode*>(inst)) {
                    // PHI节点创建新的版本
                    for (auto* alloca : allocas) {
                        if (phi->getName().find(alloca->getName()) != std::string::npos) {
                            auto* newVersion = new Variable(alloca->getName() + "_v1");
                            versionStacks[alloca].push(newVersion);
                            std::cout << "    PHI创建新版本: " 
                                      << newVersion->getName() << std::endl;
                        }
                    }
                }
            }
            
            // 重命名load指令
            for (auto* inst : bb->getInstructions()) {
                if (inst->getOpcode() == InstructionType::LOAD) {
                    auto* loadedVar = inst->getOperands()[0];
                    // 检查是否是我们要提升的alloca
                    for (auto* alloca : allocas) {
                        if (loadedVar->getName() == alloca->getName()) {
                            // 用栈顶的版本替换load
                            auto* currentVersion = versionStacks[alloca].top();
                            std::cout << "    替换load " << inst->getName() 
                                      << " 为版本 " << currentVersion->getName() 
                                      << std::endl;
                            break;
                        }
                    }
                }
                
                // 重命名store指令
                if (inst->getOpcode() == InstructionType::STORE) {
                    auto* storedVar = inst->getOperands()[1];
                    // 检查是否是我们要提升的alloca
                    for (auto* alloca : allocas) {
                        if (storedVar->getName() == alloca->getName()) {
                            // 创建新版本
                            auto* newVersion = new Variable(alloca->getName() + "_v" + 
                                                       std::to_string(versionStacks[alloca].size()));
                            versionStacks[alloca].push(newVersion);
                            std::cout << "    Store创建新版本: " 
                                      << newVersion->getName() << std::endl;
                            
                            // 用新版本替换store的目标
                            break;
                        }
                    }
                }
            }
        }
    }
    
    // 删除alloca和相关的load/store指令
    void removeAllocasAndMemOps(const std::vector<Instruction*>& allocas) {
        std::cout << "  删除alloca和内存操作指令" << std::endl;
        
        for (auto* alloca : allocas) {
            std::cout << "    删除alloca: " << alloca->getName() << std::endl;
        }
    }
    
    std::unordered_map<Instruction*, PhiNode*> phiNodes_;
};

int main() {
    // 创建一个简单的函数来演示Mem2Reg
    Function func("example");
    
    // 创建基本块
    auto* entryBB = new BasicBlock("entry");
    auto* thenBB = new BasicBlock("then");
    auto* elseBB = new BasicBlock("else");
    auto* mergeBB = new BasicBlock("merge");
    
    // 设置控制流关系
    mergeBB->addPredecessor(thenBB);
    mergeBB->addPredecessor(elseBB);
    
    // 在entry块中创建alloca
    auto* allocaInst = new Instruction(InstructionType::ALLOCA, "x");
    entryBB->addInstruction(allocaInst);
    
    // 在entry块中存储初始值
    auto* store1 = new Instruction(InstructionType::STORE, "store1");
    store1->addOperand(new Constant(10));
    store1->addOperand(new Variable("x"));
    entryBB->addInstruction(store1);
    
    // 在then块中修改x
    auto* store2 = new Instruction(InstructionType::STORE, "store2");
    store2->addOperand(new Constant(20));
    store2->addOperand(new Variable("x"));
    thenBB->addInstruction(store2);
    
    // 在else块中修改x
    auto* store3 = new Instruction(InstructionType::STORE, "store3");
    store3->addOperand(new Constant(30));
    store3->addOperand(new Variable("x"));
    elseBB->addInstruction(store3);
    
    // 在merge块中加载x
    auto* load1 = new Instruction(InstructionType::LOAD, "load1");
    load1->addOperand(new Variable("x"));
    mergeBB->addInstruction(load1);
    
    // 添加基本块到函数
    func.addBasicBlock(entryBB);
    func.addBasicBlock(thenBB);
    func.addBasicBlock(elseBB);
    func.addBasicBlock(mergeBB);
    
    // 运行Mem2Reg优化
    Mem2Reg optimizer;
    optimizer.run(func);
    
    return 0;
}
