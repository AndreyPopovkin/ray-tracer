#include "header.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow )
{
    Tetragon screen(
            Point(-4000, -320, -230),
            Point(-4000, 320, -230),
            Point(-4000, 320, 230),
            Point(-4000, -320, 230)
        );
    Scene scene(Point(-10000, 0, 0), screen);
    
    scene.pushSphere(Sphere(Point(400, 0, 0), 250));
    scene.pushSphere(Sphere(Point(100, 250, 0), 40));
    scene.pushStar(Star(Point(-10000, 10000, 10000)));
    scene.update();
    while (1);

    return 0;   
}