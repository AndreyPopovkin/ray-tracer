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
             int widthScreenResolution_, int heightScreenResolution_)
                : eye(eye_),
                  widthScreenResolution(widthScreenResolution_),
                  heightScreenResolution(heightScreenResolution_),
                  drawer(widthScreenResolution, heightScreenResolution) 
                {
                    screen = screen_; 
                }

const int num_of_threads = 4;

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

void Scene::antiAliasing() {
    Point start = screen.getP(0);
    Vector dx = (screen.getP(1) - screen.getP(0)) * (1. / widthScreenResolution);
    Vector dy = (screen.getP(2) - screen.getP(1)) * (1. / heightScreenResolution);
    Ray sight(eye, start - eye);
    std::vector<std::pair<std::pair<int, int>, int>> updates;
    for (int x = 1; x < widthScreenResolution - 1; ++x)
        for (int y = 1; y < heightScreenResolution - 1; ++y) {
            if (getDist(x, y) > 40) {
                int sum = 0;
                for (int ddx = -1; ddx <= 1; ddx += 2)
                    for (int ddy = -1; ddy <= 1; ddy += 2) {
                        sight.direction = (start + dx * (x + ddx / 2.) + dy * (y + ddy / 2.)) - eye;
                        sum += getTracedColor(sight);
                    }
                //drawer.draw(x, y, sum / 4);
                updates.push_back({{x, y}, sum / 4});
            }
        }
    for (auto p : updates)
        drawer.draw(p.first.first, p.first.second, p.second);
}

int Scene::getTracedColor(const Ray& sight) {
    std::pair<Ray, bool> intersection = rayTracer.traceRay(sight);
    if (!intersection.second) return 0;
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

void Scene::updateByOneThread(int x1, int y1, int x2, int y2) {
    Point start = screen.getP(0);
    Vector dx = (screen.getP(1) - screen.getP(0)) * (1. / widthScreenResolution);
    Vector dy = (screen.getP(2) - screen.getP(1)) * (1. / heightScreenResolution);
    Ray sight(eye, start - eye);
    for (int x = x1; x < x2; ++x)
        for (int y = y1; y < y2; ++y) {
            sight.direction = (start + dx * x + dy * y) - eye;
            drawer.draw(x, y, getTracedColor(sight));
        }
}

void Scene::update() {
    auto begin = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    for (int i = 0; i < num_of_threads; ++i)
        threads.emplace_back(updateByOneThread, this,
                                widthScreenResolution * i / num_of_threads, 0, 
                                widthScreenResolution * (i + 1) / num_of_threads, heightScreenResolution);
    
    for (auto i = threads.begin(); i != threads.end(); ++i)
        i->join();

    //antiAliasing();

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
