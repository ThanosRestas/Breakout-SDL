#ifndef GLOBALS_H
#define GLOBALS_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdio.h>

//Screen attributes
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;
const unsigned int SCREEN_BPP = 32;

//The paddle's attribues
const unsigned int PADDLE_WIDTH = 16;
const unsigned int PADDLE_HEIGHT = 100;
const unsigned int SPEED = 1300;

//The ball's attributes
const unsigned int BALL_WIDTH = 18;
const unsigned int BALL_HEIGHT = 18;

//The tiling system's attributes
const int TILE_WIDTH = 100;
const int TILE_HEIGHT = 50;
const int TOTAL_TILES = 32;
const int TILE_SPRITES = 3;

//Tile sprite types
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;

extern SDL_Surface *screen ;
extern SDL_Surface *paddleSprite ;
extern SDL_Surface *ballSprite ;
extern SDL_Surface *tileSheet ;

extern SDL_Event event;

extern SDL_Surface *life;
extern SDL_Surface *showBallvelocityY;
extern SDL_Surface *showBallvelocityX;
extern SDL_Surface *showPlayerVelocity;


extern TTF_Font *font;
extern SDL_Color textColor;

extern SDL_Rect clips[TILE_SPRITES];

struct CustomRect
{
    float x;
    float y;
    int h;
    int w;
};

//bool check_collision(CustomRect A, CustomRect B,Tile *tiles[]);


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
bool init();
SDL_Surface *load_image( std::string filename );
bool load_files();
void clean_up();
void clip_tiles();



#endif // GLOBALS_H
