#pragma once

#include <glm/glm.hpp>

/**
 * @brief 光线类，表示三维空间中的一条射线
 *
 * 光线由原点 origin 和方向 direction 定义，参数方程为：
 * P(t) = origin + t * direction，其中 t >= 0。
 * direction 应为单位向量以保证参数 t 对应实际距离。
 */
class Ray {
public:
    using Point3 = glm::vec3;
    using Vec3   = glm::vec3;

    /**
     * @brief 构造光线
     * @param origin 光线起点
     * @param direction 光线方向（应为单位向量）
     */
    Ray(const Point3& origin, const Vec3& direction);

    /** @brief 获取光线起点 */
    Point3 origin() const { return m_origin; }

    /** @brief 获取光线方向 */
    Vec3 direction() const { return m_direction; }

    /**
     * @brief 计算光线上参数 t 处的点坐标
     * @param t 参数值
     * @return 点坐标 P(t) = origin + t * direction
     */
    Point3 at(float t) const;

private:
    Point3 m_origin;
    Vec3   m_direction;
};
