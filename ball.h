#ifndef BALL_H
#define BALL_H
#include "globals.h"
#include "tile.h"

class Ball
{
    private:        

        CustomRect ball;

    public:
        Ball(float x , float y);
        int xVelocity,yVelocity;
        int life;

        void move(CustomRect player,Tile *tiles[] , float deltaTicks,int destroyedTile[]);
        bool check_collision(CustomRect A, CustomRect B,int &side);
        int check_brick_collision(CustomRect A, Tile *tiles[], int &side, int destroyedTile[]);
        void show();
};

#endif // BALL_H
