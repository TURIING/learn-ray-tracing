#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

/**
 * @brief 相机类，封装视口参数和光线生成逻辑
 *
 * 默认构造使用标准视口配置：
 * - 原点 (0, 0, 0) 位于视口前方
 * - 视口尺寸 4×2，位于 z=-1 平面
 *
 * GetRay(u, v) 根据归一化坐标 (u, v) 生成从相机原点出发、
 * 穿过视口对应位置的光线。
 */
class Camera {
public:
    /**
     * @brief 默认构造相机（标准视口配置）
     */
    Camera()
        : m_origin(0.0f, 0.0f, 0.0f)
        , m_lowerLeftCorner(-2.0f, -1.0f, -1.0f)
        , m_horizontal(4.0f, 0.0f, 0.0f)
        , m_vertical(0.0f, 2.0f, 0.0f)
    {
    }

    /**
     * @brief 根据归一化坐标生成光线
     *
     * 光线方向 = lowerLeftCorner + u*horizontal + v*vertical - origin
     *
     * @param u 水平方向归一化坐标 [0, 1]
     * @param v 垂直方向归一化坐标 [0, 1]
     * @return 从相机原点出发、穿过视口 (u,v) 位置的光线
     */
    Ray GetRay(float u, float v) const {
        return Ray(m_origin, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin);
    }

    /** @brief 获取相机原点 */
    glm::vec3 GetOrigin() const { return m_origin; }

    /** @brief 获取视口左下角坐标 */
    glm::vec3 GetLowerLeftCorner() const { return m_lowerLeftCorner; }

    /** @brief 获取视口水平跨度向量 */
    glm::vec3 GetHorizontal() const { return m_horizontal; }

    /** @brief 获取视口垂直跨度向量 */
    glm::vec3 GetVertical() const { return m_vertical; }

private:
    glm::vec3 m_origin;            ///< 相机/眼睛位置（光线起点）
    glm::vec3 m_lowerLeftCorner;   ///< 视口左下角坐标
    glm::vec3 m_horizontal;        ///< 视口水平跨度（从左到右）
    glm::vec3 m_vertical;          ///< 视口垂直跨度（从下到上）
};
