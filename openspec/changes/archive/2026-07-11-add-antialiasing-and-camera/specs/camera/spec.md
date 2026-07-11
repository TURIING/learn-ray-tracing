## ADDED Requirements

### Requirement: Camera 封装视口参数
Camera 类 SHALL 持有视口参数（origin, lowerLeftCorner, horizontal, vertical），并提供 `GetRay(float u, float v)` 方法根据归一化坐标生成光线。

#### Scenario: 默认视口生成中心光线
- **WHEN** 调用 `GetRay(0.5, 0.5)` 使用默认构造的 Camera
- **THEN** 返回的光线方向为 (0, 0, -1)，指向视口中心

#### Scenario: 视口左下角光线
- **WHEN** 调用 `GetRay(0.0, 0.0)`
- **THEN** 光线方向为 lowerLeftCorner - origin = (-2, -1, -1)

### Requirement: Camera 提供 Getter 方法访问私有成员
Camera 类 SHALL 通过 `GetOrigin()`, `GetLowerLeftCorner()`, `GetHorizontal()`, `GetVertical()` 方法暴露视口参数。

#### Scenario: Getter 返回构造时设置的参数
- **WHEN** 默认构造 Camera 后调用 `GetOrigin()`
- **THEN** 返回 (0, 0, 0)
