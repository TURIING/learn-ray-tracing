## 1. Random 随机数工具

- [x] 1.1 创建 `src/utils/Random.h`，实现 `RandomFloat()` 和 `RandomFloat(min, max)` 函数，使用 `std::mt19937` + `std::uniform_real_distribution<float>`

## 2. Camera 类

- [x] 2.1 创建 `src/core/Camera.h`，实现 Camera 封装类（默认视口参数，`GetRay(u, v)`，Getter 方法），遵循项目代码规范

## 3. 主循环改造

- [x] 3.1 修改 `src/main.cpp`：使用 Camera 替代硬编码视口变量，增加采样循环，引入 `constexpr kSamplesPerPixel`，累加颜色后 `/kSamplesPerPixel` 并用 `glm::clamp` 钳位
- [x] 3.2 将 `main.cpp` 中的 `std::cerr` / `std::cout` 替换为 `LOG_INFO` / `LOG_ERROR` 宏，添加 `Log::Init()` 和 `Log::Shutdown()`

## 4. 测试

- [x] 4.1 创建 `tests/test_random.cpp`，验证 `RandomFloat()` 范围 [0,1) 和 `RandomFloat(min,max)` 范围
- [x] 4.2 创建 `tests/test_camera.cpp`，验证默认视口参数的 `GetRay()` 输出

## 5. 验证

- [x] 5.1 编译项目确保无错误
- [x] 5.2 运行 `./bin/ray_tracer` 生成抗锯齿图像
- [x] 5.3 运行 `cd build && ctest` 确保全部测试通过
