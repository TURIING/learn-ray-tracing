# front-face-detection

## Purpose

在光线追踪击中物体时检测击中面的方向（正面/背面），为材质系统（漫反射、金属、电介质/折射）提供必要的面朝向信息。

## Requirements

### Requirement: HitRecord 记录击中面方向
HitRecord SHALL 包含一个 `frontFace` 布尔字段，表示光线击中表面的是正面（true）还是背面（false）。

#### Scenario: 光线从外侧击中球体
- **WHEN** 光线从球体外部照射到球体表面
- **THEN** `frontFace` 为 true，`normal` 指向光线来源方向（与外法线同向）

#### Scenario: 光线从内侧击中球体
- **WHEN** 光线起点在球体内部，从内部击中球体表面
- **THEN** `frontFace` 为 false，`normal` 指向光线来源方向（与外法线反向）

### Requirement: setFaceNormal 方法统一设置法线朝向
HitRecord SHALL 包含一个 `setFaceNormal(const Ray& r, const glm::vec3& outwardNormal)` 方法，该方法根据光线方向与几何外法线的点积判断击中面，并设置法线始终指向光源侧。

#### Scenario: 点积小于零时判定为正面击中
- **WHEN** `dot(ray.direction(), outwardNormal) < 0`
- **THEN** `frontFace` 设为 true，`normal` 设为 `outwardNormal`

#### Scenario: 点积大于或等于零时判定为背面击中
- **WHEN** `dot(ray.direction(), outwardNormal) >= 0`
- **THEN** `frontFace` 设为 false，`normal` 设为 `-outwardNormal`

### Requirement: Sphere::hit 使用 setFaceNormal 方法
Sphere::hit 方法 SHALL 使用 `setFaceNormal` 方法替代直接为 `rec.normal` 赋值，以确保法线朝向正确处理。

#### Scenario: 球体正常击中
- **WHEN** 光线击中球体表面
- **THEN** 交点处的 `frontFace` 和 `normal` 由 `setFaceNormal` 方法正确设置
