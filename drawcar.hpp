#include<graphics.h>


void drawCar(int x, int y) {
    // Draw the body of the car
    setcolor(RED);
    rectangle(x, y, x + 100, y + 50);

    // Draw the wheels of the car
    setcolor(BLACK);
    circle(x + 25, y + 75, 20);
    circle(x + 75, y + 75, 20);

    // Draw the windows of the car
    setcolor(WHITE);
    rectangle(x + 10, y + 10, x + 40, y + 40);
    rectangle(x + 60, y + 10, x + 90, y + 40);
}
