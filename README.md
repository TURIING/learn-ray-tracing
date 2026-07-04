# Learn Ray Tracing

从零学习光线追踪，基于 Peter Shirley 的 [Ray Tracing In One Weekend](https://raytracing.github.io/) 系列。

## 学习路线

- [ ] **Ray Tracing In One Weekend** — 基础光线追踪器
- [ ] **Ray Tracing: The Next Week** — 进阶主题（BVH、纹理、光照）
- [ ] **Ray Tracing: The Rest of Your Life** — 蒙特卡洛采样与重要性采样
- [ ] **GPU 加速** — 基于 Vulkan RTX / Compute Shader 实现

## 参考资源

- [Ray Tracing in One Weekend 系列](https://raytracing.github.io/)
- [tinyrenderer](https://github.com/ssloy/tinyrenderer) — 软渲染器教程
- [vk_mini_path_tracer](https://github.com/nvpro-samples/vk_mini_path_tracer) — Vulkan 路径追踪
- [RayTracingInVulkan](https://github.com/GPSnoopy/RayTracingInVulkan) — RTX 扩展实现

## 构建

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
