#!/bin/bash
set -e

echo "=== Harness 初始化 ==="

echo "=== 编译并运行验证 ==="
(mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build . && ./../bin/ray_tracer)

echo "=== 运行测试 ==="
cd build && ctest --output-on-failure && cd ..

echo "=== 验证完成 ==="
echo ""
echo "下一步："
echo "1. 阅读 feature_list.json 了解当前特性状态"
echo "2. 选择 ONE 个未完成的特性"
echo "3. 只实现该特性"
echo "4. 完成后重新执行验证"
