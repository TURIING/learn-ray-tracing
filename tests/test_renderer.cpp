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

// ============================================================
// 天空背景测试
// ============================================================

TEST_F(RendererTest, RayStraightUpReturnsBlue)
{
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 color = Renderer::background(r);

    EXPECT_NEAR(color.r, 0.5f, kEpsilon);
    EXPECT_NEAR(color.g, 0.7f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}

TEST_F(RendererTest, RayStraightDownReturnsWhite)
{
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    glm::vec3 color = Renderer::background(r);

    EXPECT_NEAR(color.r, 1.0f, kEpsilon);
    EXPECT_NEAR(color.g, 1.0f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}

TEST_F(RendererTest, RayHorizontalReturnsMixed)
{
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec3 color = Renderer::background(r);

    EXPECT_NEAR(color.r, 0.75f, kEpsilon);
    EXPECT_NEAR(color.g, 0.85f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}

TEST_F(RendererTest, RayNormalizationIsApplied)
{
    // 传入非单位方向向量，验证内部做了归一化
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f));
    glm::vec3 color = Renderer::background(r);

    EXPECT_NEAR(color.r, 0.5f, kEpsilon);
    EXPECT_NEAR(color.g, 0.7f, kEpsilon);
    EXPECT_NEAR(color.b, 1.0f, kEpsilon);
}

TEST_F(RendererTest, RayAtFortyFiveDegrees)
{
    float s = std::sqrt(2.0f) / 2.0f;
    Ray r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, s, s));
    glm::vec3 color = Renderer::background(r);

    float t = 0.5f * (s + 1.0f);
    glm::vec3 expected = (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);

    EXPECT_NEAR(color.r, expected.r, kEpsilon);
    EXPECT_NEAR(color.g, expected.g, kEpsilon);
    EXPECT_NEAR(color.b, expected.b, kEpsilon);
}

TEST_F(RendererTest, ColorComponentsInRange)
{
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
        glm::vec3 color = Renderer::background(r);

        EXPECT_GE(color.r, 0.0f);
        EXPECT_LE(color.r, 1.0f);
        EXPECT_GE(color.g, 0.0f);
        EXPECT_LE(color.g, 1.0f);
        EXPECT_GE(color.b, 0.0f);
        EXPECT_LE(color.b, 1.0f);
    }
}
