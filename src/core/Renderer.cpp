#include "Renderer.h"
#include <cmath>

bool Renderer::hitSphere(const glm::vec3& center, float radius, const Ray& r)
{
    glm::vec3 oc = r.origin() - center;
    auto a = glm::dot(r.direction(), r.direction());
    auto b = 2.0f * glm::dot(oc, r.direction());
    auto c = glm::dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4.0f * a * c;
    return (discriminant > 0.0f);
}

float Renderer::hitSphereT(const glm::vec3& center, float radius, const Ray& r)
{
    glm::vec3 oc = r.origin() - center;
    auto a = glm::dot(r.direction(), r.direction());
    auto b = 2.0f * glm::dot(oc, r.direction());
    auto c = glm::dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f) {
        return -1.0f;
    } else {
        return (-b - std::sqrt(discriminant)) / (2.0f * a);
    }
}

glm::vec3 Renderer::background(const Ray& r)
{
    glm::vec3 unit_direction = glm::normalize(r.direction());
    auto t = 0.5f * (unit_direction.y + 1.0f);
    const glm::vec3 white(1.0f, 1.0f, 1.0f);
    const glm::vec3 blue(0.5f, 0.7f, 1.0f);
    return (1.0f - t) * white + t * blue;
}

glm::vec3 Renderer::rayColor(const Ray& r)
{
    auto t = hitSphereT(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r);
    if (t > 0.0f) {
        glm::vec3 N = glm::normalize(r.at(t) - glm::vec3(0.0f, 0.0f, -1.0f));
        return 0.5f * glm::vec3(N.x + 1.0f, N.y + 1.0f, N.z + 1.0f);
    }

    return background(r);
}