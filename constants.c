#include "constants.h"

Shape& Shape::instance(){
    static Shape theInstance;
    return theInstance;
}

Shape::Shape(){
    cross = (int**)malloc(5 * sizeof(int*));
    criss = (int**)malloc(5 * sizeof(int*));
    for(int i = 0; i < 5; i++){
        cross[i] = (int*)malloc(2 * sizeof(int));
        criss[i] = (int*)malloc(2 * sizeof(int));
    }

    cross[0][0] = 0;
    cross[0][1] = 0;
    cross[1][0] = 1;
    cross[1][1] = 0;
    cross[2][0] = -1;
    cross[2][1] = 0;
    cross[3][0] = 0;
    cross[3][1] = -1;
    cross[4][0] = 0;
    cross[4][1] = 1;

    criss[0][0] = 0;
    criss[0][1] = 0;
    criss[1][0] = -1;
    criss[1][1] = 1; 
    criss[2][0] = 1;
    criss[2][1] = 1;
    criss[3][0] = 1;
    criss[3][1] = -1;
    criss[4][0] = -1;
    criss[4][1] = -1;
}

int** Shape::getCross(){
    return cross;
}

int** Shape::getCriss(){
    return criss;
}

Shape::~Shape(){}


