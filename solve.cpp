#include <iostream>

class Point{
public:
  int x;
  Point (int x): x(x) {}
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "Point( " << p.x << " : " << p.x << " : " << p.x << " )";
    return os;
}

int main() {
    std::cout << Point(10) << "\n";
}