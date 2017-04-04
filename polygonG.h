#ifndef RAY_TRACER_POLYGONG
#define RAY_TRACER_POLYGONG

#include "point.h"
#include "object.h"
#include "ray.h"
#include <vector>

class PolygonG: public Object{
public:
    std::vector<Point> p;
    PolygonG(std::vector<Point>&&);
    PolygonG();

    virtual std::pair<Ray, bool> intersect(const Ray&);
    virtual bool simple_intersect(const Ray&, double&);
    virtual ~PolygonG();
    virtual double maxPos(int axis);
    virtual double minPos(int axis);
};

#endif
