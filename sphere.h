#ifndef RAY_TRACER_SPHERE
#define RAY_TRACER_SPHERE

#include "object.h"
#include <cmath>
#include <iostream>

const double SPHERE_EPS = 1E-8;

class Sphere: public Object{
public:
	Point center;
	double r;
	virtual std::pair<Ray, bool> intersect(const Ray&);
    virtual bool simple_intersect(const Ray& ray, double&);
	Sphere();
	Sphere(const Point&, double);
    virtual ~Sphere();
    virtual double maxPos(int axis);
    virtual double minPos(int axis);
};

#endif
