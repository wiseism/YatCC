#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <algorithm>

// 简化的值类型
class Value {
public:
    enum class Type { CONSTANT, VARIABLE, INSTRUCTION };
    
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

// 指令类型
enum class InstructionType {
    CALL,      // 函数调用
    ADD, SUB, MUL, DIV  // 算术运算
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
    
private:
    InstructionType type_;
    std::vector<Value*> operands_;
};

// 基本块
class BasicBlock {
public:
    void addInstruction(Instruction* inst) {
        instructions_.push_back(inst);
    }
    
    const std::vector<Instruction*>& getInstructions() const {
        return instructions_;
    }
    
private:
    std::vector<Instruction*> instructions_;
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

// 模块
class Module {
public:
    void addFunction(Function* func) {
        functions_.push_back(func);
    }
    
    const std::vector<Function*>& getFunctions() const {
        return functions_;
    }
    
private:
    std::vector<Function*> functions_;
};

// 静态调用计数器分析
class StaticCallCounter {
public:
    using Result = std::unordered_map<std::string, unsigned>;
    
    Result run(Module& module) {
        Result result;
        
        std::cout << "=== 静态调用计数分析开始 ===" << std::endl;
        
        for (auto* func : module.getFunctions()) {
            std::cout << "分析函数: " << func->getName() << std::endl;
            
            for (auto* bb : func->getBasicBlocks()) {
                for (auto* inst : bb->getInstructions()) {
                    // 检查是否为调用指令
                    if (auto* callInst = dynamic_cast<Instruction*>(inst)) {
                        if (callInst->getOpcode() == InstructionType::CALL) {
                            // 获取被调用函数
                            if (callInst->getOperands().size() > 0) {
                                auto* calledFunc = callInst->getOperands()[0];
                                
                                // 检查是否为函数（不是常量或变量）
                                if (calledFunc->getType() == Value::Type::VARIABLE) {
                                    std::string funcName = calledFunc->getName();
                                    
                                    // 统计调用次数
                                    result[funcName]++;
                                    
                                    std::cout << "  发现调用: " << funcName 
                                              << " (当前计数: " << result[funcName] 
                                              << ")" << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        std::cout << "=== 静态调用计数分析完成 ===" << std::endl;
        return result;
    }
};

// 静态调用计数器打印器
class StaticCallCounterPrinter {
public:
    void print(const StaticCallCounter::Result& result) {
        std::cout << "\n=== 函数调用统计结果 ===" << std::endl;
        
        if (result.empty()) {
            std::cout << "未发现任何函数调用" << std::endl;
            return;
        }
        
        // 按调用次数排序
        std::vector<std::pair<std::string, unsigned>> sortedResults;
        for (const auto& entry : result) {
            sortedResults.push_back(entry);
        }
        
        std::sort(sortedResults.begin(), sortedResults.end(),
                 [](const auto& a, const auto& b) {
                     return a.second > b.second;  // 降序排列
                 });
        
        // 打印统计结果
        std::cout << "函数名\t调用次数" << std::endl;
        std::cout << "----------------" << std::endl;
        
        for (const auto& entry : sortedResults) {
            std::cout << entry.first << "\t" << entry.second << std::endl;
        }
        
        // 打印统计信息
        unsigned totalCalls = 0;
        for (const auto& entry : result) {
            totalCalls += entry.second;
        }
        
        std::cout << "----------------" << std::endl;
        std::cout << "总计: " << result.size() << " 个不同函数被调用" << std::endl;
        std::cout << "总调用次数: " << totalCalls << std::endl;
        std::cout << "平均调用次数: " << (double)totalCalls / result.size() << std::endl;
    }
};

int main() {
    // 创建一个简单的模块来演示静态调用计数
    Module module;
    
    // 创建主函数
    auto* mainFunc = new Function("main");
    auto* mainBB = new BasicBlock();
    
    // 创建一些辅助函数
    auto* helper1Func = new Function("helper1");
    auto* helper1BB = new BasicBlock();
    auto* helper2Func = new Function("helper2");
    auto* helper2BB = new BasicBlock();
    auto* helper3Func = new Function("helper3");
    auto* helper3BB = new BasicBlock();
    
    // 在main函数中调用辅助函数
    // 调用helper1三次
    for (int i = 0; i < 3; i++) {
        auto* call1 = new Instruction(InstructionType::CALL, "call_helper1_" + std::to_string(i));
        call1->addOperand(new Variable("helper1"));
        mainBB->addInstruction(call1);
    }
    
    // 调用helper2两次
    for (int i = 0; i < 2; i++) {
        auto* call2 = new Instruction(InstructionType::CALL, "call_helper2_" + std::to_string(i));
        call2->addOperand(new Variable("helper2"));
        mainBB->addInstruction(call2);
    }
    
    // 调用helper3五次
    for (int i = 0; i < 5; i++) {
        auto* call3 = new Instruction(InstructionType::CALL, "call_helper3_" + std::to_string(i));
        call3->addOperand(new Variable("helper3"));
        mainBB->addInstruction(call3);
    }
    
    // 在helper1函数中调用helper2
    auto* callInHelper1 = new Instruction(InstructionType::CALL, "call_in_helper1");
    callInHelper1->addOperand(new Variable("helper2"));
    helper1BB->addInstruction(callInHelper1);
    
    // 在helper2函数中调用helper3
    auto* callInHelper2 = new Instruction(InstructionType::CALL, "call_in_helper2");
    callInHelper2->addOperand(new Variable("helper3"));
    helper2BB->addInstruction(callInHelper2);
    
    // 添加基本块到函数
    mainFunc->addBasicBlock(mainBB);
    helper1Func->addBasicBlock(helper1BB);
    helper2Func->addBasicBlock(helper2BB);
    helper3Func->addBasicBlock(helper3BB);
    
    // 添加函数到模块
    module.addFunction(mainFunc);
    module.addFunction(helper1Func);
    module.addFunction(helper2Func);
    module.addFunction(helper3Func);
    
    // 运行静态调用计数分析
    StaticCallCounter counter;
    auto result = counter.run(module);
    
    // 打印结果
    StaticCallCounterPrinter printer;
    printer.print(result);
    
    return 0;
}
