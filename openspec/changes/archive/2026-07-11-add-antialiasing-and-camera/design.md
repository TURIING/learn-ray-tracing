## Context

当前 `main.cpp` 中视口参数（origin, lowerLeftCorner, horizontal, vertical）以局部常量硬编码，每个像素仅发射一条穿过像素中心的光线。这导致：(1) 视口逻辑不可复用；(2) 物体边缘有锯齿。

参考 Peter Shirley 的实现，引入 Camera 类封装视口逻辑，引入多重采样（每个像素 N 条随机偏移光线取平均）实现抗锯齿。

项目使用 C++17 + GLM，遵循 PascalCase 命名、私有成员 `m_camelCase`、中文 doxygen 注释等代码规范。

## Goals / Non-Goals

**Goals:**
- Camera 类封装视口参数和 `GetRay(u, v)` 方法
- 每个像素多次采样，子像素位置随机偏移，累加取平均
- 基于 `<random>` 的随机数工具
- 颜色累加后使用 `glm::clamp` 防止溢出

**Non-Goals:**
- 不涉及可调相机（FOV、lookat、景深）
- 不涉及分层采样（stratified sampling）
- 不涉及 Gamma 校正
- 不涉及并行渲染

## Decisions

### 1. `<random>` 方案：静态局部变量

**选择**: `RandomFloat()` 函数内使用 `static std::mt19937` + `static std::uniform_real_distribution<float>`，用 `std::random_device` 初始化种子。

**理由**: 比 `rand()` 质量高、跨平台一致。静态局部变量避免每次调用重新构造 engine，且在头文件中定义简单。

**替代方案**: 将 engine 封装为类成员 → 对于单一采样场景过度设计。

### 2. Camera 封装类（项目风格）

**选择**: 私有成员 `m_origin`, `m_lowerLeftCorner`, `m_horizontal`, `m_vertical`，公开 `GetRay(u, v)` 和对应的 Getter 方法（遵循 `GetXxx()` 风格）。

**理由**: 遵循项目代码规范（变量暴露用 get 方法）。默认构造函数使用当前硬编码的视口参数。

### 3. 颜色累加与 clamp

**选择**: `glm::clamp(color, 0.0f, 1.0f)` 对每个分量钳位

**理由**: GLM 原生支持，无需额外依赖。当前 `255.99f * clampedValue` 的映射 `[0,1] → [0,255]` 已正确处理。

### 5. 进度输出使用 Log 系统

**选择**: 使用项目已有的 `LOG_INFO` / `LOG_ERROR` 宏（基于 spdlog）替代 `std::cerr` / `std::cout`。

**理由**: 项目已有基于 spdlog 的 Log 单例（异步、彩色控制台输出、可配置级别），应统一使用日志系统而非裸标准输出。程序启动时调用 `Log::Init()`，退出前调用 `Log::Shutdown()`。

### 4. 采样数设为 100（与参考一致）

**选择**: `constexpr int kSamplesPerPixel = 100`

**理由**: 100 次采样足以显著改善视觉质量，渲染时间可接受（800×400×100 = 32M rays）。

## Risks / Trade-offs

- **渲染时间增加 ~100 倍**: 100 samples × 800 × 400 = 32M 次 rayColor 调用 → 可接受，这是离线路由追踪
- **`static` 随机数生成器不可测试**: 无法确定性复现 → 测试验证范围而非具体值
- **Camera 默认参数硬编码**: 与当前视口一致 → 后续可扩展参数化构造
