#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <cmath>
#include "core/Renderer.h"
#include "core/Ray.h"

class RendererTest : public ::testing::Test {
protected:
    static constexpr float kEpsilon = 0.001f;
};

TEST_F(RendererTest, RayStraightUpReturnsBlue)
{
    // 光线直指上方 (y=1)，应返回纯蓝色
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 color = Renderer::rayColor(r);

    EXPECT_NEAR(color.r, 0.5f, kEpsilon);
    EXPECT_NEAR(color.g, 0.7f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}

TEST_F(RendererTest, RayStraightDownReturnsWhite)
{
    // 光线直指下方 (y=-1)，应返回纯白色
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    glm::vec3 color = Renderer::rayColor(r);

    EXPECT_NEAR(color.r, 1.0f, kEpsilon);
    EXPECT_NEAR(color.g, 1.0f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}

TEST_F(RendererTest, RayHorizontalReturnsMixed)
{
    // 光线水平方向 (y=0)，t=0.5，白色和蓝色各半混合
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec3 color = Renderer::rayColor(r);

    EXPECT_NEAR(color.r, 0.75f, kEpsilon); // 0.5*1.0 + 0.5*0.5
    EXPECT_NEAR(color.g, 0.85f, kEpsilon); // 0.5*1.0 + 0.5*0.7
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);  // 0.5*1.0 + 0.5*1.0
}

TEST_F(RendererTest, RayNormalizationIsApplied)
{
    // 传入非单位方向向量，验证内部做了归一化
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f));
    glm::vec3 color = Renderer::rayColor(r);

    // 归一化后方向为 (0,1,0)，结果应与 RayStraightUpReturnsBlue 一致
    EXPECT_NEAR(color.r, 0.5f, kEpsilon);
    EXPECT_NEAR(color.g, 0.7f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}

TEST_F(RendererTest, RayAtFortyFiveDegrees)
{
    // 45度朝上方向
    float s = std::sqrt(2.0f) / 2.0f; // sin(45°) = cos(45°)
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, s, s));
    glm::vec3 color = Renderer::rayColor(r);

    // t = 0.5 * (s + 1.0) = 0.5 * (0.7071 + 1.0) ≈ 0.85355
    // color = (1-t)*white + t*blue
    float t = 0.5f * (s + 1.0f);
    glm::vec3 expected = (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);

    EXPECT_NEAR(color.r, expected.r, kEpsilon);
    EXPECT_NEAR(color.g, expected.g, kEpsilon);
    EXPECT_NEAR(color.b, expected.b, kEpsilon);
}

TEST_F(RendererTest, ColorComponentsInRange)
{
    // 验证对于各种方向，颜色分量始终在 [0, 1] 范围内
    glm::vec3 directions[] = {
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 0.5f, 0.0f),
        glm::vec3(-1.0f, -0.3f, 0.7f),
        glm::vec3(0.2f, 0.8f, 0.4f),
    };

    for (const auto& dir : directions) {
        Ray r(glm::vec3(0.0f), glm::normalize(dir));
        glm::vec3 color = Renderer::rayColor(r);

        EXPECT_GE(color.r, 0.0f);
        EXPECT_LE(color.r, 1.0f);
        EXPECT_GE(color.g, 0.0f);
        EXPECT_LE(color.g, 1.0f);
        EXPECT_GE(color.b, 0.0f);
        EXPECT_LE(color.b, 1.0f);
    }
}

// ============================================================
// hitSphere 单元测试
// ============================================================

TEST_F(RendererTest, HitSphereCenter)
{
    // 光线从原点指向球心 (0, 0, -1)，半径 0.5，应命中
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    EXPECT_TRUE(Renderer::hitSphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r));
}

TEST_F(RendererTest, HitSphereMiss)
{
    // 光线从原点指向远离球体的方向，应未命中
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    EXPECT_FALSE(Renderer::hitSphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r));
}

TEST_F(RendererTest, HitSphereInside)
{
    // 光线起点在球体内部，应命中
    Ray r(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    EXPECT_TRUE(Renderer::hitSphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r));
}

