#ifndef RAY_TRACER_DRAWER
#define RAY_TRACER_DRAWER

#include "SDL2mingw\x86_64-w64-mingw32\include\SDL2\SDL.h"

class Drawer{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Window *window;
    Uint32* pixels;
    int heightScreenResolution;
    int widthScreenResolution;
public:
    Drawer(int = 500, int = 500);
    void update();
    void draw(int, int, Uint32);
    void getWindowEvents();
    ~Drawer();
};

#endif
