# Task 4 优化技术示例

本目录包含了基于YatCC Task 4优化技术的简化实现示例，每个示例都可以独立编译运行，无需依赖LLVM库。

## 快速开始

### 编译所有示例
```bash
cd task4_examples
g++ -std=c++17 01_constant_folding.cpp -o constant_folding
g++ -std=c++17 02_mem2reg.cpp -o mem2reg
g++ -std=c++17 03_static_call_counter.cpp -o static_call_counter
```

### 运行示例
```bash
./constant_folding      # 常量折叠优化
./mem2reg              # 内存到寄存器提升
./static_call_counter   # 静态调用计数器
```

## 优化技术列表

### 1. 常量折叠 (Constant Folding)
- **代码**: [01_constant_folding.cpp](task4_examples/01_constant_folding.cpp)
- **文档**: [01_constant_folding.md](task4_examples/01_constant_folding.md)
- **原理**: 在编译时计算常量表达式，替换运行时计算
- **效果**: 减少运行时开销，提高执行速度

### 2. 内存到寄存器提升 (Memory to Register Promotion)
- **代码**: [02_mem2reg.cpp](task4_examples/02_mem2reg.cpp)
- **文档**: [02_mem2reg.md](task4_examples/02_mem2reg.md)
- **原理**: 将栈内存变量提升到SSA形式的寄存器变量
- **效果**: 减少内存访问，为其他优化创造条件

### 3. 静态调用计数器 (Static Call Counter)
- **代码**: [03_static_call_counter.cpp](task4_examples/03_static_call_counter.cpp)
- **文档**: [03_static_call_counter.md](task4_examples/03_static_call_counter.md)
- **原理**: 在编译时统计函数调用次数
- **效果**: 识别热点函数，指导优化决策

## 详细文档

- [总体说明](task4_examples/README.md) - 项目详细说明和使用指南
- [实现总结](task4_examples/SUMMARY.md) - 技术实现总结和测试结果

## 技术特点

✅ **无LLVM依赖**: 所有实现使用标准C++17
✅ **可编译运行**: 每个示例都可以独立编译和运行
✅ **详细文档**: 每个优化都有完整的Markdown文档
✅ **教学友好**: 代码注释详细，适合学习使用

## 与YatCC的关系

这些示例对应YatCC Task 4中实现的优化Pass：

| 示例 | YatCC实现 | 说明 |
|------|-----------|------|
| 常量折叠 | ConstantFolding.hpp | 常量折叠优化 |
| Mem2Reg | Mem2Reg.hpp | 内存到寄存器提升 |
| 静态调用计数 | StaticCallCounter.hpp | 静态调用计数器 |

## 学习路径

1. 阅读 [task4_examples/README.md](task4_examples/README.md) 了解项目结构
2. 选择感兴趣的优化技术，阅读对应的.md文档
3. 编译并运行对应的.cpp文件，观察优化过程
4. 修改测试用例，深入理解优化原理
5. 参考 [task4_examples/SUMMARY.md](task4_examples/SUMMARY.md) 查看完整总结

## 注意事项

- 这些示例为了教学目的做了大量简化
- 真实编译器需要处理更多边界情况
- 实际实现需要考虑编译时间和优化效果的平衡
- 任何优化都必须保证程序语义不变

## 许可证

这些示例代码仅供学习使用，可以自由修改和分发。
