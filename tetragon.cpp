#include "tetragon.h"

Tetragon::Tetragon(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    p.push_back(p1);
    p.push_back(p2);
    p.push_back(p3);
    p.push_back(p4);
}

Tetragon::Tetragon() {}

std::pair<Ray, bool> Tetragon::intersect(const Ray&) {
    // TODO
    throw 1;
}
