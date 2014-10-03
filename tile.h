#ifndef TILE_H
#define TILE_H
#include "globals.h"

class Tile
{
    private:
        SDL_Rect box;
        int type;

    public:
        Tile( int x, int y, int tileType );

        void show();

        int get_type();

        SDL_Rect get_box();
};

#endif // TILE_H
