#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

/**
 * @brief 渲染器类，负责将光线追踪结果输出到图像
 *
 * 实现了天空背景渲染和球体绘制功能：
 * - 天空：根据光线方向的 y 分量，在白色（地平线）和蓝色（天顶）之间线性混合
 * - 球体：检测光线与球体的相交，命中则返回红色
 */
class Renderer {
public:
    /**
     * @brief 检测光线是否击中球体
     *
     * 通过求解二次方程判断光线与球体是否相交：
     *   discriminant = b² - 4ac，其中 discriminant > 0 表示相交
     *
     * @param center 球心坐标
     * @param radius 球体半径
     * @param r 入射光线
     * @return true 表示光线击中球体，false 表示未击中
     */
    static bool hitSphere(const glm::vec3& center, float radius, const Ray& r);

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
     * @brief 根据光线计算像素颜色
     *
     * 优先检测球体相交，命中则返回红色；否则回退到天空背景。
     *
     * @param r 从相机发出的光线
     * @return 像素颜色（线性空间，分量范围 [0, 1]）
     */
    static glm::vec3 rayColor(const Ray& r);
};
