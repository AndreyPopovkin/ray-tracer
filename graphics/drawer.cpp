#include "drawer.h"

Drawer::Drawer(int widthScreenResolution_, int heightScreenResolution_) {
    heightScreenResolution = heightScreenResolution_;
    widthScreenResolution = widthScreenResolution_;
    pixels = new Uint32[heightScreenResolution * widthScreenResolution];
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("rayTracer", 100, 100, widthScreenResolution, heightScreenResolution, 0); 
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, widthScreenResolution, heightScreenResolution);
}

void Drawer::update() {
    SDL_UpdateTexture(texture, NULL, pixels, widthScreenResolution * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Drawer::draw(int x, int y, ColorRGB color) {
    pixels[y * widthScreenResolution + x] = color.getUint();
}

bool Drawer::getWindowEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            return 0;
        }
    }
    return 1;
}

Drawer::~Drawer() {
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window); 
    SDL_Quit(); 
}

Uint32 Drawer::getColor(int x, int y) {
    return pixels[y * widthScreenResolution + x];
}

void Drawer::printPng(std::string filename) {
    Encoder encoder;
    encoder.encode(widthScreenResolution, heightScreenResolution, pixels, filename);
}