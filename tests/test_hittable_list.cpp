#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "core/HittableList.h"
#include "core/Sphere.h"
#include "core/Ray.h"

class HittableListTest : public ::testing::Test {
protected:
    static constexpr float kEpsilon = 0.001f;
};

// ============================================================
// 空列表
// ============================================================

TEST_F(HittableListTest, EmptyListReturnsFalse)
{
    HittableList world;
    Ray r(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_FALSE(world.hit(r, 0.0f, 1000.0f, rec));
}

// ============================================================
// 单物体
// ============================================================

TEST_F(HittableListTest, SingleObjectHit)
{
    HittableList world;
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));

    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_TRUE(world.hit(r, 0.0f, 1000.0f, rec));
    EXPECT_NEAR(rec.t, 0.5f, kEpsilon);
    EXPECT_NEAR(rec.p.z, -0.5f, kEpsilon);
}

TEST_F(HittableListTest, SingleObjectMiss)
{
    HittableList world;
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));

    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    HitRecord rec;

    EXPECT_FALSE(world.hit(r, 0.0f, 1000.0f, rec));
}

// ============================================================
// 多物体 — 最近命中
// ============================================================

TEST_F(HittableListTest, TwoObjectsReturnsClosestHit)
{
    HittableList world;
    // 近球: 球心 (0,0,-1), 半径 0.5, 命中 t≈0.5
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
    // 远球: 球心 (0,0,-3), 半径 0.5, 命中 t≈2.5
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -3.0f), 0.5f));

    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_TRUE(world.hit(r, 0.0f, 1000.0f, rec));
    EXPECT_NEAR(rec.t, 0.5f, kEpsilon); // 应命中近球
    EXPECT_NEAR(rec.p.z, -0.5f, kEpsilon);
}

TEST_F(HittableListTest, SecondObjectHitWhenFirstMisses)
{
    HittableList world;
    // 球在右方，光线向左不会命中
    world.add(std::make_shared<Sphere>(glm::vec3(1.0f, 0.0f, -1.0f), 0.3f));
    // 球在前方，光线会命中
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));

    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_TRUE(world.hit(r, 0.0f, 1000.0f, rec));
    EXPECT_NEAR(rec.t, 0.5f, kEpsilon);
}

// ============================================================
// 操作
// ============================================================

TEST_F(HittableListTest, ClearRemovesAllObjects)
{
    HittableList world;
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
    world.clear();

    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_FALSE(world.hit(r, 0.0f, 1000.0f, rec));
}

TEST_F(HittableListTest, ConstructorWithSingleObject)
{
    auto sphere = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    HittableList world(sphere);

    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_TRUE(world.hit(r, 0.0f, 1000.0f, rec));
    EXPECT_NEAR(rec.t, 0.5f, kEpsilon);
}

// ============================================================
// Hittable 接口兼容性
// ============================================================

TEST_F(HittableListTest, AcceptViaHittableReference)
{
    HittableList world;
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));

    // 通过 Hittable 引用使用（验证 Composite 模式正确）
    const Hittable& hittable = world;
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_TRUE(hittable.hit(r, 0.0f, 1000.0f, rec));
}
