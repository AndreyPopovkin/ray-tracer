#ifndef RAY_TRACER_STAR
#define RAY_TRACER_STAR

#include "../SDL2mingw\x86_64-w64-mingw32\include\SDL2\SDL.h"
#include "../geometry/point.h"

class Star{
public:
    Point position;
    double bright;
    Uint32 color;
    Star(const Point&, double=0.7, Uint32=-1);
};

#endif
