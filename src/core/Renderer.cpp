#include "Renderer.h"
#include <limits>

glm::vec3 Renderer::background(const Ray& r)
{
    glm::vec3 unit_direction = glm::normalize(r.direction());
    auto t = 0.5f * (unit_direction.y + 1.0f);
    const glm::vec3 white(1.0f, 1.0f, 1.0f);
    const glm::vec3 blue(0.5f, 0.7f, 1.0f);
    return (1.0f - t) * white + t * blue;
}

glm::vec3 Renderer::rayColor(const Ray& r, const Hittable& world)
{
    HitRecord rec;
    if (world.hit(r, 0.0f, std::numeric_limits<float>::max(), rec)) {
        return 0.5f * glm::vec3(rec.normal.x + 1.0f, rec.normal.y + 1.0f, rec.normal.z + 1.0f);
    }
    return background(r);
}