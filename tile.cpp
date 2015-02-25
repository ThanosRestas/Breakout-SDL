#include "tile.h"

Tile::Tile( int x, int y, int tileType )
{
    box.x = x;
    box.y = y;

    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    centerX = (box.w + box.x) /2;
    centerY = (box.h + box.y) /2;

    type = tileType;
}

void Tile::show()
{
    apply_surface( box.x , box.y , tileSheet, screen, &clips[ type ] );
}

int Tile::get_type()//Get the color of the tile
{
    return type;
}

CustomRect Tile::get_box()
{
    return box;
}





































