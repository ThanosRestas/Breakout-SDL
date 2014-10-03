#include "ball.h"

SDL_Surface *screen = NULL;
SDL_Surface *paddleSprite = NULL;
SDL_Surface *ballSprite = NULL;

Ball::Ball()
{
    ball.x = 200;
    ball.y = 0;

    ball.h = BALL_HEIGHT;
    ball.w = BALL_WIDTH;

    xVelocity = 100;
    yVelocity = 100;
}

void Ball::move(CustomRect player, Uint32 deltaTicks)
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
    else if(check_collision(player,ball))
    {
        ball.y = player.y - BALL_HEIGHT;
        yVelocity = -yVelocity;
    }
}

void Ball::show()
{
    apply_surface( (int)ball.x, (int)ball.y, ballSprite, screen );
}
