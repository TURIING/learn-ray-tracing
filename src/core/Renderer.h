#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

/**
 * @brief 渲染器类，负责将光线追踪结果输出到图像
 *
 * 目前实现了天空背景渲染：根据光线方向的 y 分量，
 * 在白色（地平线）和蓝色（天顶）之间进行线性混合。
 */
class Renderer {
public:
    /**
     * @brief 根据光线方向计算天空颜色
     *
     * 使用线性混合公式：
     *   t = 0.5 * (unit_direction.y + 1.0)
     *   color = (1-t) * white + t * blue
     *
     * @param r 从相机发出的光线
     * @return 天空颜色（线性空间，分量范围 [0, 1]）
     */
    static glm::vec3 rayColor(const Ray& r);
};
