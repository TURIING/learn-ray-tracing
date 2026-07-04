#include "Renderer.h"

glm::vec3 Renderer::rayColor(const Ray& r)
{
    // 归一化方向向量，确保 y 分量在 [-1, 1] 范围内
    glm::vec3 unit_direction = glm::normalize(r.direction());

    // 将 y 从 [-1, 1] 映射到 [0, 1]
    auto t = 0.5f * (unit_direction.y + 1.0f);

    // 在白色和蓝色之间线性混合
    const glm::vec3 white(1.0f, 1.0f, 1.0f);
    const glm::vec3 blue(0.5f, 0.7f, 1.0f);

    // 线性插值
    return (1.0f - t) * white + t * blue;
}
