#ifndef MAP_H_
#define MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "constants.h"


class Map {
    private:
        int readBuffer[size_x][size_y];
        int writeBuffer[size_x][size_y];

        void emptyRoom();
    public:
        Map();
        void drawToScreen();
        void writeTile(int x, int y, int tileVal);
        int getTile(int x, int y);
        void equalize();

        int countR1(int x, int y, int tileType);
};


#endif
