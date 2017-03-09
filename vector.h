#ifndef RAY_TRACER_VECTOR
#define RAY_TRACER_VECTOR

#include <cmath>

class Vector{
	double x, y, z;
public:
	Vector();
	Vector(double, double, double);
	double getx() const;
	double gety() const;
	double getz() const;
	void setx(double);
	void sety(double);
	void setz(double);
	Vector operator+ (const Vector&) const;
	double operator* (const Vector&) const;
	Vector operator% (const Vector&) const;
	double len2() const;
	double len() const;
	Vector scale(double) const;
	Vector operator* (double) const;
};

#endif