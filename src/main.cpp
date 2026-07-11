#include "core/Renderer.h"
#include "core/Ray.h"
#include "core/Sphere.h"
#include "core/HittableList.h"
#include "core/Camera.h"
#include "utils/Image.h"
#include "utils/Log.hpp"
#include "utils/Random.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <memory>

int main() {
    Log::Instance().Init();

    // 图像尺寸
    const int imageWidth  = 800;
    const int imageHeight = 400;

    Image image(imageWidth, imageHeight, 3);

    // 场景：多物体
    HittableList world;
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));    // 主体球
    world.add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f)); // 大地平面球

    // 相机
    Camera camera;

    // 抗锯齿采样数
    constexpr int kSamplesPerPixel = 100;

    LOG_INFO("Starting render: {}x{} with {} samples per pixel", imageWidth, imageHeight, kSamplesPerPixel);

    for (int j = 0; j < imageHeight; ++j) {
        LOG_INFO("Scanlines remaining: {}", imageHeight - 1 - j);
        for (int i = 0; i < imageWidth; ++i) {
            glm::vec3 color(0.0f);
            for (int s = 0; s < kSamplesPerPixel; ++s) {
                // 子像素随机抖动：在像素范围内随机偏移
                auto u = (static_cast<float>(i) + RandomFloat()) / static_cast<float>(imageWidth);
                auto v = (static_cast<float>(imageHeight - 1 - j) + RandomFloat()) / static_cast<float>(imageHeight);
                Ray r = camera.GetRay(u, v);
                color += Renderer::rayColor(r, world);
            }
            color /= static_cast<float>(kSamplesPerPixel);

            // 钳位防止浮点溢出
            color = glm::clamp(color, 0.0f, 1.0f);

            image.setPixel(i, j, color);
        }
    }

    LOG_INFO("Done.");

    // 保存为 PNG 文件
    if (image.save("output.png")) {
        LOG_INFO("Image saved to output.png");
    } else {
        LOG_ERROR("Failed to save image!");
        Log::Instance().Shutdown();
        return 1;
    }

    Log::Instance().Shutdown();
    return 0;
}
