#pragma once

#include "Ray.h"
#include "Hittable.h"
#include <glm/glm.hpp>

/**
 * @brief 渲染器类，负责将光线追踪结果输出到图像
 *
 * 提供天空背景渲染和场景着色功能：
 * - 天空：根据光线方向的 y 分量，在白色（地平线）和蓝色（天顶）之间线性混合
 * - 场景：通过 Hittable 接口检测光线命中，命中则通过法线可视化表面颜色
 */
class Renderer {
public:
    /**
     * @brief 根据光线方向计算天空背景颜色
     *
     * 使用线性混合公式：
     *   t = 0.5 * (unit_direction.y + 1.0)
     *   color = (1-t) * white + t * blue
     *
     * @param r 从相机发出的光线
     * @return 天空颜色（线性空间，分量范围 [0, 1]）
     */
    static glm::vec3 background(const Ray& r);

    /**
     * @brief 根据光线和场景计算像素颜色
     *
     * 使用 Hittable 接口检测场景中物体的相交，命中则通过表面法线计算颜色；
     * 未命中则回退到天空背景。
     *
     * 颜色公式：0.5 * (N + 1.0)，将法线分量从 [-1,1] 映射到 [0,1]
     *
     * @param r 从相机发出的光线
     * @param world 场景中的可击中物体
     * @return 像素颜色（线性空间，分量范围 [0, 1]）
     */
    static glm::vec3 rayColor(const Ray& r, const Hittable& world);
};
