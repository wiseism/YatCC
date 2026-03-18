#!/bin/bash

# 完整的task1测试脚本

TASK1_BIN="/Users/ibqo/Develop/git/github/cpp/yatcc/task/1/flex/task1"
CASES_DIR="/Users/ibqo/Develop/git/github/cpp/yatcc/test/cases"
OUTPUT_DIR="/tmp/task1_test_output"

# 创建输出目录
mkdir -p "$OUTPUT_DIR"

# 获取所有测试用例
cd "$CASES_DIR"
find . -name "*.sysu.c" | sed 's|^\./||' | sort > /tmp/cases.txt

echo "开始测试task1..."
echo "===================="
echo "测试用例总数: $(wc -l < /tmp/cases.txt)"
echo "===================="

passed=0
failed=0
total=$(wc -l < /tmp/cases.txt)

while IFS= read -r case; do
    case_name=$(basename "$case")
    output_file="$OUTPUT_DIR/${case_name}/output.txt"
    
    # 创建输出目录
    mkdir -p "$OUTPUT_DIR/${case_name}"
    
    echo -n "测试 $case_name ... "
    
    # 运行task1
    if "$TASK1_BIN" "$CASES_DIR/$case" "$output_file" > /dev/null 2>&1; then
        # 检查输出文件是否存在且不为空
        if [ -f "$output_file" ] && [ -s "$output_file" ]; then
            echo "PASS"
            ((passed++))
        else
            echo "FAIL (输出为空或不存在)"
            ((failed++))
        fi
    else
        echo "FAIL (运行失败)"
        ((failed++))
    fi
done < /tmp/cases.txt

echo "===================="
echo "测试结果: $passed/$total 通过, $failed 失败"

# 计算得分
if [ $total -gt 0 ]; then
    score=$(echo "scale=2; $passed * 100 / $total" | bc)
    echo "得分: $score/100.00"
fi
