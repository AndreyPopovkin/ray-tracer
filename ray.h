#ifndef RAY_TRACER_RAY
#define RAY_TRACER_RAY

#include "vector.h"
#include "point.h"

class Ray{
public:
	Point source;
	Vector direction;
	Ray();
	Ray(double, double, double, double, double, double);
	Ray(const Point&, const Vector&);
};

std::ostream& operator<<(std::ostream&, const Ray&);

#endif