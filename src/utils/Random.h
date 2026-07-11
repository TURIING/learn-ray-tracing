#pragma once

#include <random>

/**
 * @brief 随机浮点数工具
 *
 * 基于 std::mt19937 引擎和 std::uniform_real_distribution 生成随机浮点数。
 * 引擎在首次调用时使用 std::random_device 初始化种子。
 */

/**
 * @brief 生成 [0, 1) 范围内的随机浮点数
 * @return 范围 [0, 1) 内的随机 float
 */
inline float RandomFloat() {
    static std::mt19937 sEngine(std::random_device{}());
    static std::uniform_real_distribution<float> sDist(0.0f, 1.0f);
    return sDist(sEngine);
}

/**
 * @brief 生成 [min, max) 范围内的随机浮点数
 * @param min 下限（包含）
 * @param max 上限（不包含）
 * @return 范围 [min, max) 内的随机 float
 */
inline float RandomFloat(float min, float max) {
    return min + (max - min) * RandomFloat();
}
