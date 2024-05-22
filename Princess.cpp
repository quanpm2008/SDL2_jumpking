#include "Princess.h"

Princess :: Princess()
{



    HeightFrame = 64;
    WidthFrame = 64;


    frame = 0;

}


void Princess :: set_clip()
{
    for(int i = 0; i < 8 ; i++)
    {
        frame_clip[i].x = i*WidthFrame;
        frame_clip[i].y = 0;
        frame_clip[i].w = WidthFrame;
        frame_clip[i].h = HeightFrame;
    }

}

void Princess :: Show(SDL_Renderer* renderer)
{
    LoadImage("img//Princess.png", renderer);




        if(frame/12 >= 8)
        {
            frame = 0;
        }

        frame++;




    rect.x= 576;
    rect.y= 256 ;

    SDL_Rect* current_clip = &frame_clip[frame/12];

    SDL_Rect renderQuad = {rect.x, rect.y, WidthFrame, HeightFrame};

    SDL_RenderCopy(renderer, p_object, current_clip, &renderQuad);


}




