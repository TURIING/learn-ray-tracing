# hittable-list

## Purpose

管理多个 Hittable 对象的容器，支持多物体光线追踪场景。同时定义清理后的 Renderer 接口规范。

## Requirements

### Requirement: HittableList 管理多个 Hittable 对象
HittableList SHALL 持有 `std::vector<std::shared_ptr<Hittable>>`，并提供 `add()` 方法向列表中添加对象、`clear()` 方法清空列表。

#### Scenario: 向空列表添加对象
- **WHEN** 调用 `world.add(object)` 添加一个 Hittable 对象
- **THEN** 该对象被加入内部列表，后续 `hit()` 调用会检测该对象

#### Scenario: 清空列表
- **WHEN** 调用 `world.clear()`
- **THEN** 列表被清空，后续 `hit()` 不会命中任何对象

### Requirement: HittableList 遍历所有对象返回最近命中
HittableList SHALL 实现 `hit()` 方法，遍历内部列表中所有对象，返回光线方向上参数 t 最小的交点。HittableList 自身必须实现 Hittable 接口。

#### Scenario: 单物体列表命中
- **WHEN** 列表包含一个球体，光线命中该球体
- **THEN** 返回 true，`rec` 包含正确的交点信息

#### Scenario: 多物体列表返回最近命中
- **WHEN** 列表包含两个球体，光线同时命中两者
- **THEN** 返回 true，`rec` 对应 t 值更小的那个交点

#### Scenario: 空列表不命中
- **WHEN** 列表为空，光线射向任意方向
- **THEN** 返回 false，`rec` 未被修改

#### Scenario: 全部未命中
- **WHEN** 列表包含物体但光线未命中任何物体
- **THEN** 返回 false

### Requirement: Renderer::background 作为独立天空背景方法
Renderer SHALL 保留 `background(const Ray& r)` 方法，根据光线方向计算天空渐变颜色，不依赖任何场景物体。

#### Scenario: 天空渐变颜色正确
- **WHEN** 光线方向为垂直向上 (0,1,0)
- **THEN** 返回蓝色 (0.5, 0.7, 1.0)

#### Scenario: 天空渐变颜色范围正确
- **WHEN** 光线方向为任意单位向量
- **THEN** 颜色分量均在 [0, 1] 范围内

### Requirement: Renderer::rayColor 仅保留 Hittable 接口版本
Renderer SHALL 仅保留 `rayColor(const Ray& r, const Hittable& world)` 双参数版本。移除硬编码球体的单参数 `rayColor(const Ray& r)`。

#### Scenario: 场景命中返回法线颜色
- **WHEN** 光线命中场景中的物体
- **THEN** 返回基于法线的颜色 0.5 * (normal + 1.0)

#### Scenario: 场景未命中返回天空颜色
- **WHEN** 光线未命中场景中任何物体
- **THEN** 返回与 `background(r)` 一致的颜色
