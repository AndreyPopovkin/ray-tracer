#ifndef RAY_TRACER_SPHERE
#define RAY_TRACER_SPHERE

#include "object.h"
#include <cmath>
#include <iostream>

class Sphere: public Object{
public:
	Point center;
	double r;
	virtual std::pair<Ray, bool> intersect(const Ray&);
	Sphere();
	Sphere(const Point&, double);
};

#endif
