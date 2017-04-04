#ifndef RAY_TRACER_SCENE
#define RAY_TRACER_SCENE

#include <vector>
#include <mutex>
#include <atomic>
#include "polygonG.h"
#include "sphere.h"
#include "ray.h"
#include "point.h"
#include "star.h"
#include "tetragon.h"
#include "triangle.h"
#include "vector.h"
#include "drawer.h"
#include "rayTracer.h"
#include "visualSys.h"
#include <thread>
#include <iostream>

class Scene{
    VisualSys screen;
    int widthScreenResolution;
    int heightScreenResolution;
    int heightPow;
    Drawer drawer;
    RayTracer rayTracer;
    int threadsNum;
    std::vector<Star> stars;
    std::mutex mutex;
    std::atomic<int> step_a;
    bool buildedKD;
    void updateByOneLines();
    int getDist(int, int);
    int bitReverse(int);
public:
    // экспериментально, сильно замедляет рендеринг
    void antiAliasing(int razor=40, int precision=1);

    ColorRGB getTracedColor(const Ray&);
    void pushTetragon(const Tetragon&);
    void pushTriangle(const Triangle&);
    void pushPolygon(const PolygonG&);
    void pushSphere(const Sphere&);
    Scene(const Point&, const Tetragon&, int widthScreenResolution_=640, 
            int heightScreenResolution_=460, int threadsNum_=4);
    Scene(const VisualSys&, int widthScreenResolution_=640, 
            int heightScreenResolution_=460, int threadsNum_=4);
    void update();
    void pushStar(const Star&);
    bool getWindowEvents();
    void shiftAlongAxis(double, int);
};

#endif
