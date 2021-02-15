#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void CrossSleep(int ms) //crossplatform sleep
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms);
#endif
}

#include <cstring>
#include <iostream>

#include "Camera.h"
#include "functions.h"
#define PI 3.14159265358979323846
using namespace std;

// screen dimensions

#define WIDTH 800
#define HEIGHT 600

// width and height of each character in pixels
const int dW = 4, dH = 8;

// set cursor at start to avoid flickering
void gotoxy(short x, short y) {
#ifdef _WIN32
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("%c[%d;%df", 0x1B, y, x);
#endif
}
char palette[] = " .:;~=#OB8%&";

int main() {
    // ball declaration::
    ball balls[3];
    balls[0].center[0] = 0;
    balls[0].center[1] = 0;
    balls[0].center[2] = 0;
    balls[0].radius = 1;
    balls[0].color = 1;
    balls[0].coeff = 0.9;
    balls[1].center[0] = -3;
    balls[1].center[1] = 0;
    balls[1].center[2] = 0;
    balls[1].radius = 0.5;
    balls[1].color = 1;
    balls[1].coeff = 0.7;
    balls[2].center[0] = 0;
    balls[2].center[1] = -3;
    balls[2].center[2] = 0;
    balls[2].radius = 0.5;
    balls[2].color = 1;
    balls[2].coeff = 0.7;

    double alfa = 0, beta = PI / 2, r = 1.9;

    // starting screen
    for (int i = 0; i < HEIGHT / dH - 4; i++) {
        for (int j = 0; j < WIDTH / dW; j++) {
            putchar('@');
        }
        putchar('\n');
    }
    getchar();
    gotoxy(0, 0);

    while (1) {
        char platno[HEIGHT / dH * (WIDTH / dW + 1) + 1];
        Camera cam(r, alfa, beta);

        int p = 0;
        for (int i = 0; i < HEIGHT / dH; i++) {
            for (int j = 0; j < WIDTH / dW; j++) {
                double origin[3] = { cam.x, cam.y, cam.z };

                double unit[3] = {
                    -((double)(j - WIDTH / dW / 2) + 0.5) / (double)(WIDTH / dW / 2),
                    ((double)(i - HEIGHT / dH / 2) + 0.5) / (double)(WIDTH / dH / 2),
                    -1 };
                transformVector(unit, cam.matrix);
                unit[0] -= cam.x;
                unit[1] -= cam.y;
                unit[2] -= cam.z;
                normalize(unit);
                double luminance = cam.rayTrace(origin, unit, balls, 3, 2, 0.3, 5);
                int color = (int)((strlen(palette) - 1) * luminance);
                platno[p++] = palette[color];
            }
            platno[p++] = '\n';
        }
        platno[p] = 0;

        // display:
        // puts is very fast
        puts(platno);

        // sleeping to reduce frames count
        // maybe there is a better way than sleeping to sync
        CrossSleep(5);
        // instead of system("cls") i used this because it looks smoother
        gotoxy(0, 0);
        // update camera position
        // using very small angle increments to get a smoother transition
        alfa += 0.0003 * PI;
        if (beta > PI / 2000)
            beta -= 0.0003 * PI;
    }
    return 0;
}
