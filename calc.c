#include <xgfx/window.h>
#include <xgfx/drawing.h>
#include <math.h>
#include "lerp.h"

void transformCoords(float x, float y, int* screenX, int* screenY) {
    *screenX = x*96 + 320;
    *screenY = -y*96 + 240;
}

float f(float x, float time) {
    return powf(x,3)+(sinf(time)-1)*x;
}

vec2 a;
vec2 b = {-1, 0};
vec2 c = {1, 0};
vec2 d;

int main() {
    initWindow(640, 480, "Calculator");
    float time = 5;
    while(1) {
        Event event;
        while (checkWindowEvent(&event)) {
            if (event.type == WINDOW_CLOSE) {
                return 0;
            }
        }
        clear();
        line(0, 240, 640, 240, 0x00ffffff);
        line(320, 0, 320, 480, 0x00ffffff);
        int oldX;
        int oldY;
        int screenX;
        int screenY;
        for (float x = -5; x < 5; x += 0.1) {
            transformCoords(x, f(x, time), &screenX, &screenY);
            if (x > -5) {
                line(oldX, oldY, screenX, screenY, 0x00ff0000);
            }
            oldX = screenX;
            oldY = screenY;
        }
        for (float x = -5; x < 5; x += 0.1) {
            float h = 0.1;
            transformCoords(x, (f(x+h, time)-f(x, time))/h, &screenX, &screenY);
            if (x > -5) {
                line(oldX, oldY, screenX, screenY, 0x0000ff00);
            }
            oldX = screenX;
            oldY = screenY;
        }
        for (float x = 0; x < 5; x += 0.1) {
            float h = 10;
            float sum = 0;
            for (int i = 0; i < round(x*h); i++) {
                sum += f(i/h, time);
            }
            transformCoords(x, sum/h, &screenX, &screenY);
            if (x > 0) {
                line(oldX, oldY, screenX, screenY, 0x000000ff);
            }
            oldX = screenX;
            oldY = screenY;
        }
        for (float x = -5; x < 0; x += 0.1) {
            float h = 10;
            float sum = 0;
            for (int i = 0; i > x * h; i--) {
                sum -= f(i/h, time);
            }
            transformCoords(x, sum/h, &screenX, &screenY);
            if (x > -5) {
                line(oldX, oldY, screenX, screenY, 0x000000ff);
            }
            oldX = screenX;
            oldY = screenY;
        }
        a[0] = sinf(time) - 1;
        a[1] = cosf(time);

        d[0] = -sinf(time) + 1;
        d[1] = -cosf(time);

        int aX;
        int aY;
        transformCoords(a[0], a[1], &aX, &aY);
        int bX;
        int bY;
        transformCoords(b[0], b[1], &bX, &bY);
        int cX;
        int cY;
        transformCoords(c[0], c[1], &cX, &cY);
        int dX;
        int dY;
        transformCoords(d[0], d[1], &dX, &dY);
        line(aX, aY, bX, bY, 0x00ff00ff);
        line(bX, bY, cX, cY, 0x00ff00ff);
        line(cX, cY, dX, dY, 0x00ff00ff);

        for (float t = 0; t < 1.01; t += 0.05) {
            vec2 p;
            cubicBezier(a, b, c, d, p, t);
            transformCoords(p[0], p[1], &screenX, &screenY);
            if (t != 0) {
                line(oldX, oldY, screenX, screenY, 0x0000ffff);
            }
            oldX = screenX;
            oldY = screenY;
        }

        time += 0.01;
        updateWindow();
    }
}
