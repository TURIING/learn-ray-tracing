#include <gtest/gtest.h>
#include <core/Ray.h>

TEST(RayTest, ConstructionAndGetters) {
    Ray::Point3 origin(1.0f, 2.0f, 3.0f);
    Ray::Vec3 direction(0.0f, 0.0f, 1.0f);
    Ray ray(origin, direction);

    EXPECT_FLOAT_EQ(ray.origin().x, 1.0f);
    EXPECT_FLOAT_EQ(ray.origin().y, 2.0f);
    EXPECT_FLOAT_EQ(ray.origin().z, 3.0f);

    EXPECT_FLOAT_EQ(ray.direction().x, 0.0f);
    EXPECT_FLOAT_EQ(ray.direction().y, 0.0f);
    EXPECT_FLOAT_EQ(ray.direction().z, 1.0f);
}

TEST(RayTest, AtOrigin) {
    Ray::Point3 origin(0.0f, 0.0f, 0.0f);
    Ray::Vec3 direction(1.0f, 0.0f, 0.0f);
    Ray ray(origin, direction);

    Ray::Point3 p = ray.at(0.0f);
    EXPECT_FLOAT_EQ(p.x, 0.0f);
    EXPECT_FLOAT_EQ(p.y, 0.0f);
    EXPECT_FLOAT_EQ(p.z, 0.0f);
}

TEST(RayTest, AtPositiveT) {
    Ray::Point3 origin(1.0f, 2.0f, 3.0f);
    Ray::Vec3 direction(0.0f, 1.0f, 0.0f);
    Ray ray(origin, direction);

    Ray::Point3 p = ray.at(5.0f);
    EXPECT_FLOAT_EQ(p.x, 1.0f);
    EXPECT_FLOAT_EQ(p.y, 7.0f);
    EXPECT_FLOAT_EQ(p.z, 3.0f);
}

TEST(RayTest, AtNegativeT) {
    Ray::Point3 origin(1.0f, 0.0f, 0.0f);
    Ray::Vec3 direction(1.0f, 0.0f, 0.0f);
    Ray ray(origin, direction);

    Ray::Point3 p = ray.at(-2.0f);
    EXPECT_FLOAT_EQ(p.x, -1.0f);
    EXPECT_FLOAT_EQ(p.y, 0.0f);
    EXPECT_FLOAT_EQ(p.z, 0.0f);
}

TEST(RayTest, AtZeroT) {
    Ray::Point3 origin(4.0f, 5.0f, 6.0f);
    Ray::Vec3 direction(0.0f, 0.0f, -1.0f);
    Ray ray(origin, direction);

    Ray::Point3 p = ray.at(0.0f);
    EXPECT_FLOAT_EQ(p.x, 4.0f);
    EXPECT_FLOAT_EQ(p.y, 5.0f);
    EXPECT_FLOAT_EQ(p.z, 6.0f);
}
