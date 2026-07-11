#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

/**
 * @brief 光线击中记录，存储交点信息
 *
 * 当 Hittable::hit 返回 true 时，此结构体包含：
 * - 交点坐标 p
 * - 交点处的表面法线 normal（单位向量，指向外侧）
 * - 光线参数 t（交点沿光线的距离）
 */
struct HitRecord {
    glm::vec3 p;       ///< 交点坐标
    glm::vec3 normal;  ///< 表面法线（单位向量）
    float t;           ///< 光线参数
};

/**
 * @brief 可被光线击中的物体抽象基类
 *
 * 所有可渲染的几何体（球体、平面、三角形等）均需实现此接口。
 * 子类必须实现 hit 方法，用于检测光线是否与物体相交，
 * 并在指定参数范围 [tMin, tMax] 内记录最近的交点信息。
 */
class Hittable {
public:
    virtual ~Hittable() = default;

    /**
     * @brief 检测光线是否击中物体
     *
     * @param r 入射光线
     * @param tMin 光线参数的最小值（交点 t 必须 >= tMin）
     * @param tMax 光线参数的最大值（交点 t 必须 <= tMax）
     * @param[out] rec 命中记录，仅在返回 true 时更新
     * @return true 表示光线击中物体，false 表示未击中
     */
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};
