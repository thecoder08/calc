#include <xgfx/window.h>
#include <xgfx/drawing.h>
#include <math.h>
#include <stdio.h>

XEvent eventBuffer[100];

void transformCoords(float x, float y, int* screenX, int* screenY) {
    *screenX = x*96 + 320;
    *screenY = y*-96 + 240;
}

float f(float x, float t) {
    return powf(x, 4) + powf(x, 3) - 2*powf(x, 2) - 3*x + 1;
}

int main() {
    initWindow(640, 480, "Calculator");
    float t = 0;
    while(1) {
        int eventsRead = checkWindowEvents(eventBuffer, 100);
        for (int i = 0; i < eventsRead; i++) {
            XEvent event = eventBuffer[i];
            if (event.type == ClosedWindow) {
                return 0;
            }
        }
        rectangle(0, 0, 640, 480, 0x00000000);
        line(0, 240, 640, 240, 0x00ffffff);
        line(320, 0, 320, 480, 0x00ffffff);
        int oldX = 0;
        int oldY = 0;
        for (float x = -5; x < 5; x += 0.1) {
            int screenX;
            int screenY;
            transformCoords(x, f(x, t), &screenX, &screenY);
            line(oldX, oldY, screenX, screenY, 0x00ff0000);
            oldX = screenX;
            oldY = screenY;
        }
        oldX = 0;
        oldY = 0;
        for (float x = -5; x < 5; x += 0.1) {
            int screenX;
            int screenY;
            float h = 0.1;
            transformCoords(x, (f(x+h, t)-f(x, t))/h, &screenX, &screenY);
            line(oldX, oldY, screenX, screenY, 0x0000ff00);
            oldX = screenX;
            oldY = screenY;
        }
        oldX = 0;
        oldY = 0;
        for (float x = -5; x < 5; x += 0.1) {
            float h = 10;
            float sum = 0;
            for (int i = 0; i < x * h; i++) {
                sum += f(i/h, t);
            }
            int screenX;
            int screenY;
            transformCoords(x, sum/h, &screenX, &screenY);
            if (x >= 0) {
                line(oldX, oldY, screenX, screenY, 0x000000ff);
            }
            oldX = screenX;
            oldY = screenY;
        }
        oldX = 0;
        oldY = 0;
        for (float x = -5; x < 5; x += 0.1) {
            float h = 10;
            float sum = 0;
            for (int i = 0; i > x * h; i--) {
                sum -= f(i/h, t);
            }
            int screenX;
            int screenY;
            transformCoords(x, sum/h, &screenX, &screenY);
            if (x < 0) {
                line(oldX, oldY, screenX, screenY, 0x000000ff);
            }
            oldX = screenX;
            oldY = screenY;
        }
        /*int screenX;
        int screenY;
        transformCoords(0, sinf(t), &screenX, &screenY);
        printf("%f, %f, %d, %d\n", 0.0, sinf(t), screenX, screenY);
        line(0, 0, screenX, screenY, 0x000000ff);*/
        t += 0.01;
        updateWindow();
    }
}