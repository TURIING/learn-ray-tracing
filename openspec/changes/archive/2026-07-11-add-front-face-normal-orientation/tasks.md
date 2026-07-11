## 1. 修改 HitRecord 结构体

- [x] 1.1 在 `src/core/Hittable.h` 的 `HitRecord` 结构体中新增 `bool frontFace` 字段
- [x] 1.2 在 `src/core/Hittable.h` 的 `HitRecord` 结构体中添加 `void setFaceNormal(const Ray& r, const glm::vec3& outwardNormal)` inline 方法

## 2. 修改 Sphere::hit 实现

- [x] 2.1 在 `src/core/Sphere.cpp` 的 `Sphere::hit` 方法中，用 `rec.setFaceNormal(r, outward_normal)` 替换原来的 `rec.normal = (rec.p - m_center) / m_radius`（两个分支都需要替换）

## 3. 验证

- [x] 3.1 编译项目确保无错误
- [x] 3.2 运行 ./bin/ray_tracer 生成 output.png，对比之前结果确认渲染不变
- [x] 3.3 运行现有测试 `cd build && ctest` 确保全部通过
