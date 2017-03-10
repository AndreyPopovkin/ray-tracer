#include "drawer.h"

Drawer::Drawer() {
    SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("SDL2 Window", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0); 
        renderer = SDL_CreateRenderer(window, -1, 0);
        texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Drawer::update() {
    SDL_UpdateTexture(texture, NULL, pixels, WINDOW_WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    DL_RenderPresent(renderer);
}

void Drawer::draw(int x, int y, Uint32 color) {
    pixels[y * WINDOW_WIDTH + x] = color;
}

bool Drawer::getWindowEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            return 0;
            break;
        }
    }
    return 1;
}

Drawer::~Drawer() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window); 
    SDL_Quit(); 
}
