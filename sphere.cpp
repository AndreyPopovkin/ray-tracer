#include "sphere.h"
#include <cmath>

std::pair<Ray, bool> Sphere::intersect(const Ray& ray) {
	Vector toCenter = (center - ray.source);
	if (toCenter.len2() > r * r) {
		if (toCenter * ray.direction < 0) return {Ray(), 0};
		double distance = std::sqrt((toCenter % ray.direction).len2() / ray.direction.len2());
		if (distance > r) return {Ray(), 0};
		double lenToDistancePoint = std::sqrt(toCenter.len2() - distance * distance);
		double distanceToSurface = lenToDistancePoint - std::sqrt(r * r - distance * distance);
		Point intersection = ray.source + ray.direction.scale(distanceToSurface);
		Vector normal = (intersection - center).scale(1);
		return {Ray(intersection, normal), 1};
	} else {
		// TODO
		return {Ray(), 0};
	}
}

bool Sphere::simple_intersect(const Ray& ray, double& dist) {
	Vector k = ray.source - center;
	double b = k * ray.direction;
	double c = k * k - r * r;
	double d = b * b - c;

	if (d >= 0) {
		double sqrtfd = sqrt(d);

		double t1 = -b + sqrtfd;
		double t2 = -b - sqrtfd;

		double min_t  = std::min(t1,t2);
		double max_t = std::max(t1,t2);

		double t = (min_t >= 0) ? min_t : max_t;

		dist = t;

		return (t > SPHERE_EPS);
	}
	return 0;
}

Sphere::Sphere() {}

Sphere::~Sphere() {}

Sphere::Sphere(const Point& p, double r): center(p), r(r) {}
