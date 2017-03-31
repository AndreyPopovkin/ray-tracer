#include "polygon.h"

Polygon::~Polygon() {}

double Polygon::maxPos(int axis) {
    double ans = p[0].maxPos(axis);
    for (auto point : p)
        ans = std::max(ans, point.maxPos(axis));
    return ans;
}

double Polygon::minPos(int axis) {
    double ans = p[0].maxPos(axis);
    for (auto point : p)
        ans = std::min(ans, point.minPos(axis));
    return ans;
}
