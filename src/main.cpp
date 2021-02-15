/* Includes */

#include "vector.h"
#include "Camera.h"
#include "functions.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


/* Defines */

#define PI          3.14159265358979323846
#define WIDTH       800         /* Screen width */
#define HEIGHT      600         /* Screen height */
#define C_WIDTH     4           /* Width of each character in pixels */
#define C_HEIGHT    8           /* Height of each character in pixels */
const char palette[] = " .:;~=#OB8%&";

using namespace std;


/* Functions */

/* crossplatform sleep */
void crossSleep(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms);
#endif
}

/* set cursor at start to avoid flickering (avoid clearing screen) */
void gotoxy(short x, short y) {
#ifdef _WIN32
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("%c[%d;%df", 0x1B, y, x);
#endif
}


/* Main function */
int main(void)
{
    /* ball declaration */
    ball balls[3];
    balls[0].center.set(0, 0, 0);
    balls[0].radius = 1;
    balls[0].color = 1;
    balls[0].coeff = 0.9;
    balls[1].center.set(-3, 0, 0);
    balls[1].radius = 0.5;
    balls[1].color = 1;
    balls[1].coeff = 0.7;
    balls[2].center.set(0, -3, 0);
    balls[2].radius = 0.5;
    balls[2].color = 1;
    balls[2].coeff = 0.7;

    double alfa = 0;
    double beta = PI / 2;
    double r = 1.9;

    /* starting screen */
    for (int i = 0; i < HEIGHT / C_HEIGHT - 4; i++)
    {
        for (int j = 0; j < WIDTH / C_WIDTH; j++)
        {
            putchar('@');
        }
        putchar('\n');
    }
    getchar();
    gotoxy(0, 0);

    while (true)
    {
        char platno[HEIGHT / C_HEIGHT * (WIDTH / C_WIDTH + 1) + 1];
        Camera cam(r, alfa, beta);

        int p = 0;
        for (int i = 0; i < HEIGHT / C_HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH / C_WIDTH; j++)
            {
                Vector origin(cam.x, cam.y, cam.z);

                Vector unit(-((double)(j - WIDTH / C_WIDTH / 2) + 0.5) / (double)(WIDTH / C_WIDTH / 2),
                            ((double)(i - HEIGHT / C_HEIGHT / 2) + 0.5) / (double)(WIDTH / C_HEIGHT / 2),
                            -1);

                unit = unit.transformMatrixToVector(cam.matrix);
                unit.set(unit.getX() - cam.x, unit.getY() - cam.y, unit.getZ() - cam.z);
                unit.normalize();

                double luminance = cam.rayTrace(origin, unit, balls, 3, 2, 0.3, 5);
                int color = (int)((strlen(palette) - 1) * luminance);
                platno[p++] = palette[color];
            }
            platno[p++] = '\n';
        }
        platno[p] = 0;

        /* puts function is very fast */
        puts(platno);

        /* sleeping to reduce frames count, maybe there is a better way than sleeping to sync */
        crossSleep(5);

        /* instead of system("cls") i used this because it looks smoother */
        gotoxy(0, 0);

        /* update camera position, using very small angle increments to get a smoother transition */
        alfa += 0.0003 * PI;
        if (beta > PI / 2000)
        {
            beta -= 0.0003 * PI;
        }
    }
    return 0;
}
