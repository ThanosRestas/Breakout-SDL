#include "ball.h"
#include "globals.h"
#include "player.h"
#include "timer.h"


SDL_Event event;
TTF_Font *font;
SDL_Color textColor = { 255, 250, 250 };

SDL_Surface *showTicks;

SDL_Surface *showBallvelocityY;
SDL_Surface *showBallvelocityX;
SDL_Surface *showPlayerVelocity;


int main( int argc, char* args[] )
{
    bool quit = false;
    Player control(200,700);
    Ball bullet;
    Uint32 startTicks = 0;
    Uint32 deltaTicks = 0;
    char ballVelX[5];
    char ballVelY[5];
    bool debug = false;

    if(init() == false)
    {
        return 1;
    }

    if(load_files() == false)
    {
        return 2;
    }

    startTicks = SDL_GetTicks();

    while(quit == false)
    {                
        while(SDL_PollEvent(&event))
        {
           if((event.type == SDL_KEYDOWN))
            {

                if(event.key.keysym.sym == SDLK_1)
                {
                    bullet.xVelocity += 100;
                    bullet.yVelocity += 100;
                }
                else if(event.key.keysym.sym == SDLK_2)
                {
                    bullet.xVelocity -= 100;
                    bullet.yVelocity -= 100;
                }
                else if(event.key.keysym.sym == SDLK_F1)
                {
                    if(debug == false)
                    {
                        debug = true;
                    }
                    else
                    {
                        debug = false;
                    }

                }
            }

            control.handle_input();



            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        deltaTicks = SDL_GetTicks() - startTicks;
        control.move(deltaTicks);
        bullet.move(control.player,deltaTicks);

        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
        control.show();
        bullet.show();

        sprintf(ballVelX,"xVel %d",bullet.xVelocity);
        sprintf(ballVelY,"yVel %d",bullet.yVelocity);

        showBallvelocityX = TTF_RenderText_Solid(font,ballVelX,textColor);
        showBallvelocityY = TTF_RenderText_Solid(font,ballVelY,textColor);

        if(debug == true)
        {
            apply_surface(20, 10, showBallvelocityX, screen );
            apply_surface(20, 50, showBallvelocityY, screen );
            SDL_FreeSurface(showBallvelocityY);
            SDL_FreeSurface(showBallvelocityX);
        }





        startTicks = SDL_GetTicks();
        deltaTicks = 0;

        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }


    clean_up();
    return 0;

}
