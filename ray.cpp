#include "ray.h"

Ray::Ray() {}

Ray::Ray(double x, double y, double z, double dx, double dy, double dz)
	: source(x, y, z), direction(dx, dy, dz) {}
	
Ray::Ray(const Point& source, const Vector& direction)
	: source(source), direction(direction) {}

std::ostream& operator<<(std::ostream& os, const Ray& ray) {
    os << "Ray( source: " << ray.source << ", direction: " << ray.direction << " )";
    return os;
}