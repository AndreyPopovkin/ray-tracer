#ifndef RAY_TRACER_TETRAGON
#define RAY_TRACER_TETRAGON

#include "polygon.h"
#include "triangle.h"
#include <vector>

class Tetragon: public Polygon{
public:
    //Point p1, p2, p3, p4;
    Tetragon(const Point&, const Point&, const Point&, const Point&);
    Tetragon();
    // добавлен для совместимости реализаций различного наследования
    Point getP(int);
    virtual ~Tetragon();
    virtual std::pair<Ray, bool> intersect(const Ray&);
    virtual bool simple_intersect(const Ray&, double&);
};

#endif
