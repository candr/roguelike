#include "caves.h"

//A function to initialize two maps for the cave generation cellular automata
//Input: Two pointers to 2D arrays. There should be no memory associated with these yet
//Output: None
//Effect: Both pointers willbe allocated size_x * size_y memory
//Searchmap will be randomly filled with walls and spaces, based on FILLP
//Also, searchMap will have a boundary of walls
//fillMap will be filled with walls
void initMap(int ***searchMap, int ***fillMap){
    

    *searchMap = (int**)malloc(sizeof(int*) * size_x);
    *fillMap = (int**)malloc(sizeof(int*) * size_x);

    for(int i = 0; i < size_x; i++){
        (*searchMap)[i] = (int*)malloc(sizeof(int) * size_y);
        (*fillMap)[i] = (int*)malloc(sizeof(int) * size_y);
    }

    for(int i = 1; i < size_x-1; i++){
        for(int j = 1; j < size_y-1; j++){
            (*fillMap)[i][j] = TILE_FLOOR;
            (*searchMap)[i][j] = ((rand()%100 < FILLP) ? TILE_WALL : TILE_FLOOR);
        }
    }


    for(int i = 0; i < size_y; i++){
        (*fillMap)[0][i] = TILE_WALL;
        (*fillMap)[size_x-1][i] = TILE_WALL;
        (*searchMap)[0][i] = TILE_WALL;
        (*searchMap)[size_x-1][i] = TILE_WALL;
    }

    for(int i = 1; i < size_x-1; i++){
        (*fillMap)[i][0] = TILE_WALL;
        (*fillMap)[i][size_y-1] = TILE_WALL;
        (*searchMap)[i][0] = TILE_WALL;
        (*searchMap)[i][size_y-1] = TILE_WALL;
    }
   

}



//Counts all the walls within 1 space of x,y
//Input: The map we are using, and a position on the map
//Output: The number of walls
//Effects: None
int countWallsR1(int** map, int x, int y){

    int counter = 0;

    for(int i = x - 1; i <= x + 1; i++){
        for(int j = y - 1; j <= y + 1; j++){
            if(i <= 0 || i >= size_x || j <= 0 || j >= size_y){
                continue;
            }else if (i == x && j == y){
                continue;
            }else if(map[i][j] == TILE_WALL){
                counter++;
            }
        }
    }
    return counter;
}


//Counts all the walls within 2 spaces of x,y
//Input: The map we are using, and a position on the map
//Output: The number of walls
//Effects: None
int countWallsR2(int** map, int x, int y){
    int counter = 0;

    for(int i = x - 2; i <= x + 2; i++){
        for(int j = y - 2; j <= y + 2; j++){
            if(i <= 0 || i >= size_x || j <= 0 || j >= size_y){
                continue;
            }else if (i == x && j == y){
                continue;
            }else if (abs(i-x) == 2 && abs(j-y) == 2){
                continue;
            }else if(map[i][j] == TILE_WALL){
                counter++;
            } 
        }
    }
    return counter;
}


//A generation function for CA cave making
//This one places walls based on the function
//W(x,y) -> R1(x,y) >= 5 || R2(x,y) <= 2
//where R1 is the number of walls within 1 space
//and R2 is the number of walls withing 2 spaces
//Input: 2 maps. searchMap is the map we check, then place the walls in fillMap
//Output: None
//Effect: fillMap is the sucessor to searchMap
void generation1(int** searchMap, int** fillMap){
    for(int i = 1; i < size_x-1; i++){
        for(int j = 1; j < size_y-1; j++){
            int count = countWallsR1(searchMap, i, j);
            int count2 = countWallsR2(searchMap, i, j);
            if (count >= 5 || count2 <= 2){
                fillMap[i][j] = TILE_WALL;
            } else {
                fillMap[i][j] = TILE_FLOOR;
            }
        }
    }
}


//A generation function for CA cave making
//This one places walls based on the function
//W(x,y) -> R1(x,y) >= 5 
//where R1 is the number of walls within 1 space
//Input: 2 maps. searchMap is the map we check, then place the walls in fillMap
//Output: None
//Effect: fillMap is the sucessor to searchMap
void generation2(int** searchMap, int** fillMap){
    for(int i = 1; i < size_x-1; i++){
        for(int j = 1; j < size_y-1; j++){
            int count = countWallsR1(searchMap, i, j);
            if (count >= 5) {
                fillMap[i][j] = TILE_WALL;
            } else {
                fillMap[i][j] = TILE_FLOOR;
            }
        }
    }
}

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
void makeCaves(Map* map){

    int** grid;
    int** grid2;


    initMap(&grid,&grid2);


    //4 generations checking for close caves and big empty spots
    generation1(grid, grid2);
    generation1(grid2, grid);
    generation1(grid, grid2);
    generation1(grid2, grid);

    //3 generations checking only for close walls
    generation2(grid, grid2);
    generation2(grid2, grid);
    generation2(grid, grid2);

    for(int i = 0; i < size_x; i++){
        for(int j = 0; j < size_y; j++){
            map->writeTile(i, j, grid2[i][j]);
        }
    }

    free(grid);
    free(grid2);
}

