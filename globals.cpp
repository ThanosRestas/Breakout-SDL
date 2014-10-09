#include "globals.h"

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if(TTF_Init() == -1)
    {
        return false;
    }

    //Initialize SDL_mixer


    //Set the window caption
    SDL_WM_SetCaption( "SDL-Breakout", NULL );

    //If everything initialized fine
    return true;
}

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

bool load_files()
{
    //Load the dot image
    paddleSprite = load_image( "assets/Paddle.bmp" );
    ballSprite = load_image("assets/ball.bmp");
    font = TTF_OpenFont("assets/gothic.ttf", 20);
    tileSheet = load_image("assets/spritesheet.bmp");

    if( paddleSprite == NULL )
    {
        return 1;
    }

    if(ballSprite == NULL)
    {
        return 2;
    }

    if(font == NULL)
    {
        return 3;
    }

    if(tileSheet == NULL)
    {
        return 4;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface(screen);
    SDL_FreeSurface(paddleSprite);
    SDL_FreeSurface(showTicks);
    SDL_FreeSurface(showBallvelocityY);
    SDL_FreeSurface(showBallvelocityX);
    SDL_FreeSurface(showPlayerVelocity);



    //Quit SDL
    SDL_Quit();
}

void clip_tiles()
{
    clips[ TILE_BLUE ].x = 0;
    clips[ TILE_BLUE ].y = 0;
    clips[ TILE_BLUE ].w = TILE_WIDTH;
    clips[ TILE_BLUE ].h = TILE_HEIGHT;

    clips[ TILE_GREEN ].x = 0;
    clips[ TILE_GREEN ].y = 51;
    clips[ TILE_GREEN ].w = TILE_WIDTH;
    clips[ TILE_GREEN ].h = TILE_HEIGHT;

    clips[ TILE_RED ].x = 0;
    clips[ TILE_RED ].y = 102;
    clips[ TILE_RED ].w = TILE_WIDTH;
    clips[ TILE_RED ].h = TILE_HEIGHT;

}




























