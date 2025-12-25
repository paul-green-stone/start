#ifdef _MSC_VER
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

#include "../include/Shapes/Shapes.h"
#include "../include/Application.h"

/* ================================================================ */
/* ============================= LINE ============================= */
/* ================================================================ */

void Line_draw(const Line* line) {

    int x1, y1, x2, y2;
    int dx, dy;
    int x, y;       /* Current pixel to plot */
    int p;          /* Decision parameter */
    int sign_x = 0, sign_y = 0;

    SDL_Renderer* ctx = get_context();
    /* ======== */

    x1 = line->base.x;
    y1 = line->base.y;
    x2 = line->direction.x;
    y2 = line->direction.y;

    dx = x2 - x1;
    dy = y2 - y1;

    x = x1;
    y = y1;

    if (dx >= 0) { sign_x++; }
    else { sign_x--; }

    if (dy >= 0) { sign_y++; }
    else { sign_y--; }

    if (fabs((float) dy) < fabs((float) dx)) {

        p = (2 * dy * sign_y) - (dx * sign_x);
        for (int i = 0; i <= dx * sign_x; i++) {

            SDL_RenderDrawPoint(ctx, x, y);

            if (p < 0) {
                p += (2 * dy * sign_y);
            }
            else {
                y += sign_y;
                p += (2 * dy * sign_y) - (2 * dx * sign_x);
            }

            x += sign_x;
        }
    }
    else {

        p = (2 * dx * sign_x - dy * sign_y);
        for (int i = 0; i < dy * sign_y; i++) {

            SDL_RenderDrawPoint(ctx, x, y);

            if (p < 0) {
                p += 2 * dx * sign_x;
            }
            else {
                x += sign_x;
                p += (2 * dx * sign_x) - (2 * dy * sign_y);
            }

            y += sign_y;
        }
    }
}

/* ================================================================ */
/* ============================ CIRCLE ============================ */
/* ================================================================ */

void Cirlce_draw(const Circle* circle) {

    int x, y;       /* Current pixel to plot */
    int p;

    SDL_Renderer* ctx = get_context();
    /* ======== */

    x = 0;
    y = circle->radius;

    p = 1 - circle->radius;

    /* ======== */

    for (; x <= y; ) {

        SDL_RenderDrawPoint(ctx, x + circle->center.x, y + circle->center.y);
        SDL_RenderDrawPoint(ctx, x + circle->center.x, -y + circle->center.y);
        SDL_RenderDrawPoint(ctx, -x + circle->center.x, y + circle->center.y);
        SDL_RenderDrawPoint(ctx, -x + circle->center.x, -y + circle->center.y);
        SDL_RenderDrawPoint(ctx, y + circle->center.x, x + circle->center.y);
        SDL_RenderDrawPoint(ctx, y + circle->center.x, -x + circle->center.y);
        SDL_RenderDrawPoint(ctx, -y + circle->center.x, x + circle->center.y);
        SDL_RenderDrawPoint(ctx, -y + circle->center.x, -x + circle->center.y);

        x++;

        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

/* ================================================================ */
