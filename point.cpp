#include "point.h"

Point::Point(): x(0), y(0), z(0) {}

Point::Point(double x, double y, double z): x(x), y(y), z(z) {}

double Point::getx() const{
	return x;
}

double Point::gety() const{
	return y;
}

double Point::getz() const{
	return z;
}

void Point::setx(double x_) {
	x = x_;
}

void Point::sety(double y_) {
	y = y_;
}

void Point::setz(double z_) {
	z = z_;
}

Point Point::operator+ (const Vector& v) const{
	return Point(x + v.getx(), y + v.gety(), z + v.getz());
}

Point Point::operator- (const Vector& v) const{
	return Point(x - v.getx(), y - v.gety(), z - v.getz());
}

Vector Point::operator- (const Point& p) const{
	return Vector(x - p.getx(), y - p.gety(), z - p.getz());
}

void Point::print() const{
	std::cout << "(" <<  x << ' ' << y << ' ' << z << ")\n";
}
