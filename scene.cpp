#include "scene.h"
#include <chrono>

void Scene::pushSphere(const Sphere& sphere) {
    rayTracer.pushSphere(sphere);
}

void Scene::pushTriangle(const Triangle& triangle) {
    rayTracer.pushTriangle(triangle);
}

void Scene::pushTetragon(const Tetragon& tetragon) {
    rayTracer.pushTetragon(tetragon);
}

Scene::Scene(const Point& eye_, const Tetragon& screen_,
             int widthScreenResolution_, int heightScreenResolution_,
             int threadsNum_)
                : eye(eye_),
                  widthScreenResolution(widthScreenResolution_),
                  heightScreenResolution(heightScreenResolution_),
                  drawer(widthScreenResolution, heightScreenResolution),
                  threadsNum(threadsNum_)
                {
                    screen = screen_; 
                    heightPow = 0;
                    while ((1 << heightPow) < heightScreenResolution)
                        ++heightPow;
                }

const int threadsNum = 4;

int Scene::getDist(int x, int y) {
    int min_ = 1E9;
    int max_ = 0;
    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy) {
            min_ = std::min(min_, (int)drawer.getColor(x + dx, y + dy));
            max_ = std::max(max_, (int)drawer.getColor(x + dx, y + dy));
        }
    return max_ - min_;
}

int Scene::bitReverse(int n) {
    int ans = 0;
    for (int i = 0; i < heightPow; ++i)
        ans ^= (((n >> i) & 1) << (heightPow - i - 1));
    return ans;
}

void Scene::antiAliasing(int razor, int precision) {
    // razor отсекает пиксели, которые нет необходимости уточнять
    // precision -- корень из количества лучей
    Point start = screen.getP(0);
    Vector dx = (screen.getP(1) - screen.getP(0)) * (1. / widthScreenResolution);
    Vector dy = (screen.getP(2) - screen.getP(1)) * (1. / heightScreenResolution);
    Ray sight(eye, start - eye);
    std::vector<std::pair<std::pair<int, int>, int>> updates;
    for (int x = 1; x < widthScreenResolution - 1; ++x)
        for (int y = 1; y < heightScreenResolution - 1; ++y) {
            if (getDist(x, y) > razor) {
                int sum = 0;
                for (int ddx = -precision; ddx <= precision; ddx += 1)
                    for (int ddy = -precision; ddy <= precision; ddy += 1) {
                        sight.direction = (start + 
                            dx * (x + ddx / (double)(precision + 1)) + 
                            dy * (y + ddy / (double)(precision + 1))) - eye;
                        sum += getTracedColor(sight);
                    }
                updates.push_back({{x, y}, sum / precision * precision});
            }
        }
    for (auto p : updates)
        drawer.draw(p.first.first, p.first.second, p.second);
}

int Scene::getTracedColor(const Ray& sight) {
    std::pair<Ray, bool> intersection = rayTracer.traceRay(sight);
    if (!intersection.second) return 256 * 100;
    else {
        double bright = 20;
        for (auto star : stars) {
            Ray starRay(intersection.first.source, star.position - intersection.first.source);
            double cos_ = (starRay.direction.scale(1) * intersection.first.direction.scale(1));
            if (cos_ > 0 && !rayTracer.traceRay(starRay).second) {
                    bright += star.bright * cos_;
            }
        }
        bright = std::min(bright, (double)255);
        return bright;
    }
}

void Scene::updateByOneLines() {
    int y;
    Point start = screen.getP(0);
    Vector dx = (screen.getP(1) - screen.getP(0)) * (1. / widthScreenResolution);
    Vector dy = (screen.getP(2) - screen.getP(1)) * (1. / heightScreenResolution);
    Ray sight(eye, start - eye);
    while ((y = step_a.fetch_add(1)) < (1 << heightPow)) {
        y = bitReverse(y);
        if (y >= heightScreenResolution) continue;
        for (int x = 0; x < widthScreenResolution; ++x) {
            sight.direction = (start + dx * x + dy * y) - eye;
            drawer.draw(x, y, getTracedColor(sight));
        }
    }
}

void Scene::update() {
    auto begin = std::chrono::high_resolution_clock::now();

    step_a.store(0);

    std::vector<std::thread> threads;
    for (int i = 0; i < threadsNum; ++i)
        threads.emplace_back(updateByOneLines, this);

    while (step_a.load() < (1 << heightPow)) {
        drawer.update();
        if (!drawer.getWindowEvents())
            exit(0);
        SDL_Delay(1000 / 30);
    }

    for (auto i = threads.begin(); i != threads.end(); ++i)
        i->join();
    
    antiAliasing();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "all rays traced during " << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() / 1000. << "s" << std::endl;

    drawer.update();
}

void Scene::pushStar(const Star& star) {
    stars.push_back(star);
}

bool Scene::getWindowEvents() {
    drawer.update();
    return drawer.getWindowEvents();
}
