#include "Sphere.h"
#include <cmath>

Sphere::Sphere(const glm::vec3& center, float radius)
    : m_center(center), m_radius(radius)
{
}

bool Sphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const
{
    glm::vec3 oc = r.origin() - m_center;
    auto a = glm::dot(r.direction(), r.direction());
    auto half_b = glm::dot(oc, r.direction());
    auto c = glm::dot(oc, oc) - m_radius * m_radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant > 0.0f) {
        auto sqrtd = std::sqrt(discriminant);

        // 优先尝试较小的根（近交点）
        auto temp = (-half_b - sqrtd) / a;
        if (temp < tMax && temp > tMin) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            glm::vec3 outward_normal = (rec.p - m_center) / m_radius;
            rec.setFaceNormal(r, outward_normal);
            return true;
        }

        // 再尝试较大的根（远交点）
        temp = (-half_b + sqrtd) / a;
        if (temp < tMax && temp > tMin) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            glm::vec3 outward_normal = (rec.p - m_center) / m_radius;
            rec.setFaceNormal(r, outward_normal);
            return true;
        }
    }

    return false;
}
