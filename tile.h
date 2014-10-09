#ifndef TILE_H
#define TILE_H
#include "globals.h"

class Tile
{
    private:

        int type;

    public:
        CustomRect box;
        Tile( int x, int y, int tileType );

        void show();

        int get_type();

        CustomRect get_box();
};

#endif // TILE_H
