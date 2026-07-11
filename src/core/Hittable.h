#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

/**
 * @brief 光线击中记录，存储交点信息
 *
 * 当 Hittable::hit 返回 true 时，此结构体包含：
 * - 交点坐标 p
 * - 交点处的表面法线 normal（单位向量，始终指向光源侧）
 * - 光线参数 t（交点沿光线的距离）
 * - 击中面方向 frontFace（true = 正面/外侧，false = 背面/内侧）
 */
struct HitRecord {
    glm::vec3 p;            ///< 交点坐标
    glm::vec3 normal;       ///< 表面法线（单位向量，指向光源侧）
    float t;                ///< 光线参数
    bool frontFace;         ///< 击中面方向（true=正面，false=背面）

    /**
     * @brief 根据光线方向和几何外法线设置法线朝向
     *
     * 始终使法线指向光线来源方向（光源侧）：
     * - dot(rayDir, outwardNormal) < 0 → 正面击中 → normal = outwardNormal
     * - dot(rayDir, outwardNormal) >= 0 → 背面击中 → normal = -outwardNormal
     *
     * @param r 入射光线
     * @param outwardNormal 几何外法线（单位向量）
     */
    inline void setFaceNormal(const Ray& r, const glm::vec3& outwardNormal) {
        frontFace = glm::dot(r.direction(), outwardNormal) < 0.0f;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
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
