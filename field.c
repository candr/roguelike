#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <queue>
#include <vector>

#include "line.h"
#include "caves.h"
#include "constants.h"
#include "slime.h"

void emptyRoom(int** map){
    for(int i = 0; i < size_y; i++){
        map[0][i] = TILE_WALL;
        map[size_x-1][i] = TILE_WALL;
    }

    for(int i = 1; i < size_x-1; i++){
        map[i][0] = TILE_WALL;
        map[i][size_y-1] = TILE_WALL;
    }

    for(int i = 1; i < size_x-2; i++){
        for(int j = 1; j < size_y-2; j++){
            map[i][j] = TILE_FLOOR;
        }
    }
}

void flood(int x, int y, int** map){
    
   
    std::queue< std::vector<int> > frontier;
    char checkedTiles[size_x][size_y]; 

    for(int i = 0; i < size_x; i++){
        for(int j = 0; j < size_y; j++){
            checkedTiles[i][j] = 0;
        }
    }
    checkedTiles[x][y] = 1;

    std::vector<int> newCoord(2, 0);
    newCoord[0] = x;
    newCoord[1] = y;
    frontier.push(newCoord);



    while(!frontier.empty()){
        std::vector<int> nextTile = frontier.front();

        if(map[nextTile[0]][nextTile[1]] == TILE_FLOOR){
            map[nextTile[0]][nextTile[1]] = TILE_WATER;
            for(int i = -1; i <= 1; i++){
                for(int j = -1; j<= 1; j++){
                    int checkX = nextTile[0] + i;
                    int checkY= nextTile[1] + j;
                    //fprintf(errfile, "%i %i\n", checkX, checkY);
                    if( checkX > 0 && checkY > 0 && checkX < size_x && checkY < size_y && checkedTiles[checkX][checkY] == 0){
                        std::vector<int> newCoord(2, 0);
                        newCoord[0] = checkX;
                        newCoord[1] = checkY;
                        frontier.push(newCoord);
                        checkedTiles[nextTile[0]][nextTile[1]] = 1;
                    }
                }
            }
        }
        frontier.pop();
    }

}


void lineOfSight(int avat_x, int avat_y, int** map, char** mapMask){
    int* lineVals = (int*)malloc(sizeof(int) * (size_x > size_y ? size_x : size_y));
    /*
    FILE* errfile;
    errfile = fopen("errfile.txt", "a");
    */
    //reset the mask
    for(int i = 0; i < size_x; i++){
        for(int j = 0; j < size_y; j++){
            mapMask[i][j] = 0;
        }
    }
    for(int i = 0; i < size_y; i++){
        mapMask[0][i] = 1;
        mapMask[size_x-1][i] = 1;
    }

    for(int i = 1; i < size_x-1; i++){
        mapMask[i][0] = 1;
        mapMask[i][size_y-1] = 1;
    }

    mapMask[avat_x][avat_y] = 1;
    for(int i = 0; i < size_x; i++){
        for(int j = 0; j < size_y; j++){
            if(abs(avat_x - i) > abs(avat_y - j)){
                char dir = makeLineShallow(i, j, avat_x, avat_y, lineVals);
                if(dir == 0){ // avatar to the left of (i,j)
                    int xInd = avat_x;
                    do{
                        xInd++;
                        mapMask[xInd][lineVals[xInd - avat_x]] = 1;
                    }while(xInd < i && map[xInd][lineVals[xInd - avat_x]] != TILE_WALL);

                }
                if(dir == 1){ // avatar to the right of (i,j)
                    int xInd = avat_x;
                    int ctr = 1;
                    do{
                        xInd--;
                        mapMask[xInd][lineVals[ctr++]] = 1;
                    }while(xInd > i && map[xInd][lineVals[ctr]] != TILE_WALL);
                }
            } else {
                char dir = makeLineSteep(i, j, avat_x, avat_y, lineVals);
                if(dir == 0){ //avatar is above (i,j)
                    int yInd = avat_y;
                    do{
                        yInd++;
                        mapMask[lineVals[yInd-avat_y]][yInd] = 1;
                    }while(yInd < j && map[lineVals[yInd-avat_y]][yInd] != TILE_WALL);

                } else if(dir == 1){
                    int yInd = avat_y;
                    int ctr = 1;
                    do{
                        yInd--;
                        mapMask[lineVals[ctr++]][yInd] = 1;
                    }while(yInd > j && map[lineVals[ctr]][yInd] != TILE_WALL);
                }

            }
        }
    }
    //fclose(errfile);
    free(lineVals);
}

int main(){

    //FILE* errfile;
    //errfile = fopen("errfile.txt", "a");

    srand(time(NULL));

    Map map;


    //with caves
    makeCaves(&map);

    //Add food
    /*
    int foodCount = 5;
    do{
        int newFoodX = rand()%size_x;
        int newFoodY = rand()%size_y;
        if(map.getTile(newFoodX, newFoodY) == TILE_FLOOR){
            map.writeTile(newFoodX, newFoodY, TILE_FOOD);
            foodCount--;
        }
    }while(foodCount > 0);
    */

    map.equalize();

    Flood flood(10, 10, &map);

    int ch = 0;
    //fprintf(errfile, "Right before the do\n");

    do{
        flood.surge();

        map.drawToScreen();

        ch = getch();
    }while(ch != 'q');

    //cleanup
    endwin();

    /*

    for(int i = 0; i < size_x; i++){
        free(map[i]);
        free(mapMask[i]);
    }

    free(map);
    free(mapMask);
    */
   // fclose(errfile);
}
