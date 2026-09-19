#include <stdbool.h>

bool checkOverlap(int radius, int xCenter, int yCenter,
                  int x1, int y1, int x2, int y2) {

    int closestX = xCenter;
    int closestY = yCenter;

    // Find the closest X coordinate on the rectangle
    if (xCenter < x1)
        closestX = x1;
    else if (xCenter > x2)
        closestX = x2;

    // Find the closest Y coordinate on the rectangle
    if (yCenter < y1)
        closestY = y1;
    else if (yCenter > y2)
        closestY = y2;

    // Calculate squared distance
    int dx = xCenter - closestX;
    int dy = yCenter - closestY;

    return (dx * dx + dy * dy) <= (radius * radius);
}