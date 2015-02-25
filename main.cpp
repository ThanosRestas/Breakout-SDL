#include "ball.h"
#include "globals.h"
#include "player.h"
#include "tile.h"


SDL_Event event;
TTF_Font *font;
SDL_Color textColor = { 255, 250, 250 };

SDL_Surface *life;

SDL_Surface *showBallvelocityY;
SDL_Surface *showBallvelocityX;
SDL_Surface *showPlayerVelocity;
SDL_Surface *tileSheet ;


SDL_Rect clips[ TILE_SPRITES ];

bool set_tiles(Tile *tiles[],int level)//Creating the map from the level1 text file
{
    int unsigned x = TILE_WIDTH;
    int unsigned y = TILE_HEIGHT;

    std::ifstream map("assets/level1.map");    

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
        if(x>= 9 * TILE_WIDTH)//Adjusting the appearance of the map
        {
            x = TILE_WIDTH;
            y+=TILE_HEIGHT;
        }
    }

    map.close();
    return true;
}


int main( int argc, char* args[] )
{
    bool quit = false;
    bool debug = false;
    int level = 1;
    Player control(200,700);
    Ball bullet(200 + PADDLE_WIDTH/2, 500);
    int tilesDestroyed = 0;

    float startTicks = 0;
    float deltaTicks = 0;
    char ballVelX[5];
    char ballVelY[5];
    char playerLife[5];


    Tile *tiles[TOTAL_TILES];
    int destroyedTile[TOTAL_TILES];


    for( int t = 0; t < TOTAL_TILES; t++ )
    {
       destroyedTile[t] = false;
    }

    if(init() == false)
    {
        return 5;
    }

    if(load_files() == false)
    {
        return 6;
    }

   clip_tiles();

   if( set_tiles( tiles , level ) == false )
   {
       return 1;
   }   

    startTicks = SDL_GetTicks();

    while(quit == false)
    {
        tilesDestroyed = 0;
        while(SDL_PollEvent(&event))
        {
           if((event.type == SDL_KEYDOWN))
            {

                if(event.key.keysym.sym == SDLK_1 && debug == true)//Adjusting velocity via the 1 number key in debuging mode
                {
                    bullet.xVelocity += 100;
                    bullet.yVelocity += 100;
                }
                else if(event.key.keysym.sym == SDLK_2 && debug == true)//Adjusting velocity via the 2 number key in debuging mode
                {
                    bullet.xVelocity -= 100;
                    bullet.yVelocity -= 100;
                }
                else if(event.key.keysym.sym == SDLK_F1)//Enabling or disabling debuging mode ( information of velocities)
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

            control.handle_input();//Handle the paddle's movement

            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        deltaTicks = SDL_GetTicks() - startTicks;//Frame rate
        control.move(deltaTicks);
        bullet.move(control.player,tiles,deltaTicks,destroyedTile);//Moving the ball

        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );//Black color every frame


        for( int t = 0; t < TOTAL_TILES; t++ )
        {
           if(destroyedTile[t] == 0)
           {
               tiles[ t ]->show();

           }
        }

        control.show();
        bullet.show();

        sprintf(ballVelX,"xVel %d",bullet.xVelocity);//Formating text to be displayed for the HUD
        sprintf(ballVelY,"yVel %d",bullet.yVelocity);
        sprintf(playerLife,"Life : %d",bullet.life);

        showBallvelocityX = TTF_RenderText_Solid(font,ballVelX,textColor);
        showBallvelocityY = TTF_RenderText_Solid(font,ballVelY,textColor);

        life = TTF_RenderText_Solid(font,playerLife,textColor);

        apply_surface(20, 10, life, screen );

        if(debug == true)
        {
            apply_surface(20, 50, showBallvelocityX, screen );
            apply_surface(20, 70, showBallvelocityY, screen );
            SDL_FreeSurface(showBallvelocityY);
            SDL_FreeSurface(showBallvelocityX);
        }

        startTicks = SDL_GetTicks();
        deltaTicks = 0;


        for( int t = 0; t < TOTAL_TILES; t++ )//Checking how many tiles are destroyed in the game
        {
           if(destroyedTile[t] == 1)
           {
               tilesDestroyed++;
           }
        }


        if(bullet.life == 0 || tilesDestroyed == TOTAL_TILES)//Close the game if life drops to zero or all the tiles are destroyed in the game
        {
            quit = true;
        }

        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }


    clean_up();
    return 0;

}
