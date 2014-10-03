#include "player.h"

Player::Player(int xUser, int yUser)
{
       player.x = xUser;
       player.y = yUser;
       player.w = PADDLE_HEIGHT;
       player.h = PADDLE_WIDTH;
       xVelocity = 0;
}

void Player::handle_input()
{
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_LEFT)
        {
            xVelocity -= SPEED;
        }
        else if(event.key.keysym.sym == SDLK_RIGHT)
        {
            xVelocity += SPEED;
        }
    }
    else if(event.type == SDL_KEYUP)
    {
        if(event.key.keysym.sym == SDLK_LEFT)
        {
            xVelocity += SPEED;
        }
        else if(event.key.keysym.sym == SDLK_RIGHT)
        {
            xVelocity -= SPEED;
        }
    }
}

void Player::move(Uint32 deltaTicks)
{
    player.x += xVelocity *(deltaTicks/1000.f);


    if( player.x < 0 )
    {
        player.x = 0;
    }
    else if( player.x + PADDLE_HEIGHT > SCREEN_WIDTH)
    {
        player.x = SCREEN_WIDTH - PADDLE_HEIGHT;
    }
}

void Player::show()
{
    apply_surface( (int)player.x, (int)player.y, paddleSprite, screen );
}
