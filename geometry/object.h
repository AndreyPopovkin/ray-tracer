#ifndef RAY_TRACER_OBJECT
#define RAY_TRACER_OBJECT

#include "ray.h"
#include <utility>

class Object{
public:
    int id;

	// return normal ray-vector to surface in first intersection point
	virtual std::pair<Ray, bool> intersect(const Ray&) = 0;
    virtual bool simple_intersect(const Ray&, double&) = 0;
    virtual ~Object() {}

    // узнаем границы bouding-box'а, содержащего обьект, axis: 0 - x, 1 - y, 2 - z
    virtual double maxPos(int axis) = 0;
    virtual double minPos(int axis) = 0;
};

#endif