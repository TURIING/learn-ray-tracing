#pragma once

#include "Hittable.h"
#include <glm/glm.hpp>

/**
 * @brief 球体几何体，实现 Hittable 接口
 *
 * 使用解析法（判别式）检测光线与球体的相交。
 * 对于给定光线 P(t) = origin + t * direction，求解：
 *   |P(t) - center|² = radius²
 * 展开为关于 t 的一元二次方程，通过判别式判断相交情况。
 */
class Sphere : public Hittable {
public:
    /** @brief 默认构造 */
    Sphere() = default;

    /**
     * @brief 构造球体
     * @param center 球心坐标
     * @param radius 球体半径
     */
    Sphere(const glm::vec3& center, float radius);

    /**
     * @brief 检测光线是否击中球体
     *
     * 在 (tMin, tMax) 开区间内查找最近的交点（判别式 > 0 才视为命中）。
     * 优先尝试较小的根（近交点），不在范围内则尝试较大的根。
     * 若光线起点在球体内部，则返回出口点。
     *
     * @param r 入射光线
     * @param tMin 光线参数的最小值（开区间下界）
     * @param tMax 光线参数的最大值（开区间上界）
     * @param[out] rec 命中记录
     * @return true 表示命中
     */
    bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;

private:
    glm::vec3 m_center{0.0f};  ///< 球心坐标
    float     m_radius{0.0f};  ///< 球体半径
};
