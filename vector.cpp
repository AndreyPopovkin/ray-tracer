#include "vector.h"

Vector::Vector(): x(0), y(0), z(0) {}

Vector::Vector(double x, double y, double z): x(x), y(y), z(z) {}

double Vector::getx() const{
	return x;
}

double Vector::gety() const{
	return y;
}

double Vector::getz() const{
	return z;
}

void Vector::setx(double x_) {
	x = x_;
}

void Vector::sety(double y_) {
	y = y_;
}

void Vector::setz(double z_) {
	z = z_;
}

Vector Vector::operator+ (const Vector& v) const{
	return Vector(x + v.getx(), y + v.gety(), z + v.getz());
}

double Vector::operator* (const Vector& v) const{
	return x * v.getx() + y * v.gety() + z * v.getz();
}

Vector Vector::operator% (const Vector& v) const{
	return Vector(
		y * v.getz() - z * v.gety(), 
		-x * v.getz() + z * v.getx(),
		x * v.gety() - y * v.getx()
		);
}

double Vector::len2 () const{
	return x * x + y * y + z * z;
}

double Vector::len () const{
	return std::sqrt(len2());
}

Vector Vector::scale(double l) const{
	double L = len();
	return *this * (l / L);
}

Vector Vector::operator* (double l) const{
	return Vector(x * l, y * l, z * l);
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "Vector( " << v.x << " : " << v.y << " : " << v.z << " )";
    return os;
}

Vector operator -(const Vector& v) {
    return Vector(-v.x, -v.y, -v.z);
}
