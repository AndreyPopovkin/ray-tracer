#include "rayTracer.h"

void RayTracer::pushSphere(const Sphere& sphere) {
    objects.push_back(new Sphere(sphere));
}

RayTracer::RayTracer() {}

std::pair<Ray, bool> RayTracer::traceRay(const Ray& ray) const{
    double distToNearest2 = -1;
    Ray answer;
    //std::cout << ray << "\n";
    for (auto item : objects) {        
        auto intersection = item->intersect(ray);
        if (intersection.second) {
            double distance2 = (intersection.first.source - ray.source).len2();
            if (distToNearest2 < 0 || distance2 < distToNearest2) {
                distToNearest2 = distance2;
                answer = intersection.first;
            }
        }
    }
    //std::cout << distToNearest2 << "\n";
    return {answer, distToNearest2 >= 0};
}

