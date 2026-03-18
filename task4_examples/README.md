# Task 4 优化技术示例

本目录包含了Task 4中涉及的主要编译优化技术的简化实现示例，每个示例都可以独立编译运行，无需依赖LLVM库。

## 目录结构

```
task4_examples/
├── README.md                           # 本文件
├── 01_constant_folding.cpp              # 常量折叠优化
├── 01_constant_folding.md              # 常量折叠详细说明
├── 02_mem2reg.cpp                    # 内存到寄存器提升
├── 02_mem2reg.md                    # Mem2Reg详细说明
├── 03_static_call_counter.cpp          # 静态调用计数器
└── 03_static_call_counter.md          # 静态调用计数器详细说明
```

## 优化技术概览

### 1. 常量折叠 (Constant Folding)
- **文件**: `01_constant_folding.cpp`
- **说明**: `01_constant_folding.md`
- **原理**: 在编译时计算常量表达式，替换运行时计算
- **优势**: 减少运行时开销，提高执行速度
- **编译**: `g++ -std=c++17 01_constant_folding.cpp -o constant_folding`

### 2. 内存到寄存器提升 (Memory to Register Promotion)
- **文件**: `02_mem2reg.cpp`
- **说明**: `02_mem2reg.md`
- **原理**: 将栈内存变量提升到SSA形式的寄存器变量
- **优势**: 减少内存访问，为其他优化创造条件
- **编译**: `g++ -std=c++17 02_mem2reg.cpp -o mem2reg`

### 3. 静态调用计数器 (Static Call Counter)
- **文件**: `03_static_call_counter.cpp`
- **说明**: `03_static_call_counter.md`
- **原理**: 在编译时统计函数调用次数
- **优势**: 识别热点函数，指导优化决策
- **编译**: `g++ -std=c++17 03_static_call_counter.cpp -o static_call_counter`

## 快速开始

### 编译所有示例
```bash
# 编译常量折叠示例
g++ -std=c++17 01_constant_folding.cpp -o constant_folding

# 编译Mem2Reg示例
g++ -std=c++17 02_mem2reg.cpp -o mem2reg

# 编译静态调用计数器示例
g++ -std=c++17 03_static_call_counter.cpp -o static_call_counter
```

### 运行示例
```bash
# 运行常量折叠
./constant_folding

# 运行Mem2Reg
./mem2reg

# 运行静态调用计数器
./static_call_counter
```

## 学习路径建议

### 初学者路径
1. 先阅读每个`.md`文件理解优化原理
2. 运行对应的`.cpp`文件观察优化过程
3. 修改代码中的测试用例，观察不同情况下的行为
4. 尝试添加新的优化场景

### 进阶学习路径
1. 对比简化实现与LLVM实际实现的差异
2. 思考如何处理更复杂的情况（如循环、嵌套调用等）
3. 研究优化之间的相互影响（如常量折叠后的代码如何影响Mem2Reg）
4. 探索其他相关优化技术

## 与LLVM的对应关系

这些简化示例模拟了LLVM中的真实Pass：

| 简化实现 | LLVM Pass | 说明 |
|-----------|------------|------|
| ConstantFolding | `llvm::ConstantFold` | 常量折叠 |
| Mem2Reg | `llvm::PromoteMemoryToRegister` | 内存到寄存器提升 |
| StaticCallCounter | `llvm::CallGraph` | 调用图分析 |

## 优化效果对比

### 常量折叠效果
```
优化前:  x = 3 + 5 * 2    // 2次运行时计算
优化后:  x = 13            // 编译时计算完成
```

### Mem2Reg效果
```
优化前:  alloca x; store 10, x; load x, use x    // 内存访问
优化后:  x_1 = 10; use x_1                      // 寄存器访问
```

### 静态调用计数器效果
```
分析结果: helper函数被调用15次，是热点函数
优化建议: 考虑内联helper函数或进行性能优化
```

## 扩展阅读

### 推荐资源
- [LLVM Language Reference](https://llvm.org/docs/LangRef.html)
- [SSA Form](https://en.wikipedia.org/wiki/Static_single_assignment_form)
- [Compiler Optimization](https://en.wikipedia.org/wiki/Compiler_optimization)

### 相关论文
- "SSA-based Compiler Design" - Ron Cytron et al.
- "Effective SSA-based Compiler Optimizations" - various authors

## 注意事项

1. **简化假设**: 这些示例为了教学目的做了大量简化
2. **实际复杂性**: 真实编译器需要处理更多边界情况
3. **性能考虑**: 实际实现需要考虑编译时间和优化效果的平衡
4. **正确性保证**: 任何优化都必须保证程序语义不变

## 贡献指南

如果你想扩展这些示例：

1. 保持代码风格一致
2. 添加详细的注释说明
3. 更新对应的.md文档
4. 确保代码可以编译运行
5. 添加新的测试用例

## 许可证

这些示例代码仅供学习使用，可以自由修改和分发。
