## Why

当前 `HitRecord` 只存储法线向量，无法区分光线击中物体的是正面还是背面。随着后续要实现透明材质（折射）和不同面有不同表现（如玻璃球内部），必须知道光线是从外侧还是内侧击中表面。这是漫反射、金属、电介质材质实现的前置依赖。

## What Changes

- **HitRecord** 结构体新增 `frontFace` 布尔字段，表示光线是否从外侧击中表面
- **HitRecord** 结构体新增 `setFaceNormal()` 方法，统一根据外法线和光线方向设置法线朝向
  - 光线方向与外法线方向相反 → 正面击中 → 法线保持指向外侧
  - 光线方向与外法线方向相同 → 背面击中 → 法线翻转指向内侧
- **BREAKING**: `HitRecord::normal` 的语义变化 — 现在始终指向光线的逆方向（即指向"光源侧"），而非原始几何外法线
- **Sphere::hit()** 使用 `setFaceNormal()` 替代直接赋值 `rec.normal`

## Capabilities

### New Capabilities
- `front-face-detection`: 在光线击中物体时检测击中面的方向（正面/背面），为后续材质系统（反射、折射）提供必要信息

### Modified Capabilities
<!-- 无现有 spec 需要修改 -->

## Impact

- `src/core/Hittable.h` — HitRecord 结构体修改，新增字段和方法
- `src/core/Sphere.cpp` — Sphere::hit 方法内法线赋值逻辑改为调用 setFaceNormal
- 未来所有 Hittable 子类都需要使用 setFaceNormal 方法设置法线
