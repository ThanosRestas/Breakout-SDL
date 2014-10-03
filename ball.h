#ifndef BALL_H
#define BALL_H
#include "globals.h"

class Ball
{
    private:        

        CustomRect ball;

    public:
        Ball();
        int xVelocity,yVelocity;
        void move(CustomRect player, Uint32 deltaTicks);
        void show();
};

#endif // BALL_H
