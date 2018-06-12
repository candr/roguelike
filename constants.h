#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <stdlib.h>

#define TILE_EMPTY -1
#define TILE_FLOOR 0
#define TILE_WALL 1
#define TILE_WATER 2
#define TILE_FOOD 3
#define TILE_SLIME_HEAD 4
#define TILE_SLIME_NODE 5
#define TILE_AVATAR 6

#define FILLP 40

#define size_x 50
#define size_y 20

class Shape{
    public:
        static Shape& instance();

        int** getCriss();
        int** getCross();

    private:
        int **cross;
        int **criss;
        Shape();
        ~Shape();
};


#endif
