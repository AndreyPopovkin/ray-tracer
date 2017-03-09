#ifndef RAY_TRACER_RAYTRACER
#define RAY_TRACER_RAYTRACER

#include <vector>
#include "sphere.h"
#include "ray.h"

    class RayTracer{
std::vector<Object*> objects;
public:
    void pushSphere(const Sphere&);
    RayTracer();
    Ray traceRay(const Ray&) const;
};

#endif
