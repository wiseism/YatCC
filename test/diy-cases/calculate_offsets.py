#!/usr/bin/env python3

def calculate_offsets(filename):
    with open(filename, 'r') as f:
        content = f.read()
    
    print(f"File length: {len(content)}")
    print("\n=== First 500 characters ===")
    print(repr(content[:500]))
    
    # 查找一些关键位置
    search_strings = [
        "int main(){",
        "int a, b, c, d;",
        "a = 10;",
        "return (c + a) * (b - d);"
    ]
    
    print("\n=== Key positions ===")
    for s in search_strings:
        pos = content.find(s)
        if pos != -1:
            print(f"'{s}' found at offset {pos}")
            # 显示位置周围的内容
            start = max(0, pos - 20)
            end = min(len(content), pos + len(s) + 20)
            print(f"  Surrounding: {repr(content[start:end])}")

if __name__ == "__main__":
    filename = "/mnt/d/develops/git/github/cpp/YatCC/cmake-build-debug-wsl24/test/task0/functional-1/024_op_priority2.sysu.c"
    calculate_offsets(filename)
