#include "header.h"

const int triangPrecision = 300;

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
            Point(4000, 320 / 300. / 3 + 2.5, -330 / 300. / 3),
            Point(4000, 320 / 300. / 3 + 2.5, 330 / 300. / 3),
            Point(4000, -320 / 300. / 3 + 2.5, 330 / 300. / 3),
            Point(4000, -320 / 300. / 3 + 2.5, -330 / 300. / 3)
        );
    Scene scene(Point(10000, 0, 0), screen, 640, 480, 4);
    
    /*
    Tetragon screen(
            Point(4000, 320 / 400. + 3.1, -330 / 400.),
            Point(4000, 320 / 400. + 3.1, 330 / 400.),
            Point(4000, -320 / 400. + 3.1, 330 / 400.),
            Point(4000, -320 / 400. + 3.1, -330 / 400.)
        );
    Scene scene(Point(10000, 3.1, 0), screen, 640, 480, 4);
    */
    Parcer parcer("Cartoon_female_base_model_002_clean_mesh.obj");
    scene.pushStar(Star(Point(10000, 1000, 1000)));
    

    //Parcer parcer("04.obj");

    /*
    Tetragon screen(
        Point(0, 320 / 2, -230 / 2),
        Point(0, 320 / 2, 230 / 2),
        Point(0, -320 / 2, 230 / 2),
        Point(0, -320 / 2, -230 / 2)
    );
    Scene scene(Point(-10000, 10000, 10000), screen, 640, 480, 4);
    scene.pushStar(Star(Point(10000, 1000, 1000)));
    Parcer parcer("Z3_OBJ.obj");
    */
    auto v = parcer.parce();
    std::cout << "all " << v.first.size() << "triangles\n";
    std::cout << "and " << v.second.size() << " tetragons loaded\n";

    for (auto item : v.first)
        scene.pushTriangle(item);
    for (auto item : v.second)
        scene.pushTetragon(item);
    
    /*
    Tetragon screen(
        Point(4000, -440, 320 ),
        Point(4000, 440, 320 ),
        Point(4000, 440, -320 ),
        Point(4000, -440, -320 )
    );
    Scene scene(Point(-10000, 0, 0), screen, 640, 480, 4);
    scene.pushStar(Star(Point(-10000, 1000, 1000)));
    scene.pushSphere(Sphere(Point(0, 0, 0), 100));
    */

    //scene.pushSphere(Sphere(Point(100, 250, 0), 40));
    //scene.pushSphere(Sphere(Point(100, -250, 0), 40));
    //scene.pushSphere(Sphere(Point(100, 0, 250), 40));
    //triangulateSphere(scene, Sphere(Point(0, 0, 0), 100));
    //scene.pushSphere(Sphere(Point(0, 0, -250), 40));
    //scene.pushTriangle(Triangle(Point(100, 0, 0), Point(50, 100, 0), Point(50, 0, 100)));
    //scene.pushTriangle(Triangle(Point(100, 0, 0), Point(90, -100, 0), Point(60, 0, 100)));
    //scene.pushTriangle(Triangle(Point(100, 0, 0), Point(50, 100, 0), Point(70, 0, -100)));
    //scene.pushTriangle(Triangle(Point(100, 0, 0), Point(90, -100, 0), Point(80, 0, -100)));
    //scene.pushStar(Star(Point(-10000, 10000, 10000)));
    //double t = clock();
    scene.update();
    //std::cout << (clock() - t) / CLOCKS_PER_SEC << "\n";
    while (scene.getWindowEvents()) SDL_Delay(200);

    return 0;
}