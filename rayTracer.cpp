#include "rayTracer.h"

void RayTracer::pushSphere(const Sphere& sphere) {
    objects.push_back(new Sphere(sphere));
}

void RayTracer::pushTriangle(const Triangle& triangle) {
    objects.push_back(new Triangle(triangle));
}

void RayTracer::pushTetragon(const Tetragon& tetragon) {
    objects.push_back(new Tetragon(tetragon));
}

RayTracer::RayTracer() {}

std::pair<Ray, bool> RayTracer::traceRay(const Ray& ray) {
    if (tree.root == nullptr) {
        double distToNearest2 = -1;
        Ray answer;
        for (const auto& item : objects) {        
            auto intersection = item->intersect(ray);
            if (intersection.second) {
                double distance2 = (intersection.first.source - ray.source).len2();
                if (distToNearest2 < 0 || distance2 < distToNearest2) {
                    distToNearest2 = distance2;
                    answer = intersection.first;
                }
            }
        }
        return {answer, distToNearest2 >= 0};
    } else {
        auto ans = tree.traceRay(ray);
        return ans;
    }
}

void RayTracer::buildKD() {
    tree.build(objects);
}

RayTracer::~RayTracer() {
    for (auto item : objects)
        delete item;
}

void RayTracer::resetCounter() {
    tree.counter.store(0);
}

int RayTracer::count() {
    return tree.counter.load();
}
