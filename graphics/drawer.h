#ifndef RAY_TRACER_DRAWER
#define RAY_TRACER_DRAWER

#include "..\SDL2mingw\x86_64-w64-mingw32\include\SDL2\SDL.h"
#include "colorRGB.h"
#include <string>
#include <iostream>
#include "encodePng.h"

class Drawer{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Window *window;
    Uint32* pixels;
    int widthScreenResolution;
    int heightScreenResolution;
public:
    Drawer(int = 500, int = 500);
    void update();
    void draw(int, int, ColorRGB);
    Uint32 getColor(int, int);
    bool getWindowEvents();
    void printPng(std::string filename);
    ~Drawer();
};

#endif
