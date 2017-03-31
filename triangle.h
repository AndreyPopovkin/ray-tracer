#ifndef RAY_TRACER_TRIANGLE
#define RAY_TRACER_TRIANGLE

#include "object.h"
#include <vector>
#include <iostream>

const double TRIANGLE_EPS = 1E-8;

// не наследуюсь от polygon, для улучшения производительности

class Triangle : public Object{
public:
    Point p1, p2, p3;
    Triangle(const Point&, const Point&, const Point&);
    Triangle();
    virtual std::pair<Ray, bool> intersect(const Ray&);
    virtual bool simple_intersect(const Ray&, double&);
    virtual ~Triangle();
    friend std::ostream& operator<<(std::ostream&, const Triangle&);
    virtual double maxPos(int axis);
    virtual double minPos(int axis);
};

#endif
