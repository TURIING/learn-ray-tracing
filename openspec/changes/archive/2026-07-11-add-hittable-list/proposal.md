## Why

当前渲染器只支持单个球体场景。要实现多物体场景（多个球体、大地平面等），需要引入一个能容纳多个 Hittable 对象的容器。同时，引入 Hittable 接口后，Renderer 中遗留的硬编码球体检测方法已无用处，应一并清理。

## What Changes

- **新增** `HittableList` 类：实现 Hittable 接口，持有 `std::vector<std::shared_ptr<Hittable>>`，通过线性扫描返回最近命中点
- **新增** 多物体场景：main.cpp 中使用 HittableList 管理两个球体（主体球 + 大地平面球）
- **移除** `Renderer::hitSphere()`、`Renderer::hitSphereT()`：**BREAKING** — 硬编码球体检测已被 Sphere::hit 替代
- **移除** `Renderer::rayColor(r)` 单参数重载：**BREAKING** — 硬编码球体场景已被 rayColor(r, world) 替代
- **重构** 天空背景测试：改为直接调用 `Renderer::background()` 而非通过已删除的 rayColor(r)

## Capabilities

### New Capabilities
- `hittable-list`: 管理多个 Hittable 对象的容器，支持添加/清空/遍历命中检测，自身实现 Hittable 接口以保持对外透明

### Modified Capabilities
<!-- 无现有 spec 需要修改 -->

## Impact

- `src/core/HittableList.h` — 新增文件
- `src/core/Renderer.h` / `Renderer.cpp` — 删除 3 个旧方法
- `src/main.cpp` — 场景升级为多物体
- `tests/test_renderer.cpp` — 天空测试重构为 background() 调用，旧命中测试移除
- `tests/test_hittable_list.cpp` — 新增测试文件
- `tests/CMakeLists.txt` — 注册新测试文件
