#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define MAX_PARTICLES 1000
#define PARTICLE_LIFETIME 20
#define MAX_COLOR 256
#define GRAVITY -0.5
#define WIND 0.05

typedef struct {
    float x, y;
    float vx, vy;
    int color;
    int lifetime;
} Particle;

Particle particles[MAX_PARTICLES];

int getRandomColor() {
    return RGB(rand() % 256, rand() % 256, rand() % 256);
}

void initParticle(Particle *p, int cx, int cy, int radius) {
    float angle = (float)rand() / RAND_MAX * 2 * M_PI;
    float speed = (float)rand() / RAND_MAX * 2;
    float radiusOffset = (float)rand() / RAND_MAX * radius * 2; 

    p->x = cx + cos(angle) * radiusOffset;
    p->y = cy + sin(angle) * radiusOffset;
    p->vx = cos(angle) * speed;
    p->vy = sin(angle) * speed;
    p->color = COLOR(rand() % MAX_COLOR, rand() % MAX_COLOR, rand() % MAX_COLOR);
    p->lifetime = rand() % PARTICLE_LIFETIME;
}

void initParticles(int cx, int cy, int radius) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        initParticle(&particles[i], cx, cy, radius);
    }
}

void updateParticles(int cx, int cy, int radius) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x += particles[i].vx + WIND;
        particles[i].y += particles[i].vy + GRAVITY;
        particles[i].lifetime--;

        if (particles[i].lifetime <= 0 ||
            particles[i].x < 0 || particles[i].x > getmaxx() ||
            particles[i].y < 0 || particles[i].y > getmaxy()) {
            initParticle(&particles[i], cx, cy, radius);
        }

        particles[i].color = COLOR((particles[i].color >> 16) & 0xFF, (particles[i].color >> 8) & 0xFF, particles[i].color & 0xFF) - 1;
        if (particles[i].color < 0) particles[i].color = 0;
    }
}

void drawParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        putpixel((int)particles[i].x, (int)particles[i].y, particles[i].color);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    srand(time(NULL));

    int radius = 20;
    int x = getmaxx() / 2;
    int y = getmaxy() / 2;
    int dx = 15;
    int dy = 15;
    int squishTimer = 0;
    int trailLength = 3; 

    int trailX[trailLength], trailY[trailLength]; 
    for (int i = 0; i < trailLength; i++) {
        trailX[i] = x;
        trailY[i] = y;
    }

    int ballColor = getRandomColor(); 
    int oppositeColor = RGB(255 - GetRValue(ballColor), 255 - GetGValue(ballColor), 255 - GetBValue(ballColor)); 
    initParticles(x, y, radius);

    char text1[] = "Spandan Shrestha '81'";
    char text2[] = "Neeti Singh '49'";
    char text3[] = "Summit Sthapit '87'";
    char text4[] = "Shrijal Sthapit '76'";
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    while (1) {
        setbkcolor(oppositeColor);
        cleardevice();

        setcolor(ballColor);

        outtextxy(10, 10, text1);
        outtextxy(10, 30, text2);
        outtextxy(10, 50, text3);
        outtextxy(10, 70, text4);

        for (int i = trailLength - 1; i > 0; i--) {
            trailX[i] = trailX[i - 1];
            trailY[i] = trailY[i - 1];
        }
        trailX[0] = x;
        trailY[0] = y;

        setcolor(MAGENTA);
        for (int i = 1; i < trailLength; i++) {
            line(trailX[i-1], trailY[i-1], trailX[i], trailY[i]);
        }

        if (x - radius <= 0 || x + radius >= getmaxx()) {
            dx = -dx;
            squishTimer = 3; 
            ballColor = getRandomColor(); 
            oppositeColor = RGB(255 - GetRValue(ballColor), 255 - GetGValue(ballColor), 255 - GetBValue(ballColor)); 
            PlaySound(TEXT("sounds\\boing.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }

        if (y - radius <= 0 || y + radius >= getmaxy()) {
            dy = -dy;
            squishTimer = 3; 
            ballColor = getRandomColor(); 
            oppositeColor = RGB(255 - GetRValue(ballColor), 255 - GetGValue(ballColor), 255 - GetBValue(ballColor)); 
            PlaySound(TEXT("sounds\\boing.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }

        int squishX = radius;
        int squishY = radius;
        if (squishTimer > 0) {
            squishX += 10; 
            squishY -= 5; 
            squishTimer--; 
        }

        setcolor(ballColor);
        setfillstyle(SOLID_FILL, ballColor);
        fillellipse(x, y, squishX, squishY);

        updateParticles(x, y, radius);
        drawParticles();

        Sleep(35);

        x += dx;
        y += dy;
    }

    closegraph();
    return 0;
}
