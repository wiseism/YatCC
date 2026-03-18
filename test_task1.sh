#!/bin/bash

# 简单的task1测试脚本

TASK1_BIN="/Users/ibqo/Develop/git/github/cpp/yatcc/task/1/flex/task1"
CASES_DIR="/Users/ibqo/Develop/git/github/cpp/yatcc/test/cases"
OUTPUT_DIR="/tmp/task1_test"

# 创建输出目录
mkdir -p "$OUTPUT_DIR"

# 测试用例列表
test_cases=(
    "functional-0/000_main.sysu.c"
    "functional-0/001_var_defn.sysu.c"
    "functional-0/002_var_defn2.sysu.c"
    "functional-0/003_var_defn3.sysu.c"
    "functional-0/004_const_var_defn.sysu.c"
    "functional-0/005_const_var_defn2.sysu.c"
    "functional-0/006_const_var_defn3.sysu.c"
    "functional-0/007_comment1.sysu.c"
    "functional-0/008_comment2.sysu.c"
    "functional-0/009_hex_defn.sysu.c"
    "functional-0/010_hex_oct_add.sysu.c"
)

echo "开始测试task1..."
echo "===================="

passed=0
total=${#test_cases[@]}

for case in "${test_cases[@]}"; do
    case_name=$(basename "$case")
    output_file="$OUTPUT_DIR/${case_name}.output"
    
    echo -n "测试 $case_name ... "
    
    # 运行task1
    "$TASK1_BIN" "$CASES_DIR/$case" "$output_file" > /dev/null 2>&1
    
    # 检查输出文件是否存在
    if [ -f "$output_file" ]; then
        # 检查输出是否为空
        if [ -s "$output_file" ]; then
            echo "PASS"
            ((passed++))
        else
            echo "FAIL (输出为空)"
        fi
    else
        echo "FAIL (无输出文件)"
    fi
done

echo "===================="
echo "测试结果: $passed/$total 通过"
