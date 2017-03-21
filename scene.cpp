#include "scene.h"

void Scene::pushSphere(const Sphere& sphere) {
    rayTracer.pushSphere(sphere);
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

void Scene::update() {
    Point start = screen.p[0];
    Vector dx = (screen.p[1] - screen.p[0]) * (1. / widthScreenResolution);
    Vector dy = (screen.p[2] - screen.p[1]) * (1. / heightScreenResolution);
    Ray sight(eye, start - eye);
    for (int x = 0; x < widthScreenResolution; ++x)
        for (int y = 0; y < heightScreenResolution; ++y) {
            sight.direction = (start + dx * x + dy * y) - eye;
            //std::cout << sight << "\n";
            std::pair<Ray, bool> intersection = rayTracer.traceRay(sight);
            if (!intersection.second) drawer.draw(x, y, 0);
            else {
                //std::cout << "some intersections\n";
                double bright = 40;
                for (auto star : stars) {
                    Ray starRay(intersection.first.source, star.position - intersection.first.source);
                    starRay.source = starRay.source - starRay.direction.scale(0.01);
                    if (!rayTracer.traceRay(starRay).second) {
                        bright += star.bright * sqrt(1 - (starRay.direction.scale(1) % intersection.first.direction.scale(1)).len());
                    }
                }
                drawer.draw(x, y, 256 * (int)bright);
            }
        }
    drawer.update();
}

void Scene::pushStar(const Star& star) {
    stars.push_back(star);
}