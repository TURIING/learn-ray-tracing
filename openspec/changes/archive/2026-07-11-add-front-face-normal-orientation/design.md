## Context

当前 `HitRecord` 结构体仅存储交点坐标 `p`、表面法线 `normal` 和光线参数 `t`。法线始终指向几何体的外侧（即 `outward_normal`），无法表示光线从内部击中表面的情况。

这在后续实现介质材质（折射/玻璃）时将产生问题：光线进入玻璃球内部后，法线应指向内侧。

参考 Peter Shirley 的实现，解决方案是在 `HitRecord` 中引入 `frontFace` 标志和 `setFaceNormal` 方法。

## Goals / Non-Goals

**Goals:**
- 在所有 Hittable 子类中统一法线朝向处理逻辑
- 法线始终指向光线来源方向（光源侧），而非几何外侧
- 为后续材质系统（漫反射、金属、电介质）提供正确的基础数据

**Non-Goals:**
- 不涉及材质系统本身的实现
- 不修改 Hittable 接口签名
- 不改变 `HitRecord` 的对外数据布局（仅新增字段）

## Decisions

### 1. `setFaceNormal` 作为 inline 方法放在头文件中

**选择**: 在 `HitRecord` 结构体内部定义 inline 方法

**理由**:
- 这是简单逻辑，无需单独的 .cpp 文件
- inline 不影响性能（编译器会自动决定是否内联）
- 保持与现有代码风格一致（单头文件定义结构体和接口）

**替代方案**: 定义为独立函数 — 但这样会割裂数据与行为，使用不便。

### 2. 翻转判断逻辑：`dot(r.direction(), outward_normal) < 0`

**选择**: 点积 < 0 表示正面击中

**理由**:
- 光线方向 `d` 与表面外法线 `n_out` 方向相反时，`dot(d, n_out) < 0` → 正面
- 光线方向 `d` 与表面外法线 `n_out` 方向相同时，`dot(d, n_out) > 0` → 背面（光线来自内部）
- 这是物理直觉：正面的法线应指向光线来的方向

### 3. `frontFace` 存储为布尔字段

**选择**: `bool frontFace` 作为 `HitRecord` 的直接字段

**理由**:
- 后续材质计算需要此信息来决定反射/折射行为
- 存储而非按需计算，避免重复点积运算

### 4. Sphere::hit 中使用 `setFaceNormal` 替代手动计算

**选择**: 先用 `(p - center) / radius` 计算几何外法线，再调用 `setFaceNormal`

**理由**:
- 球体的几何外法线计算简单（交点减球心再除以半径）
- `setFaceNormal` 统一处理翻转逻辑
- 其他未来 Hittable 子类可复用相同模式

## Risks / Trade-offs

- **ABI 兼容性**: 结构体大小变化（新增 1 bool = 1 byte，但由于对齐可能增加 3 bytes padding）→ 影响很小，这是单项目内部结构体，不涉及外部 ABI
- **现有代码需要适配**: 所有读取 `rec.normal` 的代码不会报错，但语义变了（之前始终外法线，现在指向光源侧）→ 当前唯一的消费者是 `Renderer::rayColor` 中的法线可视化，结果不变（因为当前只有正面击中场景，且法线可视化公式 `0.5*(N+1)` 对正面击中无变化）
