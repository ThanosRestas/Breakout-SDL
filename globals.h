#ifndef GLOBALS_H
#define GLOBALS_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <string>
#include <stdlib.h>
#include <sstream>

//Screen attributes
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;
const unsigned int SCREEN_BPP = 32;

//The paddle's attribues
const unsigned int PADDLE_WIDTH = 16;
const unsigned int PADDLE_HEIGHT = 100;
const unsigned int SPEED = 1000;


//The ball's attributes
const unsigned int BALL_WIDTH = 18;
const unsigned int BALL_HEIGHT = 18;

extern SDL_Surface *screen ;
extern SDL_Surface *paddleSprite ;
extern SDL_Surface *ballSprite ;
extern SDL_Event event;

extern SDL_Surface *showTicks;
extern SDL_Surface *showBallvelocityY;
extern SDL_Surface *showBallvelocityX;
extern SDL_Surface *showPlayerVelocity;


extern TTF_Font *font;
extern SDL_Color textColor;

struct CustomRect
{
    float x;
    float y;
    int h;
    int w;
};

bool check_collision(CustomRect A, CustomRect B);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
bool init();
SDL_Surface *load_image( std::string filename );
bool load_files();
void clean_up();

#endif // GLOBALS_H
