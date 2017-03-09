#ifndef RAY_TRACER_SCENE
#define RAY_TRACER_SCENE

#include <vector>
#include "sphere.h"
#include "ray.h"
#include "point.h"  3

class Scene{
    RayTracer rayTracer;
    Drawer drawer;
    std::vector<Star> stars;
    Point eye;
public:
    void pushSphere(const Sphere&);
    Scene();
    void update();

};

#endif
