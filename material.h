#ifndef RAY_TRACER_MATERIAL
#define RAY_TRACER_MATERIAL

#include "colorRGB.h"

class Material{
public:
    ColorRGB color;
    double alpha;
    double reflect;
    double refract;
};

#endif
