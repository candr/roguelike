#ifndef SLIME_H_
#define SLIME_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>

#include "constants.h"
#include "map.h"

class Flood {
    private:
        std::list< std::vector<int> > frontier;
        FILE *debug;
        int checkedTiles[size_x][size_y];
        
        int age;
        Map* map;

        bool placeTile(std::vector<int>);
        std::list< std::vector<int> > frontierBuffer;

    public:
        Flood(int,int,Map*);
        void surge();
        ~Flood();
};


#endif
