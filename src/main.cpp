#include "core/Renderer.h"
#include "core/Ray.h"
#include "utils/Image.h"
#include <glm/glm.hpp>
#include <iostream>

int main() {
    // 图像尺寸
    const int image_width  = 400;
    const int image_height = 200;

    Image image(image_width, image_height, 3);

    // 视口参数（虚拟成像平面）
    // 光线方程: P(t) = origin + t * direction
    // 其中 direction = lower_left_corner + u*horizontal + v*vertical
    const glm::vec3 lower_left_corner(-2.0f, -1.0f, -1.0f); // 视口左下角
    const glm::vec3 horizontal(4.0f, 0.0f, 0.0f);            // 视口水平跨度（从左到右）
    const glm::vec3 vertical(0.0f, 2.0f, 0.0f);              // 视口垂直跨度（从下到上）
    const glm::vec3 origin(0.0f, 0.0f, 0.0f);                // 相机/眼睛位置（光线起点）

    for (int j = 0; j < image_height; ++j) {
        std::cerr << "\rScanlines remaining: " << (image_height - 1 - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // 计算像素中心的 uv 坐标
            // j=0 对应图片顶部 → v 接近 1.0 → 天空
            // j=height-1 对应图片底部 → v 接近 0.0 → 地平线
            auto u = static_cast<float>(i) / static_cast<float>(image_width);
            auto v = static_cast<float>(image_height - 1 - j) / static_cast<float>(image_height);

            // 生成光线
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);

            // 计算颜色
            glm::vec3 color = Renderer::rayColor(r);

            // 将线性颜色 [0,1] 转换为 [0,255] 并写入图像
            int ir = static_cast<int>(255.99f * color.r);
            int ig = static_cast<int>(255.99f * color.g);
            int ib = static_cast<int>(255.99f * color.b);
            image.setPixel(i, j, static_cast<unsigned char>(ir),
                           static_cast<unsigned char>(ig),
                           static_cast<unsigned char>(ib));
        }
    }

    std::cerr << "\nDone.\n";

    // 保存为 PNG 文件
    if (image.save("output.png")) {
        std::cout << "Image saved to output.png" << std::endl;
    } else {
        std::cerr << "Failed to save image!" << std::endl;
        return 1;
    }

    return 0;
}
