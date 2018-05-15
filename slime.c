#include "slime.h"

    


Flood::Flood(int x,int y, Map* glbMap){

    std::vector<int> newCoord(2, 0);
    newCoord[0] = x;
    newCoord[1] = y;
    frontier.push_front(newCoord);
    map = glbMap;
    age = 0;
    debug = fopen("floodDebug.txt", "a");

    for(int i = 0; i < size_x; i++){
        for(int j = 0; j < size_y; j++){
            checkedTiles[i][j] = 0;
        }
    }

    checkedTiles[x][y] = 1;
}


void Flood::surge(){
    std::list< std::vector<int> >::iterator it = frontier.begin(); 
    fprintf(debug, "Size of frontier at turn %i is %i\n", age, (int)frontier.size());
    while(it != frontier.end()){
        int x = (*it)[0];
        int y = (*it)[1];
        int wallCount = map->countR1(x, y, TILE_WALL);
        int waterCount = map->countR1(x, y, TILE_WATER);
        if(map->getTile(x, y) == TILE_WATER || map->getTile(x, y) == TILE_WALL){
            it = frontier.erase(it);
        } else if(map->getTile(x, y) == TILE_FLOOR && ((wallCount+waterCount >= 3) || (age < 2))){
            map->writeTile(x, y, TILE_WATER);

            for(int i = -1; i <= 1; i++){
                for(int j = -1; j<= 1; j++){
                    int checkX = x + i;
                    int checkY = y + j;
                    //fprintf(errfile, "%i %i\n", checkX, checkY);
                    if( checkX > 0 && checkY > 0 && checkX < size_x && checkY < size_y){
                        if(checkedTiles[checkX][checkY] == 0 && map->getTile(checkX, checkY) == TILE_FLOOR){
                            //fprintf(debug, "Adding %i, %i to frontier\n", checkX, checkY);
                            std::vector<int> newCoord(2, 0);
                            newCoord[0] = checkX;
                            newCoord[1] = checkY;
                            frontierBuffer.push_front(newCoord);
                        }
                        checkedTiles[checkX][checkY] = 1;
                    }
                }
            }
            it = frontier.erase(it);
        } else {
            ++it;
        }
    }

    while(!frontierBuffer.empty()){
        frontier.push_front(frontierBuffer.front());
        frontierBuffer.pop_front();
    }
    age++;

}

Flood::~Flood(){
    fclose(debug);
}

