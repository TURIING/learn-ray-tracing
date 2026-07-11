#pragma once

#include "Hittable.h"
#include <memory>
#include <vector>

/**
 * @brief Hittable 对象容器，管理多个可被光线击中的物体
 *
 * 采用 Composite 模式，HittableList 自身实现 Hittable 接口，
 * 对渲染器透明。hit() 方法线性扫描所有物体，返回最近交点。
 *
 * 使用示例：
 *   HittableList world;
 *   world.add(std::make_shared<Sphere>(center, radius));
 *   world.add(std::make_shared<Sphere>(center2, radius2));
 *   Renderer::rayColor(r, world);
 */
class HittableList : public Hittable {
public:
    /** @brief 默认构造空列表 */
    HittableList() = default;

    /**
     * @brief 构造包含单个物体的列表
     * @param object 初始物体
     */
    explicit HittableList(std::shared_ptr<Hittable> object) { add(object); }

    /** @brief 清空所有物体 */
    void clear() { m_objects.clear(); }

    /**
     * @brief 向列表中添加物体
     * @param object 待添加的物体（shared_ptr 共享所有权）
     */
    void add(std::shared_ptr<Hittable> object) { m_objects.push_back(object); }

    /**
     * @brief 遍历所有物体，返回最近命中点
     *
     * 使用临时 HitRecord 避免命中确认前污染输出参数。
     * closestSoFar 随命中更新，自动排除更远的交点。
     *
     * @param r 入射光线
     * @param tMin 光线参数下界
     * @param tMax 光线参数上界
     * @param[out] rec 最近命中记录，仅在返回 true 时有效
     * @return true 表示至少一个物体被命中
     */
    bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override {
        HitRecord tempRec;
        bool hitAnything = false;
        auto closestSoFar = tMax;

        for (const auto& object : m_objects) {
            if (object->hit(r, tMin, closestSoFar, tempRec)) {
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }

    /** @brief 获取内部物体列表（仅读） */
    const std::vector<std::shared_ptr<Hittable>>& objects() const { return m_objects; }

private:
    std::vector<std::shared_ptr<Hittable>> m_objects;  ///< 物体列表
};
