#ifndef RAY_TRACER_SCENE
#define RAY_TRACER_SCENE

#include <vector>
#include "sphere.h"
#include "ray.h"
#include "point.h"

class Scene{
    RayTracer rayTracer;
    Drawer drawer;
    std::vector<Star> stars;
    Tetragon screen;
    int heightScreenResolution;
    int widthScreenResolution;
    Point eye;
public:
    void pushSphere(const Sphere&);
    Scene(const Point&, const Tetragon&, int, int);
    void update();
    void pushStar(const Point&);
};

#endif
