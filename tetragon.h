#ifndef RAY_TRACER_TETRAGON
#define RAY_TRACER_TETRAGON

#include "point.h"
#include "object.h"
#include "ray.h"
#include <vector>

class Tetragon: public Object{
public:
    std::vector<Point> p;
    Tetragon(const Point&, const Point&, const Point&, const Point&);
    Tetragon();
    virtual std::pair<Ray, bool> intersect(const Ray&);
};

#endif
