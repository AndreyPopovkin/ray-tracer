#ifndef RAY_TRACER_OBJECT
#define RAY_TRACER_OBJECT

#include "ray.h"
#include <utility>

class Object{
public:
	// return normal ray-vector to surface in first intersection point
	virtual std::pair<Ray, bool> intersect(const Ray&) = 0;
};

#endif