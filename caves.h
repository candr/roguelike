#ifndef CAVES_H_
#define CAVES_H_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "constants.h"
#include "map.h"

//A function to initialize two maps for the cave generation cellular automata
//Input: Two pointers to 2D arrays. There should be no memory associated with these yet
//Output: None
//Effect: Both pointers willbe allocated size_x * size_y memory
//Searchmap will be randomly filled with walls and spaces, based on FILLP
//Also, searchMap will have a boundary of walls
//fillMap will be filled with walls
void initMap(int ***searchMap, int ***fillMap);

//Counts all the walls within 1 space of x,y
//Input: The map we are using, and a position on the map
//Output: The number of walls
//Effects: None
int countWallsR1(int** map, int x, int y);

//Counts all the walls within 2 spaces of x,y
//Input: The map we are using, and a position on the map
//Output: The number of walls
//Effects: None
int countWallsR2(int** map, int x, int y);

//A generation function for CA cave making
//This one places walls based on the function
//W(x,y) -> R1(x,y) >= 5 || R2(x,y) <= 2
//where R1 is the number of walls within 1 space
//and R2 is the number of walls withing 2 spaces
//Input: 2 maps. searchMap is the map we check, then place the walls in fillMap
//Output: None
//Effect: fillMap is the sucessor to searchMap
void generation1(int** searchMap, int** fillMap);

//A generation function for CA cave making
//This one places walls based on the function
//W(x,y) -> R1(x,y) >= 5 
//where R1 is the number of walls within 1 space
//Input: 2 maps. searchMap is the map we check, then place the walls in fillMap
//Output: None
//Effect: fillMap is the sucessor to searchMap
void generation2(int** searchMap, int** fillMap);

//A function that creates a believably organic cave map by using
//cellular automata
//It runs through 4 generations of a function
//W(x,y) -> R1(x,y) >= 5 || R2(x,y) <= 2
//and then 3 generations of a function
//W(x,y) -> R1(x,y) >= 5 
//where R1 is the number of walls within 1 space
//and R2 is the number of walls withing 2 spaces
//
//Input: One map, to print the end result of the CA onto
//Output: None
//Effect: The map has been drawn with the result of the cave system
void makeCaves(Map* map);

#endif

