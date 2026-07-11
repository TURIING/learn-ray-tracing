## Context

当前 `Renderer` 直接处理单个 `Hittable` 对象（如 `Sphere`）。要支持多物体场景，需要一个容器类来管理多个 `Hittable` 对象，并遍历它们找到最近的交点。

项目已实现 `Hittable` 抽象接口和 `Sphere` 具体类，`HitRecord` 已包含 `frontFace` 检测。`HittableList` 是自然的下一步——它本身就是 Hittable 接口的实现，对渲染器完全透明。

同时，Renderer 中遗留的 `hitSphere()`、`hitSphereT()` 和单参数 `rayColor(r)` 方法已被 `Sphere::hit()` 和双参数 `rayColor(r, world)` 取代，此次一并清理。

## Goals / Non-Goals

**Goals:**
- 提供 `HittableList` 容器，支持添加/删除多个 `shared_ptr<Hittable>` 对象
- `HittableList::hit()` 遍历所有对象，返回沿光线方向上最近的交点
- 清理 Renderer 中已被 Hittable 接口取代的旧方法
- 升级 main.cpp 场景为多物体（小球 + 大地平面球）

**Non-Goals:**
- 不涉及加速结构（BVH、KD-tree）——保持简单线性扫描
- 不涉及材质系统
- 不涉及相机抽象

## Decisions

### 1. 使用 `std::shared_ptr<Hittable>` 持有对象

**选择**: `shared_ptr`

**理由**: 与参考实现（Peter Shirley）保持一致，简化学习对比。且为未来可能的共享引用场景保留灵活性。

**替代方案**: `unique_ptr` 语义更精确（HittableList 独占所有权），但与书本代码差异更大。

### 2. HittableList 继承 Hittable（Composite 模式）

**选择**: `class HittableList : public Hittable`

**理由**: 这是 Composite 设计模式的经典应用。渲染器无需区分单个物体和物体列表，统一通过 `Hittable::hit()` 接口使用。未来可以嵌套 HittableList。

### 3. 使用 `temp_rec` 避免污染输出参数

**选择**: 每次命中先写入临时 `HitRecord temp_rec`，确认是最近命中后才赋值给 `rec`

**理由**: 如果直接写入 `rec`，当后续物体更近时会被覆盖；如果后续物体未命中，`rec` 中残留的是不完整数据。临时变量避免了这种不干净的状态。

### 4. 头文件内实现 hit() 方法

**选择**: `HittableList.h` 中直接实现 `hit()`，无需 `.cpp` 文件

**理由**: `hit()` 逻辑简单（<10 行的线性循环），放入头文件减少编译单元，与项目中 `Hittable.h`（纯接口头文件）风格一致。

### 5. Renderer 旧方法全部移除而非标记 deprecated

**选择**: 直接删除

**理由**: 这是学习项目的早期阶段，无外部消费者，无向后兼容需求。deprecated 标记只会留下需要后续清理的技术债务。

## Risks / Trade-offs

- **线性扫描 O(n)**: 每个像素对每个物体做一次命中检测 → 当前场景只有 2 个球体，性能完全不受影响。未来物体增多时再引入 BVH。
- **shared_ptr 额外开销**: 引用计数原子操作 → 对离线路由追踪渲染器可忽略不计。
- **测试覆盖**: 删除旧测试时也移除了部分间接的 `background()` 覆盖 → 天空测试重构为直接调用 `background()`，覆盖更精确。