TEST_F(RendererTest, HitSphereTangent)
{
    // 光线恰好擦过球体表面（判别式 = 0），应未命中
    // 球心 (0, 0, -1)，半径 0.5，从原点出发，沿 z=-1 方向偏移半径距离
    Ray r(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    EXPECT_FALSE(Renderer::hitSphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r));
}

TEST_F(RendererTest, HitSphereLineIntersectsButBehindRay)
{
    // 球体在射线起点后方，但光线所在的直线仍与球体相交（数学上判别式 > 0）
    // 注意：hitSphere 当前不检查 t > 0，这是参考实现的预期行为
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    EXPECT_TRUE(Renderer::hitSphere(glm::vec3(0.0f, 0.0f, 1.0f), 0.5f, r));
}

// ============================================================
// hitSphereT 单元测试
// ============================================================

TEST_F(RendererTest, HitSphereTCenter)
{
    // 光线从原点指向球心 (0, 0, -1)，半径 0.5
    // t = 0.5 (交点在 z=-0.5)
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    float t = Renderer::hitSphereT(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r);
    EXPECT_NEAR(t, 0.5f, kEpsilon);
}

TEST_F(RendererTest, HitSphereTMiss)
{
    // 光线未击中球体，应返回 -1.0
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    float t = Renderer::hitSphereT(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r);
    EXPECT_LT(t, 0.0f);
}

TEST_F(RendererTest, HitSphereTInside)
{
    // 光线起点在球体内部（球心），最近交点在射线后方
    // 前方交点 t=0.5 需要通过 (-b + sqrt(discriminant)) / (2a) 获得
    Ray r(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    float t = Renderer::hitSphereT(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r);
    EXPECT_LT(t, 0.0f); // 最近根在后方
}

TEST_F(RendererTest, HitSphereTBehindRay)
{
    // 球体在射线后方，返回负 t（交点在光线反方向）
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    float t = Renderer::hitSphereT(glm::vec3(0.0f, 0.0f, 1.0f), 0.5f, r);
    EXPECT_LT(t, 0.0f);
}

// ============================================================
// rayColor 球体法线可视化集成测试
// ============================================================

TEST_F(RendererTest, RayColorSphereCenterReturnsFrontNormal)
{
    // 光线从原点指向球心，命中点法线为 (0, 0, 1)，颜色 = 0.5*(1, 1, 2) = (0.5, 0.5, 1.0)
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    glm::vec3 color = Renderer::rayColor(r);

    EXPECT_NEAR(color.r, 0.5f, kEpsilon);
    EXPECT_NEAR(color.g, 0.5f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}

TEST_F(RendererTest, RayColorSphereNormalColorInRange)
{
    // 验证法线可视化颜色分量始终在 [0, 1] 范围内
    // 扫描球体上方区域的多条光线
    for (int i = 0; i <= 10; ++i) {
        float u = -0.5f + 0.1f * static_cast<float>(i); // x: -0.5 ~ 0.5
        Ray r(glm::vec3(u, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        glm::vec3 color = Renderer::rayColor(r);

        EXPECT_GE(color.r, 0.0f);
        EXPECT_LE(color.r, 1.0f);
        EXPECT_GE(color.g, 0.0f);
        EXPECT_LE(color.g, 1.0f);
        EXPECT_GE(color.b, 0.0f);
        EXPECT_LE(color.b, 1.0f);
    }
}

TEST_F(RendererTest, RayColorSphereMissReturnsSky)
{
    // 光线未击中球体，应返回天空颜色（延续原有行为）
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 color = Renderer::rayColor(r);

    EXPECT_NEAR(color.r, 0.5f, kEpsilon);
    EXPECT_NEAR(color.g, 0.7f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}

TEST_F(RendererTest, RayColorExistingSkyTestsUnaffected)
{
    // 验证原有天空测试光线不命中球体，行为不变
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec3 color = Renderer::rayColor(r);

    EXPECT_NEAR(color.r, 0.75f, kEpsilon);
    EXPECT_NEAR(color.g, 0.85f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}
