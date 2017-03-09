#include "ray.h"

Ray::Ray() {}

Ray::Ray(double x, double y, double z, double dx, double dy, double dz)
	: source(x, y, z), direction(dx, dy, dz) {}
	
Ray::Ray(const Point& source, const Vector& direction)
	: source(source), direction(direction) {}