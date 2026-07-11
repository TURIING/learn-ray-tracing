#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "core/Camera.h"

class CameraTest : public ::testing::Test {
protected:
    static constexpr float kEpsilon = 0.001f;
};

TEST_F(CameraTest, GetOrigin)
{
    Camera camera;
    glm::vec3 origin = camera.GetOrigin();

    EXPECT_NEAR(origin.x, 0.0f, kEpsilon);
    EXPECT_NEAR(origin.y, 0.0f, kEpsilon);
    EXPECT_NEAR(origin.z, 0.0f, kEpsilon);
}

TEST_F(CameraTest, GetLowerLeftCorner)
{
    Camera camera;
    glm::vec3 corner = camera.GetLowerLeftCorner();

    EXPECT_NEAR(corner.x, -2.0f, kEpsilon);
    EXPECT_NEAR(corner.y, -1.0f, kEpsilon);
    EXPECT_NEAR(corner.z, -1.0f, kEpsilon);
}

TEST_F(CameraTest, GetRayCenterPointsForward)
{
    Camera camera;
    // (0.5, 0.5) 应对应视口中心，光线指向 -z 方向
    Ray r = camera.GetRay(0.5f, 0.5f);

    EXPECT_NEAR(r.origin().x, 0.0f, kEpsilon);
    EXPECT_NEAR(r.origin().y, 0.0f, kEpsilon);
    EXPECT_NEAR(r.origin().z, 0.0f, kEpsilon);

    // 方向应为 (0, 0, -1)
    EXPECT_NEAR(r.direction().x, 0.0f, kEpsilon);
    EXPECT_NEAR(r.direction().y, 0.0f, kEpsilon);
    EXPECT_NEAR(r.direction().z, -1.0f, kEpsilon);
}

TEST_F(CameraTest, GetRayLowerLeftCorner)
{
    Camera camera;
    // (0, 0) 对应视口左下角
    Ray r = camera.GetRay(0.0f, 0.0f);

    glm::vec3 expectedDir = camera.GetLowerLeftCorner() - camera.GetOrigin();
    EXPECT_NEAR(r.direction().x, expectedDir.x, kEpsilon);
    EXPECT_NEAR(r.direction().y, expectedDir.y, kEpsilon);
    EXPECT_NEAR(r.direction().z, expectedDir.z, kEpsilon);
}
