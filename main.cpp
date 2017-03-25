#include "header.h"

const int triangPrecision = 10;

Point getPoint(Sphere sphere, double sx, double sy) {
    double r = sphere.r;
    double a = (sx / triangPrecision) * 2 * PI;
    double b = (sy / triangPrecision) * PI;
    return sphere.center + Vector(r * cos(a) * sin(b), r * sin(a) * sin(b), r * cos(b));
}

void triangulateSphere(Scene& scene, Sphere sphere) {
    for (int i = 0; i < triangPrecision; ++i) {
        for (int q = 0; q < triangPrecision; ++q) {
            scene.pushTetragon(Tetragon(
                getPoint(sphere, i, q),
                getPoint(sphere, i, q + 1),
                getPoint(sphere, i + 1, q + 1),
                getPoint(sphere, i + 1, q)
            ));
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow )
{
    Tetragon screen(
            Point(320 / 4, 230 / 4 + 50, 4000),
            Point(-320 / 4, 230 / 4 + 50, 4000),
            Point(-320 / 4, -230 / 4 + 50, 4000),
            Point(320 / 4, -230 / 4 + 50, 4000)
        );
    Scene scene(Point(0, 0, 10000), screen);

    
    Parcer parcer("04.obj");

    auto v = parcer.parce();

    std::cout << v.first.size() << ' ' << v.second.size() << "\n";

    for (auto item : v.first)
        scene.pushTriangle(item);
    for (auto item : v.second)
        scene.pushTetragon(item);
    
    //scene.pushSphere(Sphere(Point(400, 0, 0), 250));
    //scene.pushSphere(Sphere(Point(100, 250, 0), 40));
    //scene.pushSphere(Sphere(Point(100, -250, 0), 40));
    //scene.pushSphere(Sphere(Point(100, 0, 250), 40));
    //triangulateSphere(scene, Sphere(Point(0, 50, 0), 40));
    //scene.pushSphere(Sphere(Point(0, 0, -250), 40));
    //scene.pushTriangle(Triangle(Point(100, 0, 0), Point(50, 100, 0), Point(50, 0, 100)));
    //scene.pushTriangle(Triangle(Point(100, 0, 0), Point(90, -100, 0), Point(60, 0, 100)));
    //scene.pushTriangle(Triangle(Point(100, 0, 0), Point(50, 100, 0), Point(70, 0, -100)));
    //scene.pushTriangle(Triangle(Point(100, 0, 0), Point(90, -100, 0), Point(80, 0, -100)));
    //scene.pushStar(Star(Point(-10000, 10000, 10000)));
    scene.pushStar(Star(Point(-10000, 4000, 10000)));
    //double t = clock();
    scene.update();
    //std::cout << (clock() - t) / CLOCKS_PER_SEC << "\n";
    while (scene.getWindowEvents()) SDL_Delay(200);

    return 0;
}