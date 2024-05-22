#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "Map.h"
#include "King.h"
#include "Princess.h"


BaseObject background;
BaseObject background2;
BaseObject background3;
BaseObject background_EndGame;
BaseObject Menu;
BaseObject Pause;
BaseObject newgame;
BaseObject quit;

struct PAUSE
{
    BaseObject menu_;
    BaseObject quit_;
    BaseObject resume_;
    BaseObject newgame_;

};

PAUSE pause_;


Mix_Music* gMenuSound = NULL;
Mix_Music* gVictorySound = NULL;


bool CheckButton(SDL_Event &e, SDL_Rect image)
{
    bool inside = false;
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(x >= image.x && x <= image.x + image.w && y >= image.y && y <= image.y + image.h)
    {
        inside = true;
    }
    return inside;
}

int main(int argc, char* argv[])
{
   initSDL(window, renderer,SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE);

   gMenuSound = Mix_LoadMUS("img//menu.mp3");
   gVictorySound = Mix_LoadMUS("img//Victory.mp3");

   background.LoadImage("img//Jungle_background.png", renderer);
   background2.LoadImage("img//castle_wall_background.png", renderer);
   background3.LoadImage("img//Summer3.png", renderer);
   background_EndGame.LoadImage("img//EndGame.png", renderer);


   Menu.LoadImage("menu//background_of_menu.png", renderer);
   Pause.LoadImage("menu//menu.png", renderer);
   newgame.LoadImage("menu//newgame.png", renderer);
   quit.LoadImage("menu//quit.png", renderer);

   pause_.menu_.LoadImage("menu//Pause_menu.png", renderer);
   pause_.quit_.LoadImage("menu//Pause_quit.png", renderer);
   pause_.newgame_.LoadImage("menu//Pause_newgame.png", renderer);
   pause_.resume_.LoadImage("menu//Pause_resume.png", renderer);

   SDL_RenderClear(renderer);

   GameMap game_map;

   game_map.LoadMap("map/map01.dat");
   game_map.LoadTile(renderer);


   King king;
   Princess princess;
   //king.LoadImage("img//king.jpg", renderer);
   king.set_clip();
   princess.set_clip();


   bool flat = true;
   bool play = false;
   bool pause = false;
   bool EndGame = false;
   while (flat) {
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
    {
        flat = false;
    }
    king.HandleEvent(event);
//*****************************************************
//su li menu
    if(!play && !EndGame)
    {
        Menu.Render(renderer, NULL);
        newgame.SetRect(100, 300);
        quit.SetRect(100, 350);
        newgame.Render(renderer, NULL);
        quit.Render(renderer, NULL);

        if( Mix_PlayingMusic() == 0 )
                            {
                                //Play the music
                                Mix_PlayMusic( gMenuSound, -1 );
                            }
        if( Mix_PausedMusic() == 1 )
                                {
                                    //Resume the music
                                    Mix_PlayMusic( gMenuSound, -1 );
                                }

    }

    if(CheckButton(event, newgame.GetRect()) && event.type == SDL_MOUSEBUTTONDOWN && !play)
    {
        play = true;
        king.firstPos();
    }
    if(CheckButton(event, quit.GetRect()) && event.type == SDL_MOUSEBUTTONDOWN && !play)
    {
        flat = false;
    }
    //else if(check2 && event.type == SDL_MOUSEBUTTONDOWN && !play)

    if(play && event.key.keysym.sym == SDLK_ESCAPE)
    {
        Pause.SetRect(240,0);
        Pause.Render(renderer, NULL);
        pause = true;
    }
    if(pause)
    {
        pause_.resume_.SetRect(375, 200);
        pause_.menu_.SetRect(375, 400);
        pause_.newgame_.SetRect(375, 300);
        pause_.quit_.SetRect(375, 500);
        pause_.resume_.Render(renderer, NULL);
        pause_.quit_.Render(renderer, NULL);
        pause_.menu_.Render(renderer, NULL);
        pause_.newgame_.Render(renderer, NULL);

        if(CheckButton(event, pause_.resume_.GetRect()) && event.type == SDL_MOUSEBUTTONDOWN)
        {
            play = true;
            pause = false;
        }
        if(CheckButton(event, pause_.newgame_.GetRect()) && event.type == SDL_MOUSEBUTTONDOWN)
        {
             king.firstPos();
             play = true;
             pause = false;
        }
        if(CheckButton(event, pause_.menu_.GetRect()) && event.type == SDL_MOUSEBUTTONDOWN)
        {
            pause = false;
            play = false;
        }

        if(CheckButton(event, pause_.quit_.GetRect()) && event.type == SDL_MOUSEBUTTONDOWN)
        {
            pause = false;
            play = false;
            flat = false;
        }
    }



    if(EndGame)
    {
        background_EndGame.Render(renderer, NULL);
        pause_.menu_.SetRect(575, 300);
        pause_.menu_.Render(renderer, NULL);
         if( Mix_PausedMusic() == 1 )
                            {
                                //Play the music
                                Mix_PlayMusic( gVictorySound, -1 );
                            }

        if(CheckButton(event, pause_.menu_.GetRect()) && event.type == SDL_MOUSEBUTTONDOWN)
        {

            pause = false;
            play = false;
            EndGame = false;
            if (Mix_PausedMusic() == 0)
           {
                                    Mix_PauseMusic();
            }

        }

    }

//*******************************************************************************


    if(play && !pause)
    {
        if (Mix_PausedMusic() == 0)
           {
                                    Mix_PauseMusic();
            }
         Map map_data = game_map.GetMap();
         if(map_data.start_y < 3*640)
         {
              background3.Render(renderer, NULL);
         }
         else if(map_data.start_y < 5*640)
         {
              background2.Render(renderer, NULL);
         }
         else background.Render(renderer, NULL);

         if(map_data.start_y < 640)
         {
              princess.Show(renderer);
         }





    king.SetMap_y(map_data.start_y);
    king.Do_Player(map_data);

    game_map.SetMap(map_data);
    game_map.Drawmap(renderer);
    king.Show(renderer);


    king.drawJumpForce();
    SDL_Rect King_pos = king.GetRect();
    if((King_pos.x >= 576 && King_pos.x <= 600) && (King_pos.y <= 260 && King_pos.y >= 200)  && map_data.start_y < 640)
    {
        play = false;
        EndGame = true;
    }


    }
    SDL_RenderPresent(renderer);
    //SDL_Delay(16);

    }
    //waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;

}
