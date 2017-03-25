#ifndef RAY_TRACER_POLYGON
#define RAY_TRACER_POLYGON

#include "point.h"
#include "object.h"
#include "ray.h"
#include <vector>

class Polygon: public Object{
public:
    std::vector<Point> p;
    virtual std::pair<Ray, bool> intersect(const Ray&) = 0;
    virtual bool simple_intersect(const Ray&, double&) = 0;
    virtual ~Polygon() {}
};

#endif
