#include "tetragon.h"

Tetragon::Tetragon(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    p.push_back(p1);
    p.push_back(p2);
    p.push_back(p3);
    p.push_back(p4);
}

Tetragon::Tetragon() {
    p.emplace_back();
    p.emplace_back();
    p.emplace_back();
    p.emplace_back();
}

Tetragon::~Tetragon() {}

Point Tetragon::getP(int ind) {
    return p[ind];
    /*
    if (ind == 0) return p1;
    else if (ind == 1) return p2;
    else if (ind == 2) return p3;
    else return p4;
    */
}

std::pair<Ray, bool> Tetragon::intersect(const Ray& r) {
    if (p.size() != 4) throw 1;
    auto intsect = Triangle(p[0], p[1], p[2]).intersect(r);
    if (intsect.second) return intsect;
    intsect = Triangle(p[2], p[3], p[0]).intersect(r);
    return intsect;
}

bool Tetragon::simple_intersect(const Ray&, double&) {
    // TODO
    throw 1;
}
