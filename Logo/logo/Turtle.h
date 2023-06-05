#ifndef TURTLE_H
#define TURTLE_H

#include <cmath>

namespace turtle {

double const PI = std::acos(-1);
double const DEGREE_TO_RADIAN = PI/180;

extern double turtleX;
extern double turtleY;
extern double turtleDir;
extern bool turtlePenDown;
extern unsigned char const * turtleColor;

const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 },
	white[] = {255, 255, 255}, black[] = {0, 0, 0};

void initTurtle();
void uninitTurtle();
void redraw();
void rest(float s);
bool interrupt();
void waitEnd();

// Change from mouse coordinates to bitmap coordinates
void drawLine(double x1, double x2, double y1, double y2, unsigned char const * color);

} // namespace turtle


#endif // TURTLE_H
