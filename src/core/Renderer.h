#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

/**
 * @brief 渲染器类，负责将光线追踪结果输出到图像
 *
 * 实现了天空背景渲染、球体绘制和法线可视化功能：
 * - 天空：根据光线方向的 y 分量，在白色（地平线）和蓝色（天顶）之间线性混合
 * - 球体：检测光线与球体的相交，命中则通过法线可视化表面颜色
 */
class Renderer {
public:
    /**
     * @brief 检测光线是否击中球体（布尔版本）
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
     * @brief 计算光线与球体的最近交点距离
     *
     * 通过求解二次方程得到光线与球体的交点参数 t：
     *   t = (-b - sqrt(b² - 4ac)) / (2a)
     *
     * @param center 球心坐标
     * @param radius 球体半径
     * @param r 入射光线
     * @return 最近交点的 t 值，未命中时返回 -1.0
     */
    static float hitSphereT(const glm::vec3& center, float radius, const Ray& r);

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
     * 检测球体相交，命中则通过表面法线计算颜色（法线可视化）；
     * 未命中则回退到天空背景。
     * 颜色公式：0.5 * (N + 1.0)，将法线分量从 [-1,1] 映射到 [0,1]
     *
     * @param r 从相机发出的光线
     * @return 像素颜色（线性空间，分量范围 [0, 1]）
     */
    static glm::vec3 rayColor(const Ray& r);
};
