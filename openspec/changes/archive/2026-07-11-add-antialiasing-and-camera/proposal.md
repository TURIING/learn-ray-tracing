## Why

当前渲染器每个像素只发射一条光线（通过像素中心），导致物体边缘出现明显的锯齿。引入多重采样抗锯齿（supersampling）：每个像素发射多条随机偏移的光线，取平均值作为最终颜色，用噪声替代锯齿边缘。同时，将硬编码在 main.cpp 中的视口参数抽取为 Camera 类，提高代码可复用性。

## What Changes

- **新增** `Camera` 类：封装视口参数（origin, lowerLeftCorner, horizontal, vertical），提供 `GetRay(u, v)` 方法生成光线
- **新增** `Random` 工具：基于 `std::mt19937` + `std::uniform_real_distribution` 的随机浮点数生成
- **新增** 多重采样：每个像素发射 `kSamplesPerPixel` 条光线，子像素位置随机抖动
- **修改** `main.cpp`：使用 Camera 替代硬编码视口变量，内层增加采样循环，颜色累加后除以采样数，使用 `glm::clamp` 防溢出

## Capabilities

### New Capabilities
- `camera`: 封装视口参数和光线生成逻辑，提供 `GetRay(u, v)` 接口
- `antialiasing`: 通过对每个像素进行多次随机采样并取平均值，消除物体边缘锯齿
- `random-utility`: 基于 `<random>` 的随机浮点数工具，支持 `[0,1)` 和 `[min,max)` 范围

### Modified Capabilities
<!-- 无现有 spec 需要修改 -->

## Impact

- `src/core/Camera.h` — 新增文件
- `src/utils/Random.h` — 新增文件
- `src/main.cpp` — Camera 替代视口变量，采样循环，颜色累加/平均/clamp
- `tests/test_camera.cpp` — 新增测试
- `tests/test_random.cpp` — 新增测试
