## ADDED Requirements

### Requirement: RandomFloat 生成 [0,1) 范围的随机浮点数
系统 SHALL 提供 `RandomFloat()` 函数，返回 [0, 1) 范围内的随机浮点数，使用 `std::mt19937` 作为随机数引擎。

#### Scenario: 多次调用返回不同值
- **WHEN** 连续调用 `RandomFloat()` 两次
- **THEN** 返回值在 [0, 1) 范围内

#### Scenario: 值在有效范围内
- **WHEN** 调用 `RandomFloat()` 10000 次
- **THEN** 所有返回值均在 [0.0, 1.0) 范围内

### Requirement: RandomFloat(min, max) 生成指定范围的随机浮点数
系统 SHALL 提供 `RandomFloat(float min, float max)` 函数，返回 [min, max) 范围内的随机浮点数。

#### Scenario: 指定范围的值分布正确
- **WHEN** 调用 `RandomFloat(5.0, 10.0)` 多次
- **THEN** 所有返回值均在 [5.0, 10.0) 范围内

### Requirement: 随机数生成器使用 std::random_device 初始化种子
随机数引擎 SHALL 在首次调用时使用 `std::random_device` 初始化种子，确保每次运行产生不同的随机序列。

#### Scenario: 不同运行产生不同序列
- **WHEN** 程序启动后首次调用 `RandomFloat()`
- **THEN** 引擎使用随机设备种子初始化
