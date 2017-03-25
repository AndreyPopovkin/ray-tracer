#ifndef RAY_TRACER_RAYTRACER
#define RAY_TRACER_RAYTRACER

#include <vector>
#include "sphere.h"
#include "triangle.h"
#include "ray.h"
#include "tetragon.h"

class RayTracer{
    std::vector<Object*> objects;
public:
    void pushTriangle(const Triangle&);
    void pushSphere(const Sphere&);
    void pushTetragon(const Tetragon&);
    RayTracer();
    std::pair<Ray, bool> traceRay(const Ray&) const;
    ~RayTracer();
};

#endif
