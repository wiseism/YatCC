#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

// 简化的指令类型枚举
enum class InstructionType {
    ADD,
    SUB,
    MUL,
    DIV,
    LOAD,
    STORE,
    CALL
};

// 简化的值类型
class Value {
public:
    enum class Type { CONSTANT, VARIABLE, INSTRUCTION };
    
    Value(Type type, const std::string& name = "")
        : type_(type), name_(name) {}
    
    Type getType() const { return type_; }
    std::string getName() const { return name_; }
    bool isConstant() const { return type_ == Type::CONSTANT; }
    
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

// 指令
class Instruction : public Value {
public:
    Instruction(InstructionType type, const std::string& name = "")
        : Value(Type::INSTRUCTION, name), type_(type) {}
    
    InstructionType getOpcode() const { return type_; }
    
    void addOperand(Value* operand) {
        operands_.push_back(operand);
    }
    
    const std::vector<Value*>& getOperands() const { return operands_; }
    
    void replaceAllUsesWith(Value* newValue) {
        // 在实际编译器中，这里会替换所有使用此指令的地方
        std::cout << "  替换指令 " << getName() << " 的所有使用为 " 
                  << newValue->getName() << std::endl;
    }
    
private:
    InstructionType type_;
    std::vector<Value*> operands_;
};

// 基本块
class BasicBlock {
public:
    void addInstruction(std::unique_ptr<Instruction> inst) {
        instructions_.push_back(std::move(inst));
    }
    
    const std::vector<std::unique_ptr<Instruction>>& getInstructions() const {
        return instructions_;
    }
    
private:
    std::vector<std::unique_ptr<Instruction>> instructions_;
};

// 函数
class Function {
public:
    Function(const std::string& name) : name_(name) {}
    
    void addBasicBlock(std::unique_ptr<BasicBlock> bb) {
        basicBlocks_.push_back(std::move(bb));
    }
    
    const std::vector<std::unique_ptr<BasicBlock>>& getBasicBlocks() const {
        return basicBlocks_;
    }
    
    std::string getName() const { return name_; }
    
private:
    std::string name_;
    std::vector<std::unique_ptr<BasicBlock>> basicBlocks_;
};

// 模块
class Module {
public:
    void addFunction(std::unique_ptr<Function> func) {
        functions_.push_back(std::move(func));
    }
    
    const std::vector<std::unique_ptr<Function>>& getFunctions() const {
        return functions_;
    }
    
private:
    std::vector<std::unique_ptr<Function>> functions_;
};

// 常量折叠优化Pass
class ConstantFolding {
public:
    void run(Module& module) {
        int foldCount = 0;
        
        std::cout << "=== 常量折叠优化开始 ===" << std::endl;
        
        for (auto& func : module.getFunctions()) {
            std::cout << "处理函数: " << func->getName() << std::endl;
            
            for (auto& bb : func->getBasicBlocks()) {
                std::vector<Instruction*> toRemove;
                
                for (auto& inst : bb->getInstructions()) {
                    if (auto* binOp = dynamic_cast<Instruction*>(inst.get())) {
                        // 检查是否为二元运算指令
                        if (binOp->getOperands().size() == 2) {
                            auto* lhs = binOp->getOperands()[0];
                            auto* rhs = binOp->getOperands()[1];
                            
                            // 检查两个操作数是否都是常量
                            auto* constLhs = dynamic_cast<Constant*>(lhs);
                            auto* constRhs = dynamic_cast<Constant*>(rhs);
                            
                            if (constLhs && constRhs) {
                                int result = 0;
                                bool canFold = true;
                                
                                switch (binOp->getOpcode()) {
                                    case InstructionType::ADD:
                                        result = constLhs->getValue() + constRhs->getValue();
                                        std::cout << "  折叠: " << constLhs->getValue() 
                                          << " + " << constRhs->getValue() 
                                          << " = " << result << std::endl;
                                        break;
                                    case InstructionType::SUB:
                                        result = constLhs->getValue() - constRhs->getValue();
                                        std::cout << "  折叠: " << constLhs->getValue() 
                                          << " - " << constRhs->getValue() 
                                          << " = " << result << std::endl;
                                        break;
                                    case InstructionType::MUL:
                                        result = constLhs->getValue() * constRhs->getValue();
                                        std::cout << "  折叠: " << constLhs->getValue() 
                                          << " * " << constRhs->getValue() 
                                          << " = " << result << std::endl;
                                        break;
                                    case InstructionType::DIV:
                                        if (constRhs->getValue() != 0) {
                                            result = constLhs->getValue() / constRhs->getValue();
                                            std::cout << "  折叠: " << constLhs->getValue() 
                                                  << " / " << constRhs->getValue() 
                                                  << " = " << result << std::endl;
                                        } else {
                                            canFold = false;
                                            std::cout << "  跳过: 除数为零" << std::endl;
                                        }
                                        break;
                                    default:
                                        canFold = false;
                                        break;
                                }
                                
                                if (canFold) {
                                    // 创建新的常量
                                    auto* newConst = new Constant(result);
                                    // 替换所有使用
                                    binOp->replaceAllUsesWith(newConst);
                                    toRemove.push_back(binOp);
                                    foldCount++;
                                }
                            }
                        }
                    }
                }
                
                // 删除被折叠的指令
                for (auto* inst : toRemove) {
                    std::cout << "  删除指令: " << inst->getName() << std::endl;
                }
            }
        }
        
        std::cout << "=== 常量折叠优化完成，共折叠 " << foldCount 
                  << " 个指令 ===" << std::endl << std::endl;
    }
};

int main() {
    // 创建一个简单的模块
    Module module;
    
    // 创建函数
    auto func = std::make_unique<Function>("example");
    auto bb = std::make_unique<BasicBlock>();
    
    // 创建一些指令来演示常量折叠
    // 示例1: 3 + 5 = 8
    auto add1 = std::make_unique<Instruction>(InstructionType::ADD, "add1");
    add1->addOperand(new Constant(3));
    add1->addOperand(new Constant(5));
    bb->addInstruction(std::move(add1));
    
    // 示例2: 10 - 2 = 8
    auto sub1 = std::make_unique<Instruction>(InstructionType::SUB, "sub1");
    sub1->addOperand(new Constant(10));
    sub1->addOperand(new Constant(2));
    bb->addInstruction(std::move(sub1));
    
    // 示例3: 4 * 6 = 24
    auto mul1 = std::make_unique<Instruction>(InstructionType::MUL, "mul1");
    mul1->addOperand(new Constant(4));
    mul1->addOperand(new Constant(6));
    bb->addInstruction(std::move(mul1));
    
    // 示例4: 20 / 4 = 5
    auto div1 = std::make_unique<Instruction>(InstructionType::DIV, "div1");
    div1->addOperand(new Constant(20));
    div1->addOperand(new Constant(4));
    bb->addInstruction(std::move(div1));
    
    // 示例5: 不能折叠的运算（包含变量）
    auto add2 = std::make_unique<Instruction>(InstructionType::ADD, "add2");
    add2->addOperand(new Constant(10));
    add2->addOperand(new Variable("x"));
    bb->addInstruction(std::move(add2));
    
    func->addBasicBlock(std::move(bb));
    module.addFunction(std::move(func));
    
    // 运行常量折叠优化
    ConstantFolding folder;
    folder.run(module);
    
    return 0;
}
