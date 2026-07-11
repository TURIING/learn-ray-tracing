## 1. 新增 HittableList

- [x] 1.1 创建 `src/core/HittableList.h`，实现 `HittableList : public Hittable` 类，包含 `add()`, `clear()`, `hit()` 方法
- [x] 1.2 在 `tests/CMakeLists.txt` 中注册新测试文件（GLOB_RECURSE 自动发现）

## 2. 清理 Renderer 旧方法

- [x] 2.1 从 `src/core/Renderer.h` 删除 `hitSphere()`, `hitSphereT()`, `rayColor(r)` 声明和注释
- [x] 2.2 从 `src/core/Renderer.cpp` 删除 `hitSphere()`, `hitSphereT()`, `rayColor(r)` 实现

## 3. 更新场景入口

- [x] 3.1 修改 `src/main.cpp`，使用 `HittableList` 管理两个球体（主体球 + 大地平面球）

## 4. 更新测试

- [x] 4.1 创建 `tests/test_hittable_list.cpp`，覆盖空列表、单物体、多物体最近命中、全部未命中场景
- [x] 4.2 重构 `tests/test_renderer.cpp`：天空测试改为直接调用 `background()`，移除所有 `HitSphere*`, `HitSphereT*`, `RayColorSphere*` 测试

## 5. 验证

- [x] 5.1 编译项目确保无错误
- [x] 5.2 运行 `./bin/ray_tracer` 生成多物体场景图像
- [x] 5.3 运行 `cd build && ctest` 确保全部测试通过
