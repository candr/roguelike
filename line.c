#include "line.h"

//The values of the array are the y or x positions of the line, with 0 being the point closest to the origin

void bresenhamXindex(int x, int y, int x0, int y0, int* results){

    int Diff = 0;
    int dy = y - y0;
    int dx = x - x0;
    int yi = 1;
    if (dy == 0){
        for(int i = 0; i <= x - x0; i++){
            results[i] = y;
        }
        return;
    }
    if (dy < 0){
        yi = -1;
        dy = -dy;
    }
    Diff = 2 * dy - dx;
    int yp = y0;

    int index = 0;
    for( int xp = x0; xp <= x; xp++){
        results[index] = yp;
        index++;
        if(Diff > 0){
            yp = yp + yi;
            Diff -= 2*dx;
        }
        Diff += 2*dy;
    }
}

void bresenhamYindex(int x, int y, int x0, int y0, int* results){

    int Diff = 0;
    int dy = y - y0;
    int dx = x - x0;
    int xi = 1;

    if (dx < 0){
        xi = -1;
        dx = -dx;
    } else if (dx == 0){
        for(int i = 0; i <= y - y0; i++){
            results[i] = x;
        }
        return;
    } 
    Diff = 2 * dx - dy;
    int xp = x0;

    int index = 0;
    for( int yp = y0; yp <= y; yp++){
        results[index] = xp;
        index++;
        if(Diff >= 0){
            xp = xp + xi;
            Diff -= 2*dy;
        }
        Diff += 2*dx;
    }
}


//Makes a straight line between (x0,y0) and (x,y)
//line between (x0,y0) and (x, y)
//This version is for lines where dx < dy
//index 0 always corresponds to y0
//return val:
//0: x0,y0 is above x,y (y > y0)
//1: x0,y0 is below x,y (y < y0)
//-1 - error
char makeLineSteep(int x, int y, int x0, int y0, int* results){
    int retVal = -1;
    if(y > y0){
        bresenhamYindex(x, y, x0, y0, results);
        retVal = 0;
    } else {
        bresenhamYindex(x0, y0, x, y, results);
        for(int i = 0; i < (y0-y+1)/2; i++){
            int shuff = results[i];
            results[i] = results[(y0-y)  - i];
            results[(y0-y) - i] = shuff;
        }
        retVal = 1;
    }
    return retVal;
}

//Makes a straight line between (x0,y0) and (x,y)
//line between (x0,y0) and (x, y)
//This version is for lines where dx > dy
//index 0 always corresponds to x0
//return val:
//0: x0,y0 is to the left of x,y (x > x0)
//1: x0,y0 is to the right of x,y (x < x0)
//-1 - error
char makeLineShallow(int x, int y, int x0, int y0, int* results){
    int retVal = -1;
    if(x > x0){
        bresenhamXindex(x, y, x0, y0, results);
        retVal = 0;
    } else {
        bresenhamXindex(x0, y0, x, y, results);
        for(int i = 0; i < (x0-x+1)/2; i++){
            int shuff = results[i];
            results[i] = results[(x0-x)  - i];
            results[(x0-x)  - i] = shuff;
        }
        retVal = 1;
    }
    return retVal;
}


