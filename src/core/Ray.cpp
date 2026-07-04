#include "Ray.h"

Ray::Ray(const Point3& origin, const Vec3& direction)
    : m_origin(origin)
    , m_direction(direction)
{
}

Ray::Point3 Ray::at(float t) const
{
    return m_origin + t * m_direction;
}
