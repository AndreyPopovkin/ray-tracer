#include "header.h"

//#include "SDL2/SDL.h"

Uint32 get_color(Uint32 r=0, Uint32 g=0, Uint32 b=0, Uint32 a=0) {
  return r + (g << 8) + (b << 16) + (a << 24);
}

SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Window *window;

Uint32 pixels[WINDOW_WIDTH * WINDOW_HEIGHT];

const Uint32 BLUE = get_color(0, 0, 255);
const Uint32 RED = get_color(255);
const Uint32 GREEN = get_color(0, 255);

void get_events(){
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    cout << "get ev\n";
  }
}

void update() {
  SDL_UpdateTexture(texture, NULL, pixels, WINDOW_WIDTH * sizeof(Uint32));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void init() {
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("SDL2 Window", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0); 
  renderer = SDL_CreateRenderer(window, -1, 0);
  texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void clr_pixels() {
  memset(pixels, 255, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(Uint32));
}

void quit_() {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window); 
  SDL_Quit(); 
}

void draw(int x, int y, Uint32 color) {
  pixels[y * WINDOW_WIDTH + x] = color;
}

Uint32 grey(int bright) {
  return 0 + (0 << 8) + (bright << 16);
}

  vector<Sphere> spheres;
  vector<Point> stars;

void trace(int x, int y, int r){
  bool f = 0;
  for (auto sphere1 : spheres) {
    Ray R(Point(-10000, 0, 0), Vector(6000, x - WINDOW_WIDTH / 2, y - WINDOW_HEIGHT / 2));
    auto inter = sphere1.intersect(R);
    if (inter.second) {
      double bright = 10;
      for (auto star : stars) {
        R = Ray(inter.first.source, (star - inter.first.source));
        double add = 1 - (inter.first.direction.scale(1) % R.direction.scale(1)).len();
        R.source = R.source - R.direction.scale(0.01);
        for (auto sphere2 : spheres)
          if (sphere2.intersect(R).second)
            add = 0;
        bright += 180 * add;
      }
      for (int dx = 0; dx < r; ++dx)
          for (int dy = 0; dy < r; ++dy)
            draw(x + dx, y + dy, grey(min(255, (int)bright)));
      f = 1;
    }
  }
  if (!f) {
    for (int dx = 0; dx < r; ++dx)
      for (int dy = 0; dy < r; ++dy)
        draw(x + dx, y + dy, grey(0));
  }
}

Uint32 getMinMaxDiff(int x, int y, int r) {
  Uint32 min_ = (300 << 16);
  Uint32 max_ = 0;
  for (int i = -1; i <= 1; ++i)
    for (int q = -1; q <= 1; ++q) {
      min_ = min(min_, pixels[(y + i * r) * WINDOW_WIDTH + x + q * r]);
      max_ = max(max_, pixels[(y + i * r) * WINDOW_WIDTH + x + q * r]);
    }
  return max_ - min_;
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow )
{
  init();
  //clr_pixels();

  spheres.emplace_back(Point(400, 0, 0), 250);
  spheres.emplace_back(Point(100, 250, 0), 40);
  //spheres.emplace_back(Point(100, -50, -250), 50);
  //srand(1997);
  //for (int i = 0; i < 5; ++i) {
  //  spheres.emplace_back(Point(400 + rand() % 100, rand() % 600 - 300, rand() % 600 - 300), 100);
  //}
  stars.resize(2);

  double d2 = 0;
  for (double d = 0; d < 1000000; d += 0.01) {
    memset(pixels, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(Uint32));
    d2 += 0.03;
    double t = clock();
    stars[0] = Point(1000 * sin(d * 2 * PI), 1000 * cos(d * 2 * PI), 0);
    stars[1] = Point(1000 * sin(d2 * 2 * PI), 0, 1000 * cos(d2 * 2 * PI));
    for (int i = 0; i < WINDOW_WIDTH; i += 2) {
      for (int q = 0; q < WINDOW_HEIGHT; q += 2) {
        trace(i, q, 2);
      }
    }
    
    for (int i = 4; i < WINDOW_WIDTH - 4; i += 2) {
      for (int q = 4; q < WINDOW_HEIGHT - 4; q += 2) {
        if (getMinMaxDiff(i, q, 2) > (30 << 16)) {
          
          trace(i, q, 1);
          trace(i, q + 1, 1);
          //draw(i, q + 1, BLUE);
          trace(i + 1, q, 1);
          trace(i + 1, q + 1, 1);
        }
      }
    }

    cout << (clock() - t) / CLOCKS_PER_SEC << "\n";
    get_events();
    update();
  }


  SDL_Event event;
  bool quit = 0;
  bool leftMouseButtonDown = false;
  while (!quit)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = true;
        case SDL_MOUSEMOTION:
            if (leftMouseButtonDown)
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                for (int i = -3; i <= 3; ++i)
                  for (int q = -3; q <= 3; ++q)
                    pixels[(mouseY + i) * 640 + mouseX + q] = 0;
            }
            break;
        }
        update();
    }
  quit_();

  return 0;   
}
