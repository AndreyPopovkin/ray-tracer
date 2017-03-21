#ifndef RAY_TRACER_SCENE
#define RAY_TRACER_SCENE

#include <vector>
#include "sphere.h"
#include "ray.h"
#include "point.h"
#include "star.h"
#include "tetragon.h"
#include "vector.h"
#include "drawer.h"
#include "rayTracer.h"
#include <iostream>

class Scene{
    Point eye;
    Tetragon screen;
    int widthScreenResolution;
    int heightScreenResolution;
    Drawer drawer;
    RayTracer rayTracer;
    std::vector<Star> stars;
public:
    void pushSphere(const Sphere&);
    Scene(const Point&, const Tetragon&, int=640, int=460);
    void update();
    void pushStar(const Star&);
};

#endif
