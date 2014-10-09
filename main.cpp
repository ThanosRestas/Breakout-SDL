#include "ball.h"
#include "globals.h"
#include "player.h"
#include "timer.h"
#include "tile.h"


SDL_Event event;
TTF_Font *font;
SDL_Color textColor = { 255, 250, 250 };

SDL_Surface *showTicks;

SDL_Surface *showBallvelocityY;
SDL_Surface *showBallvelocityX;
SDL_Surface *showPlayerVelocity;
SDL_Surface *tileSheet ;


SDL_Rect clips[ TILE_SPRITES ];

bool set_tiles(Tile *tiles[])
{
    int unsigned x = 100;
    int unsigned y = 100;

    std::ifstream map("assets/tilemap.map");

    if( map == NULL )
    {
        return false;
    }

    for(int t = 0 ; t < TOTAL_TILES; t++)
    {
        int tileType = -1;

        map >> tileType;

        if(map.fail() == true)
        {
            map.close();
            return false;
        }

        if((tileType >= 0) && (tileType < TILE_SPRITES))
        {
            tiles[t] = new Tile(x,y,tileType);
        }
        else
        {
            map.close();
            return false;
        }

        x+= TILE_WIDTH;
        if(x>= SCREEN_WIDTH)
        {
            x = 0;
            y+=TILE_HEIGHT;
        }

    }

    map.close();
    return true;
}


int main( int argc, char* args[] )
{
    bool quit = false;
    Player control(200,700);
    Ball bullet;
    float startTicks = 0;
    float deltaTicks = 0;
    char ballVelX[5];
    char ballVelY[5];
    bool debug = false;

    Tile *tiles[TOTAL_TILES];

    if(init() == false)
    {
        return 5;
    }

    if(load_files() == false)
    {
        return 6;
    }

    clip_tiles();

   if( set_tiles( tiles ) == false )
   {
       return 1;
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
        bullet.move(control.player,tiles,deltaTicks);

        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );


        for( int t = 0; t < TOTAL_TILES; t++ )
        {
           tiles[ t ]->show();
        }

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
