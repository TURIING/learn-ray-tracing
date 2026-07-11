#include <gtest/gtest.h>
#include "utils/Random.h"

TEST(RandomTest, RandomFloatInRange)
{
    for (int i = 0; i < 10000; ++i) {
        float value = RandomFloat();
        EXPECT_GE(value, 0.0f);
        EXPECT_LT(value, 1.0f);
    }
}

TEST(RandomTest, RandomFloatMinMaxInRange)
{
    const float kMin = 5.0f;
    const float kMax = 10.0f;

    for (int i = 0; i < 10000; ++i) {
        float value = RandomFloat(kMin, kMax);
        EXPECT_GE(value, kMin);
        EXPECT_LT(value, kMax);
    }
}

TEST(RandomTest, RandomFloatProducesVariation)
{
    // 连续调用应产生不同值（极低概率全相同）
    float first = RandomFloat();
    bool varied = false;
    for (int i = 0; i < 100; ++i) {
        if (RandomFloat() != first) {
            varied = true;
            break;
        }
    }
    EXPECT_TRUE(varied);
}
