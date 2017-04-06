#ifndef RAY_TRACER_COLORRGB
#define RAY_TRACER_COLORRGB

#include <cstdlib>
#include <string>

class ColorRGB{
public:
    double r, g, b;
    ColorRGB(double r, double g, double b) 
        : r(r), g(g), b(b) { }
    explicit ColorRGB(std::string colorName, double bright = 1) {
        if (colorName == "blue") {
            r = 0.3;
            g = 0.3;
            b = 1;
            this->applyBright(bright);
        } else if (colorName == "grey") {
            r = g = b = 1;
            this->applyBright(bright);
        } else if (colorName == "black")
            r = g = b = 0;
    }
    ColorRGB& applyBright(double bright) {
        r *= bright;
        g *= bright;
        b *= bright;
        return *this;
    }
    unsigned int getUint() {
        return ((int)(r * 255) << 16) + ((int)(g * 255) << 8) + ((int)(b * 255));
    }
};

#endif
