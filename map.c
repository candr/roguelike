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

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < size_x; j++){
            for(int k = 0; k < size_y; k++){
                readBuffer[i][j][k] = TILE_EMPTY;
                writeBuffer[i][j][k] = TILE_EMPTY;
            }
        }
    }

    for(int i = 0; i < size_y; i++){
        readBuffer[3][0][i] = TILE_WALL;
        readBuffer[3][size_x-1][i] = TILE_WALL;
        writeBuffer[3][0][i] = TILE_WALL;
        writeBuffer[3][size_x-1][i] = TILE_WALL;
    }

    for(int i = 1; i < size_x-1; i++){
        readBuffer[3][i][0] = TILE_WALL;
        readBuffer[3][i][size_y-1] = TILE_WALL;
        writeBuffer[3][i][0] = TILE_WALL;
        writeBuffer[3][i][size_y-1] = TILE_WALL;
    }

    for(int i = 0; i < size_x; i++){
        for(int j = 0; j < size_y; j++){
            readBuffer[0][i][j] = TILE_FLOOR;
            writeBuffer[0][i][j] = TILE_FLOOR;
        }
    }
}

void Map::drawToScreen(){

        //Print the map
        for(int i = 0; i < size_x; i++){
            for(int j = 0; j < size_y; j++){
                int k = 3;
                int tile = writeBuffer[k][i][j];
                while(tile == TILE_EMPTY){
                    k--;
                    tile = writeBuffer[k][i][j];
                }

                switch(tile){
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
                    case TILE_AVATAR:
                        attron(COLOR_PAIR(2));
                        mvaddch(j,i,'@');
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
    switch(tileVal){
        case TILE_FLOOR:
            writeBuffer[0][x][y] = TILE_FLOOR;
            break;
        case TILE_WALL:
            writeBuffer[3][x][y] = TILE_WALL;
            break;
        case TILE_WATER:
            writeBuffer[1][x][y] = TILE_WATER;
            break;
        case TILE_FOOD:
            writeBuffer[2][x][y] = TILE_FOOD;
            break;
        case TILE_AVATAR:
            writeBuffer[3][x][y] = TILE_AVATAR;
            break;
        default:
            break;
    }
}

int Map::getTile(int x, int y){
    int k = 3;
    int tile = readBuffer[k][x][y];
    while(tile == TILE_EMPTY){
        k--;
        tile = readBuffer[k][x][y];
    }
    return tile;
}

void Map::equalize(){
    for(int k = 0; k < 4; k++){
        for(int i = 0; i < size_x; i++){
            for(int j = 0; j < size_y; j++){
                readBuffer[k][i][j] = writeBuffer[k][i][j];
            }
        }
    }
}


//Counts all the walls within 1 space of x,y
//Input: The map we are using, and a position on the map
//Output: The number of walls
//Effects: None
int Map::countR1(int x, int y, int tileType){

    int counter = 0;
    int layer = -1;
    switch(tileType){
        case TILE_FLOOR:
            layer = 0;
            break;
        case TILE_WALL:
        case TILE_AVATAR:
            layer = 3;
            break;
        case TILE_WATER:
            layer = 1;
            break;
        case TILE_FOOD:
            layer = 2;
            break;
        default:
            break;
    }

    for(int i = x - 1; i <= x + 1; i++){
        for(int j = y - 1; j <= y + 1; j++){
            if(i <= 0 || i >= size_x || j <= 0 || j >= size_y){
                continue;
            }else if (i == x && j == y){
                continue;
            }else if(readBuffer[layer][i][j] == tileType){
                counter++;
            }
        }
    }
    return counter;
}

    

void Map::emptyTile(int x, int y, int layer){
    writeBuffer[layer][x][y] = TILE_EMPTY;
}

