#ifndef RAY_TRACER_DRAWER
#define RAY_TRACER_DRAWER

#include "SDL2/SDL.h"

class Drawer{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Window *window;
    Uint32 pixels[WINDOW_WIDTH * WINDOW_HEIGHT];
public:
    Drawer();
    void update();
    void draw(int, int, Uint32);
    void getWindowEvents();
    ~Drawer();
};

#endif
