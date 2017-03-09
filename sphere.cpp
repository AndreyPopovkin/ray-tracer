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

		//intersection.print();
		//int a;
		//std::cin >> a;
		return {Ray(intersection, normal), 1};
	} else {
		// TODO
		return {Ray(), 0};
	}
}

Sphere::Sphere() {}

Sphere::Sphere(const Point& p, double r): center(p), r(r) {}
