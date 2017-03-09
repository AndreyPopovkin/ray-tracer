#ifndef RAY_TRACER_POINT
#define RAY_TRACER_POINT

#include "vector.h"
#include <iostream>

class Point: public Vector{
	double x, y, z;
public:
	Point();
	Point(double, double, double);
	double getx() const;
	double gety() const;
	double getz() const;
	void setx(double);
	void sety(double);
	void setz(double);
	Point operator+ (const Vector&) const;
	Point operator- (const Vector&) const;
	Vector operator- (const Point&) const;
	void print() const;
};

#endif