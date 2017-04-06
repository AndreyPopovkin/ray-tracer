#include <algorithm>
#include <cmath>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <cmath>
#include <chrono>
#include <atomic>
#include <string>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const double PI = 3.14159265359;

#include "SDL2mingw\x86_64-w64-mingw32\include\SDL2\SDL.h"
#include "render/scene.h"
#include "render/parcer.h"
#include "render/visualSys.h"

const int triangPrecision = 50;
std::string pngName = "test.png";

Point getPoint(Sphere sphere, double sx, double sy) {
    double r = sphere.r;
    double a = (sx / triangPrecision) * 2 * PI;
    double b = (sy / triangPrecision) * PI;
    return sphere.center + Vector(r * cos(a) * sin(b), r * sin(a) * sin(b), r * cos(b));
}

void triangulateSphere(Scene* scene, Sphere sphere) {
    for (int i = 0; i < triangPrecision; ++i) {
        for (int q = 0; q < triangPrecision; ++q) {
            scene->pushTetragon(Tetragon(
                getPoint(sphere, i, q),
                getPoint(sphere, i, q + 1),
                getPoint(sphere, i + 1, q + 1),
                getPoint(sphere, i + 1, q)
            ));
        }
    }
}

void parce_obj(Scene*& scene, std::string fileName) {
    Parcer parcer(fileName);
    
    auto v = parcer.parce();
    
    for (auto item : v) 
        if (item.p.size() == 3)
            scene->pushTriangle((Triangle)(item));
        else scene->pushPolygon(item);
}

void prepare_mersedes(Scene*& scene) {
    scene = new Scene(VisualSys(
                    Point(-10000, 20, 0),
                    Vector(6000, 0, 0),
                    Vector(0, 0, -1),
                    50, 50
                ),
                900, 900
            );
    scene->pushStar(Star(Point(-10000, 3000, 3000)));
    pngName = "mersedes.png";
    parce_obj(scene, "resource/Z3_OBJ.obj");
}

void prepare_female(Scene*& scene) {
    scene = new Scene(VisualSys(
                    Point(10000, 4.1, 0),
                    Vector(-6000, 0, 0),
                    Vector(0, 0, 1),
                    0.5, 0.5
                ));
    scene->pushStar(Star(Point(10000, 1000, 1000)));
    pngName = "female.png";

    parce_obj(scene, "resource/Cartoon_female_base_model_002_clean_mesh.obj");
}

void prepare_audi(Scene*& scene) {
    scene = new Scene(VisualSys(
                    Point(0, 2, 10000),
                    Vector(0, 0, -6000),
                    Vector(-1, 0, 0),
                    4, 3
                ),
                800, 600
            );
    scene->pushStar(Star(Point(-10000, 10000, 10000)));
    //scene->pushStar(Star(Point(-10000, 10000, 10000)));
    pngName = "audi.png";

    parce_obj(scene, "resource/Audi+RS7+Sport+Perfomance.obj");
}

void prepare_triangulated_sphere(Scene*& scene) {
    scene = new Scene(VisualSys(
                    Point(-10000, 0, 0),
                    Vector(6000, 0, 0),
                    Vector(0, 0, 1),
                    200, 150
                ));
    scene->pushStar(Star(Point(-10000, 1000, -10000)));
    pngName = "triSphere.png";

    triangulateSphere(scene, Sphere(Point(0, 0, 0), 100));
}

void prepare_sphere(Scene*& scene) {
    scene = new Scene(VisualSys(
                    Point(-10000, 0, 0),
                    Vector(6000, 0, 0),
                    Vector(0, 0, 1),
                    200, 150
                ));
    scene->pushStar(Star(Point(-10000, 1000, -10000)));
    pngName = "sphere.png";
    
    scene->pushSphere(Sphere(Point(0, 0, 0), 100));
}

void prepare_test(Scene*& scene) {
    scene = new Scene(VisualSys(
                    Point(-10000, 0, 0),
                    Vector(6000, 0, 0),
                    Vector(0, 0, 1),
                    200, 200
                ),
                800, 800
            );
    scene->pushStar(Star(Point(-10000, -10000, -10000)));
    scene->pushStar(Star(Point(-10000, 10000, -10000)));
    scene->pushStar(Star(Point(-10000, 10000, 10000)));
    scene->pushStar(Star(Point(-10000, -10000, 10000)));
    
    scene->pushSphere(Sphere(Point(0, 0, 0), 30));
    scene->pushTetragon(Tetragon(
            Point(30, -150, 150),
            Point(30, 150, 150),
            Point(30, 150, -150),
            Point(30, -150, -150)
        ));
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow )
{
    Scene* scene = nullptr;
    //prepare_mersedes(scene);
    //prepare_female(scene);
    //prepare_triangulated_sphere(scene);
    //prepare_sphere(scene);
    prepare_audi(scene);
    //prepare_test(scene);

    if (scene == nullptr) {
        std::cout << "prepare returns nullptr :(\n";
        return 0;
    }
    scene->update();
    scene->printPng(pngName);
    while (scene->getWindowEvents()) {
        SDL_Delay(200);
    }

    return 0;
}