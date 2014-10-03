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

bool check_collision(CustomRect A, CustomRect B)
{
    //The sides of the rectangles
    int leftA,leftB;
    int rightA,rightB;
    int topA,topB;
    int bottomA,bottomB;

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
    if( bottomA <= topB ) { return false; }
    if( topA >= bottomB ) { return false; }
    if( rightA <= leftB ) { return false; }
    if( leftA >= rightB ) { return false; }

    //If none of the sides from A are outside B
    return true;
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

    if( paddleSprite == NULL )
    {
        return false;
    }

    if(ballSprite == NULL)
    {
        return false;
    }

    if(font == NULL)
    {
        return false;
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
