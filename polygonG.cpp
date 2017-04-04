#include "polygonG.h"
#include "triangle.h"

PolygonG::~PolygonG() {}

double PolygonG::maxPos(int axis) {
    double ans = p[0].maxPos(axis);
    for (auto point : p)
        ans = std::max(ans, point.maxPos(axis));
    return ans;
}

double PolygonG::minPos(int axis) {
    double ans = p[0].maxPos(axis);
    for (auto point : p)
        ans = std::min(ans, point.minPos(axis));
    return ans;
}

PolygonG::PolygonG(std::vector<Point>&& p_) {
    p = std::move(p_);
}

PolygonG::PolygonG() {}

std::pair<Ray, bool> PolygonG::intersect(const Ray& ray) {
    for (int i = 1; i + 1 < (int)p.size(); ++i) {
        auto intsect = Triangle(p[0], p[i], p[i + 1]).intersect(ray);
        if (intsect.second) return intsect;
    }
    return {Ray(), 0};
}

bool PolygonG::simple_intersect(const Ray& ray, double& dist) {
    //TODO
    throw 1;
}