#include "triangle.h"

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3)
            : p1(p1), p2(p2), p3(p3) {
    //p.push_back(p1);
    //p.push_back(p2);
    //p.push_back(p3);
}

Triangle::Triangle(const PolygonG& polygon) {
    p1 = polygon.p[0];
    p2 = polygon.p[1];
    p3 = polygon.p[2];
}

Triangle::Triangle() {
    //p.resize(3);
}

Triangle::~Triangle() {
    //std::cout << "!\n";
}
    
std::pair<Ray, bool> Triangle::intersect(const Ray& r) {
    //if (p.size() != 3) throw 1;
    Vector e1, e2;
    Vector P, Q, T;
    double det, inv_det, u, v;
    double t;

    //Find vectors for two edges sharing V1
    e1 = p2 - p1;
    e2 = p3 - p1;
    //Begin calculating determinant - also used to calculate u parameter
    P = r.direction % e2;
    //if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
    det = e1 * P;
    //NOT CULLING
    if (det > -TRIANGLE_EPS && det < TRIANGLE_EPS) return {Ray(), 0};
    inv_det = 1 / det;

    //calculate distance from V1 to ray origin
    T = r.source - p1;
    
    //Calculate u parameter and test bound
    u = T * P * inv_det;
    //The intersection lies outside of the triangle
    if (u < 0 || u > 1) return {Ray(), 0};

    //Prepare to test v parameter
    Q = T % e1;
    
    //Calculate V parameter and test bound
    v = r.direction * Q * inv_det;
    
    //The intersection lies outside of the triangle
    if (v < 0 || u + v  > 1) return {Ray(), 0};

    t = e2 * Q * inv_det;

    if (t > TRIANGLE_EPS) { //ray intersection
        Vector norm = (e1 % e2).scale(1);
        if (norm * r.direction < 0) {
            return {Ray(r.source + r.direction * t, norm), 1};
        }
        else {
            return {Ray(r.source + r.direction * t, -norm), 1};
        }
    }

    // No hit, no win
    return {Ray(), 0};
}

bool Triangle::simple_intersect(const Ray&, double&) {
    // TODO
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Triangle& p) {
    os << "Triangle( " << p.p1 << " : " << p.p2 << " : " << p.p3 << " )";
    return os;
}

double Triangle::maxPos(int axis) {
    return std::max(std::max(p1.maxPos(axis), p2.maxPos(axis)), p3.maxPos(axis));
}

double Triangle::minPos(int axis) {
    return std::min(std::min(p1.minPos(axis), p2.minPos(axis)), p3.minPos(axis));
}
