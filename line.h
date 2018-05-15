#ifndef LINE_H_
#define LINE_H_

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

//An implementation of bresenham's algorithm. Approximates a straight
//line between (x0,y0) and (x, y)
//This version is for lines where dx > dy
//x0 must be to the left of x (x0 < x)
//results is the y values of the line, indexed as 0 = x0
void bresenhamXindex(int x, int y, int x0, int y0, int* results);

//An implementation of bresenham's algorithm. Approximates a straight
//line between (x0,y0) and (x, y)
//This version is for lines where dx < dy
//y0 must be above y (y0 < y)
//results is the x values of the line, indexed as 0 = y0
void bresenhamYindex(int x, int y, int x0, int y0, int* results);

//Makes a straight line between (x0,y0) and (x,y)
//line between (x0,y0) and (x, y)
//This version is for lines where dx < dy
//index 0 always corresponds to y0
//return val:
//0: x0,y0 is above x,y (y > y0)
//1: x0,y0 is below x,y (y < y0)
//-1 - error
char makeLineSteep(int x, int y, int x0, int y0, int* results);

//Makes a straight line between (x0,y0) and (x,y)
//line between (x0,y0) and (x, y)
//This version is for lines where dx > dy
//index 0 always corresponds to x0
//return val:
//0: x0,y0 is to the left of x,y (x > x0)
//1: x0,y0 is to the right of x,y (x < x0)
//-1 - error
char makeLineShallow(int x, int y, int x0, int y0, int* results);

#endif
