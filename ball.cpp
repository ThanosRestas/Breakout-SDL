#include "ball.h"

SDL_Surface *screen = NULL;
SDL_Surface *paddleSprite = NULL;
SDL_Surface *ballSprite = NULL;

Ball::Ball(float x, float y)
{
    ball.x = x;
    ball.y = y;

    ball.h = BALL_HEIGHT;
    ball.w = BALL_WIDTH;

    xVelocity = 400;
    yVelocity = -400;

    life = 3;
}

int Ball::check_brick_collision(CustomRect A, Tile *tiles[], int &side,int destroyedTile[])
{

    float BcenterY = 0;
    float AcenterY = 0;
    int done = 2;

    for(int t = 0; t < TOTAL_TILES; t++)
    {
        CustomRect B = tiles[t] -> get_box();
        BcenterY = B.y + B.h/2;
        AcenterY = A.y + A.h/2;
        if(destroyedTile[t] == 0  && check_collision(A,B,side) == true)
        {
            //If the ball is above or below a tile and a collision has happened reverse yVelocity
            if(AcenterY >= BcenterY + A.w / 2 + 5 || AcenterY < BcenterY - A.w / 2 -5  )// +/- 5 pixels adjustment in the calculation is for error correction
            {
                yVelocity = -yVelocity;
                done = 1;//Top or bottom collision
            }
            else//If the ball isn't above/below a tile and a collision happened then the ball must be next to the side so reverse its xVelocity
            {
                xVelocity = -xVelocity;
                done = 0;//Left or right collision
            }

            destroyedTile[t] = 1;
            break;
        }
    }

    if(done != 2)
    {
        printf("Done is : %d \n", done);
    }


    return done;
}

bool Ball::check_collision(CustomRect A, CustomRect B,int &side)//Collision detection via the bounding box method
{
    //The sides of the rectangles
    float leftA,leftB;
    float rightA,rightB;
    float topA,topB;
    float bottomA,bottomB;

    bool isCollided = false;

    //Calculate the sides of the rectangle A
    leftA = A.x;
    rightA= A.x + A.w;
    topA = A.y ;
    bottomA = A.y + A.h;

    //Calculate the sides of the rectangle B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( rightA <= leftB )//Bottom collision
    {
        return false;
    }

    if( leftA >= rightB )//Top collision
    {
       return false;
    }

    if( bottomA <= topB )//Left collision
    {
        return false;
    }

    if( topA >= bottomB )//Right Collision
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void Ball::move(CustomRect player, Tile *tiles[], float deltaTicks,int destroyedTile[])
{
    int side = -1;
    ball.x += xVelocity *(deltaTicks/1000.f);
    ball.y += yVelocity *(deltaTicks/1000.f);

    if( ball.y < 0 )//Top wall
    {
        ball.y = 0;
        yVelocity = -yVelocity;
    }
    else if( ball.y + BALL_HEIGHT > SCREEN_HEIGHT )//When ball touches the floor : reset it's y position,substact from the life of the player 1 point and reverse it's yVelocity(so it goes up)
    {
        ball.y = 500;
        life = life - 1;
        yVelocity = -yVelocity;
    }
    else if(ball.x +BALL_HEIGHT > SCREEN_WIDTH)//Right wall bouncing
    {
        ball.x = SCREEN_WIDTH - BALL_WIDTH;
        xVelocity = -xVelocity;
    }
    else if(ball.x < 0 )//Left wall
    {
        ball.x = 0;
        xVelocity = -xVelocity;
    }

    if(check_collision(player,ball,side))
    {
        ball.y = player.y - BALL_HEIGHT;
        yVelocity = -yVelocity;
    }

    check_brick_collision(ball,tiles,side,destroyedTile);
}

void Ball::show()
{
    apply_surface( (int)ball.x, (int)ball.y, ballSprite, screen );
}
