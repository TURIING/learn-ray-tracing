#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "core/Sphere.h"
#include "core/Renderer.h"
#include "core/Ray.h"

class SphereTest : public ::testing::Test {
protected:
    static constexpr float kEpsilon = 0.001f;
};

// ============================================================
// 基本命中/未命中
// ============================================================

TEST_F(SphereTest, HitCenter)
{
    // 光线从原点指向球心 (0,0,-1)，半径 0.5
    Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_TRUE(sphere.hit(r, 0.0f, 1000.0f, rec));
    EXPECT_NEAR(rec.t, 0.5f, kEpsilon);
    EXPECT_NEAR(rec.p.x, 0.0f, kEpsilon);
    EXPECT_NEAR(rec.p.y, 0.0f, kEpsilon);
    EXPECT_NEAR(rec.p.z, -0.5f, kEpsilon);
    EXPECT_NEAR(rec.normal.x, 0.0f, kEpsilon);
    EXPECT_NEAR(rec.normal.y, 0.0f, kEpsilon);
    EXPECT_NEAR(rec.normal.z, 1.0f, kEpsilon);
}

TEST_F(SphereTest, Miss)
{
    // 光线指向远离球体的方向
    Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    HitRecord rec;

    EXPECT_FALSE(sphere.hit(r, 0.0f, 1000.0f, rec));
}

TEST_F(SphereTest, Tangent)
{
    // 光线恰好擦过球体表面（判别式 = 0），应未命中
    Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    Ray r(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_FALSE(sphere.hit(r, 0.0f, 1000.0f, rec));
}

// ============================================================
// 内部交点
// ============================================================

TEST_F(SphereTest, InsideReturnsExitPoint)
{
    // 光线起点在球心，应返回出口点 (t = radius)
    Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    Ray r(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    HitRecord rec;

    EXPECT_TRUE(sphere.hit(r, 0.0f, 1000.0f, rec));
    EXPECT_NEAR(rec.t, 0.5f, kEpsilon);
    // 出口点法线仍指向外侧 (0,0,1)
    EXPECT_NEAR(rec.normal.z, 1.0f, kEpsilon);
}

TEST_F(SphereTest, InsideOffCenter)
{
    // 光线起点在球体内部但不在球心，方向指向表面
    // 球心 (0,0,-1), 半径 0.5, 起点 (0,0,-1.25) 在球内
    // direction (0,0,-1) 指向更深处
    Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    Ray r(glm::vec3(0.0f, 0.0f, -1.25f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_TRUE(sphere.hit(r, 0.0f, 1000.0f, rec));
    // 出口点: 从球内沿 -z 方向行进 0.25 到达 z=-1.5
    EXPECT_NEAR(rec.t, 0.25f, kEpsilon);
}

// ============================================================
// tMin / tMax 过滤
// ============================================================

TEST_F(SphereTest, TMinFiltersNearRoot)
{
    // 球心命中时 near root = 0.5, far root = 1.5
    // 设 tMin = 0.7 跳过近根，应返回远根 1.5
    Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_TRUE(sphere.hit(r, 0.7f, 1000.0f, rec));
    EXPECT_NEAR(rec.t, 1.5f, kEpsilon);
    EXPECT_NEAR(rec.p.z, -1.5f, kEpsilon);
}

TEST_F(SphereTest, TMaxFiltersBothRoots)
{
    // 球心命中时 near root = 0.5, tMax = 0.3 过滤所有交点
    Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_FALSE(sphere.hit(r, 0.0f, 0.3f, rec));
}

// ============================================================
// 球体在射线后方
// ============================================================

TEST_F(SphereTest, BehindRayWithTMinZero)
{
    // 球体在射线起点后方，tMin=0 排除负根，应未命中
    Sphere sphere(glm::vec3(0.0f, 0.0f, 1.0f), 0.5f);
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    HitRecord rec;

    EXPECT_FALSE(sphere.hit(r, 0.0f, 1000.0f, rec));
}

// ============================================================
// 法线属性
// ============================================================

TEST_F(SphereTest, NormalIsUnitLength)
{
    // 验证不同命中点的法线长度均为 1
    Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    HitRecord rec;

    // 球心命中
    Ray r1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    ASSERT_TRUE(sphere.hit(r1, 0.0f, 1000.0f, rec));
    EXPECT_NEAR(glm::length(rec.normal), 1.0f, kEpsilon);

    // 球面顶部命中
    Ray r2(glm::vec3(0.0f, -0.25f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    ASSERT_TRUE(sphere.hit(r2, 0.0f, 1000.0f, rec));
    EXPECT_NEAR(glm::length(rec.normal), 1.0f, kEpsilon);
}

// ============================================================
// rayColor 集成测试
// ============================================================

TEST_F(SphereTest, RayColorWithWorld)
{
    // 使用新的 rayColor(r, world) 重载
    Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    glm::vec3 color = Renderer::rayColor(r, sphere);

    // 球心法线 (0,0,1) → color = 0.5*(1, 1, 2) = (0.5, 0.5, 1.0)
    EXPECT_NEAR(color.r, 0.5f, kEpsilon);
    EXPECT_NEAR(color.g, 0.5f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}

TEST_F(SphereTest, RayColorWithWorldMissReturnsSky)
{
    // 未命中时返回天空颜色
    Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 color = Renderer::rayColor(r, sphere);

    EXPECT_NEAR(color.r, 0.5f, kEpsilon);
    EXPECT_NEAR(color.g, 0.7f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}
