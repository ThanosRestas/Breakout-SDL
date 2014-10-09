#ifndef BALL_H
#define BALL_H
#include "globals.h"
#include "tile.h"

class Ball
{
    private:        

        CustomRect ball;

    public:
        Ball();
        int xVelocity,yVelocity;

        void move(CustomRect player,Tile *tiles[] , float deltaTicks);
        bool check_collision(CustomRect A, CustomRect B );
        bool check_brick_collision(CustomRect A,Tile *tiles[] );
        void show();
};

#endif // BALL_H
