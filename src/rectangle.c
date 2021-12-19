#include "speed.h"

/*
 * h is mapped to x
 * w is mapped to y
 */
Point get_hw_from_rectangle(Rectangle *rectangle) {
    Point point;

    point.x = rectangle->bottom_right.y - rectangle->top_left.y;
    point.y = rectangle->bottom_right.x - rectangle->top_left.x;
    return point;
}