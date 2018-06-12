#ifndef MAP_H_
#define MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "constants.h"


class Map {
    private:
        //Layer 0: Base layer
        //Layer 1: Cover
        //Layer 2: Items
        //Layer 3: People & Walls
        int readBuffer[4][size_x][size_y];
        int writeBuffer[4][size_x][size_y];

        void emptyRoom();
    public:
        Map();
        void drawToScreen();
        void writeTile(int x, int y, int tileVal);
        void emptyTile(int x, int y, int layer);
        int getTile(int x, int y);
        void equalize();

        int countR1(int x, int y, int tileType);
};


#endif
