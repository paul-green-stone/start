#include <stdio.h>

#include "../../include/Math/Vector2D.h"

/* ================================================================ */

int main(int argc, char** argv) {

    Vector2 c = {0, 0};

    Vector2 a = {10.9, -1.0};
    printf("a (plain) = {%.2f; %.2f}\n", a.x, a.y);

    Vector2* b = Vector2_create(99.6, 100.1);
    printf("b (dyn. plain) = {%.2f; %.2f}\n", b->x, b->y);
    Vector2_destroy(&b);

    Vector2_multiply(&a, &c, 10);
    printf("c (a * 10) = {%.2f; %.2f}\n", c.x, c.y);

    Vector2_divide(&c, NULL, 10);
    printf("c (c / 10) = {%.2f; %.2f}\n", c.x, c.y);

    Vector2_negate(&a);
    printf("a (negate) = {%.2f; %.2f}\n", a.x, a.y);

    Vector2 d = {3.0, 4.0};
    float length;
    Vector2_get_magnitude(&d, &length);
    printf("b's magnitute = %.2f\n", length);

    Vector2_normalize(&d);
    printf("d (normalized) = {%.2f; %.2f}\n", d.x, d.y);
}

/* ================================================================ */
