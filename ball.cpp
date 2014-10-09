#include "ball.h"

SDL_Surface *screen = NULL;
SDL_Surface *paddleSprite = NULL;
SDL_Surface *ballSprite = NULL;

Ball::Ball()
{
    ball.x = 230;
    ball.y = 0;

    ball.h = BALL_HEIGHT;
    ball.w = BALL_WIDTH;

    xVelocity = 100;
    yVelocity = 100;
}

bool Ball::check_brick_collision(CustomRect A, Tile *tiles[])
{
    int leftA,leftB;
    int rightA,rightB;
    int topA,topB;
    int bottomA,bottomB;


    for(int t = 0; t < TOTAL_TILES; t++)
    {
        CustomRect B = tiles[t] -> get_box();
        leftB = B.x;
        rightB = B.x + B.w;
        topB = B.y;
        bottomB = B.y + B.h;

        if(check_collision(A,B) == true)
        {
            return true;
        }
    }

    return false;
}

bool Ball::check_collision(CustomRect A, CustomRect B)
{
    //The sides of the rectangles
    int leftA,leftB;
    int rightA,rightB;
    int topA,topB;
    int bottomA,bottomB;
    int side = 0;

    //Calculate the sides of the rect A
    leftA = A.x;
    rightA= A.x + A.w;
    topA = A.y ;
    bottomA = A.y + A.h;

    //Calculate the sides of the rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {

        return false;
    }

    if( leftA >= rightB )
    {

        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void Ball::move(CustomRect player, Tile *tiles[], float deltaTicks)
{
    ball.x += xVelocity *(deltaTicks/1000.f);
    ball.y += yVelocity *(deltaTicks/1000.f);

    if( ball.y < 0 )//Top collision
    {
        ball.y = 0;
        yVelocity = -yVelocity;
    }
    else if( ball.y + BALL_HEIGHT > SCREEN_HEIGHT )//Bottom wall
    {
        ball.y = SCREEN_HEIGHT - BALL_HEIGHT;
        yVelocity = -yVelocity;
    }
    else if(ball.x+BALL_HEIGHT > SCREEN_WIDTH)//Right wall
    {

        ball.x = SCREEN_WIDTH - BALL_WIDTH;
        xVelocity = -xVelocity;
    }
    else if(ball.x < 0 )//Left wall
    {
        ball.x = 0;
        xVelocity = -xVelocity;
    }

    if(check_collision(player,ball) == true)
    {
        ball.y = player.y - BALL_HEIGHT;
        yVelocity = -yVelocity;
    }

    if(check_brick_collision(ball,tiles) == true)
    {
        yVelocity = -yVelocity;
    }


}



void Ball::show()
{
    apply_surface( (int)ball.x, (int)ball.y, ballSprite, screen );
}
