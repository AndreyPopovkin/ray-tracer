#ifndef RAY_TRACER_TETRAGON
#define RAY_TRACER_TETRAGON

#include "point.h"
#include "object.h"
#include "ray.h"

class Tetragon: public Object{
public:
    vector<Point> p;
    Tetragon(const Point&, const Point&, const Point&, const Point&);
    virtual pair<Ray, bool> intersect(const Ray&);
};

#endif
