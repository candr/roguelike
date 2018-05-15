#include "map.h"


Map::Map(){
    //Init ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    if(has_colors() == FALSE){
        endwin();
        printf("terminal has no colour\n");
    }

    //Init the colour pairs
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    this->emptyRoom();

   
}

void Map::emptyRoom(){
    for(int i = 0; i < size_y; i++){
        readBuffer[0][i] = TILE_WALL;
        readBuffer[size_x-1][i] = TILE_WALL;
        writeBuffer[0][i] = TILE_WALL;
        writeBuffer[size_x-1][i] = TILE_WALL;
    }

    for(int i = 1; i < size_x-1; i++){
        readBuffer[i][0] = TILE_WALL;
        readBuffer[i][size_y-1] = TILE_WALL;
        writeBuffer[i][0] = TILE_WALL;
        writeBuffer[i][size_y-1] = TILE_WALL;
    }

    for(int i = 1; i <= size_x-2; i++){
        for(int j = 1; j <= size_y-2; j++){
            readBuffer[i][j] = TILE_FLOOR;
            writeBuffer[i][j] = TILE_FLOOR;
        }
    }
}

void Map::drawToScreen(){

        //Print the map
        for(int i = 0; i < size_x; i++){
            for(int j = 0; j < size_y; j++){
                switch(writeBuffer[i][j]){
                    case TILE_FLOOR:
                        mvaddch(j,i,'.');
                        break;
                    case TILE_WALL:
                        mvaddch(j,i,'#');
                        break;
                    case TILE_WATER:
                        attron(COLOR_PAIR(1));
                        mvaddch(j,i,'~');
                        attroff(COLOR_PAIR(1));
                        break;
                    case TILE_FOOD:
                        attron(COLOR_PAIR(2));
                        mvaddch(j,i,'^');
                        attroff(COLOR_PAIR(2));
                        break;
                    default:
                        break;
                }
            }
        }

        refresh();

        this->equalize();


}


void Map::writeTile(int x, int y, int tileVal){
    writeBuffer[x][y] = tileVal;
}

int Map::getTile(int x, int y){
    return readBuffer[x][y];
}

void Map::equalize(){
    for(int i = 0; i < size_x; i++){
        for(int j = 0; j < size_y; j++){
            readBuffer[i][j] = writeBuffer[i][j];
        }
    }
}


//Counts all the walls within 1 space of x,y
//Input: The map we are using, and a position on the map
//Output: The number of walls
//Effects: None
int Map::countR1(int x, int y, int tileType){

    int counter = 0;

    for(int i = x - 1; i <= x + 1; i++){
        for(int j = y - 1; j <= y + 1; j++){
            if(i <= 0 || i >= size_x || j <= 0 || j >= size_y){
                continue;
            }else if (i == x && j == y){
                continue;
            }else if(readBuffer[i][j] == tileType){
                counter++;
            }
        }
    }
    return counter;
}
