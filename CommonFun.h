#ifndef COMMON_Func_h_
#define COMMON_Func

#include<bits/stdc++.h>
#include<windows.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

#include<string>
using namespace std;

static SDL_Window* window =nullptr;
static SDL_Renderer* renderer=nullptr;
static SDL_Event event;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const string WINDOW_TITLE = "Lien Minh Huyen Thoai";

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


const int MIN_JUMP_VAL = 5;
const int MAX_JUMP_VAL = 10;
const float MAX_FALLING_VAL = 10;
const int MAX_JUMP_TIME = 30;
const int JUMP_VELX = 10;

const int GRAVITY = 1;



static Mix_Chunk* gjumpSound;
static Mix_Music* gMenuSound;








#define TILE_SIZE 64

#define MAX_MAP_x 15
#define MAX_MAP_y 100

struct Input
{
    bool right;
    bool left;
    bool jump;

    bool falling;
    bool forcing;

};


struct Map
{
    int start_x;
    int start_y;

    int max_x;
    int max_y;


    int tile[MAX_MAP_y][MAX_MAP_x];


};




void logSDLError(std::ostream& os,
                  const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
                int SCREEN_WIDTH , int SCREEN_HEIGHT, const string &WINDOW_TITLE);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();


#endif // COMMON_Func





