#ifndef RAY_TRACER_SCENE
#define RAY_TRACER_SCENE

#include <vector>
#include <mutex>
#include <atomic>
#include "sphere.h"
#include "ray.h"
#include "point.h"
#include "star.h"
#include "tetragon.h"
#include "triangle.h"
#include "vector.h"
#include "drawer.h"
#include "rayTracer.h"
#include <thread>
#include <iostream>

class Scene{
    Point eye;
    Tetragon screen;
    int widthScreenResolution;
    int heightScreenResolution;
    int heightPow;
    Drawer drawer;
    RayTracer rayTracer;
    int threadsNum;
    std::vector<Star> stars;
    std::mutex mutex;
    std::atomic<int> step_a;
    void updateByOneLines();
    int getDist(int, int);
    int bitReverse(int);
public:
    // экспериментально, сильно замедляет рендеринг
    void antiAliasing(int razor=40, int precision=2);

    int getTracedColor(const Ray&);
    void pushTetragon(const Tetragon&);
    void pushTriangle(const Triangle&);
    void pushSphere(const Sphere&);
    Scene(const Point&, const Tetragon&, int widthScreenResolution=640, 
            int heightScreenResolution=460, int threadsNum=4);
    void update();
    void pushStar(const Star&);
    bool getWindowEvents();
};

#endif
