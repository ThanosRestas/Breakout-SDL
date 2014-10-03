#ifndef PLAYER_H
#define PLAYER_H
#include "globals.h"

class Player
{
    private:
        int xVelocity;
    public:
        CustomRect player;
        Player(int xUser,int yUser);
        void handle_input();
        void move(Uint32 deltaTicks);
        void show();
};

#endif // PLAYER_H
