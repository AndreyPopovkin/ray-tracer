#ifndef RAY_TRACER_VISUALSIS
#define RAY_TRACER_VISUALSIS

#include "../geometry/point.h"
#include "../geometry/tetragon.h"
#include "../geometry/ray.h"
#include "../geometry/vector.h"

class VisualSys{
    Point eye;
    Tetragon screen;
    Vector direction;
    Vector leftDir;
    double precision;
    double width, height;
public:
    void build() {
        Point center = eye + direction;
        leftDir = leftDir;
        Vector upDir = (direction % leftDir);
        screen.p[0] = center + leftDir.scale(width / 2) + upDir.scale(height / 2);
        screen.p[1] = center - leftDir.scale(width / 2) + upDir.scale(height / 2);
        screen.p[2] = center - leftDir.scale(width / 2) - upDir.scale(height / 2);
        screen.p[3] = center + leftDir.scale(width / 2) - upDir.scale(height / 2);
    }
    VisualSys(const Point& p, const Vector& dir, const Vector& left, double w, double h) {
        eye = p;
        direction = dir;
        Vector ort = dir % left;
        leftDir = ort % dir;
        width = w;
        height = h;
        build();
    }
    VisualSys(const Point& p, const Tetragon& screen_) {
        eye = p;
        screen = screen_;
        // TODO
    }
    void shiftAlongAxis(double dpos, int axis) {
        if (axis == 0) eye.setx(eye.getx() + dpos);
        else if (axis == 1) eye.sety(eye.gety() + dpos);
        else if (axis == 2) eye.setz(eye.getz() + dpos);
        build();
    }
    Point getP(int id) {
        return screen.p[id];
    }
    Point getEye() {
        return eye;
    }
};

#endif
