#include "King.h"

King :: King()
{
    x_val = 0;
    y_val = 0;

    x_pos = 0;
    y_pos = 0;

    HeightFrame = 64;
    WidthFrame = 61;
    KingStatus = -1;
    frame = 0;
    currentFrame = 0;
    JumpTime = 0;

    input_type.jump = false;
    input_type.left = false;
    input_type.right = false;
    input_type.falling = false;
    input_type.forcing = false;
    OnGround = false;
    Collision = false;

    map_y = 0;


}

void King :: set_clip()
{
    gjumpSound = Mix_LoadWAV("img//jump.wav");
    for(int i = 0; i < 2 ; i++)
    {
        frame_clip[i].x = i*WidthFrame;
        frame_clip[i].y = 0;
        frame_clip[i].w = WidthFrame;
        frame_clip[i].h = HeightFrame;
    }

}

void King :: Show(SDL_Renderer* renderer)
{

    if(OnGround)
    {
        LoadImage("img//Walking.png", renderer);
        currentFrame = 2;
    }
    else
    {
        LoadImage("img//Falling.png", renderer);
        currentFrame = 1;
    }

     if(input_type.forcing && OnGround)
    {
        LoadImage("img//Forcing.png", renderer);
    }
    if(input_type.jump)
    {
        LoadImage("img//Jumping.png", renderer);
    }
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(KingStatus == 1)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if(KingStatus == 0)
    {
        flip = SDL_FLIP_NONE;
    }

    if(input_type.left == true || input_type.right == true)
    {
        frame++;
    }

    else frame = 0;

    if(frame / 9 >= currentFrame)
    {
        frame = 0;
    }

    rect.x=x_pos;
    rect.y=y_pos - map_y;

    SDL_Rect* current_clip = &frame_clip[frame / 9];

    SDL_Rect renderQuad = {rect.x, rect.y, WidthFrame, HeightFrame};

    SDL_RenderCopyEx(renderer, p_object, current_clip, &renderQuad, NULL, NULL, flip);


}



void King ::HandleEvent(SDL_Event event )
{
     if(event.type == SDL_KEYDOWN && event.key.repeat == 0 )
     {
         switch(event.key.keysym.sym)
         {
         case SDLK_RIGHT:
             if(!input_type.forcing && !input_type.jump && !input_type.falling)
             {
             KingStatus = 0;
             input_type.right = true;
             break;
             }

         case SDLK_LEFT:
            if(!input_type.forcing && !input_type.jump && !input_type.falling){
            KingStatus = 1;
            input_type.left = true;
            break;
            }
         }

     }
     else if(event.type == SDL_KEYUP && event.key.repeat == 0 )
     {
         switch(event.key.keysym.sym)
         {
         case SDLK_RIGHT:
            input_type.right = false;
            input_type.left = false;
            break;
         case SDLK_LEFT:
            input_type.left = false;
            input_type.right = false;
            break;
         }
     }

     if(event.key.keysym.sym == SDLK_SPACE)
     {
         if(event.key.repeat == 0 && event.type == SDL_KEYDOWN && OnGround )
         {
             input_type.forcing = true;

         }
         else if(((event.key.repeat == 0 && event.type == SDL_KEYUP) || JumpTime == MAX_JUMP_TIME) && OnGround && input_type.forcing)
         {

             input_type.jump = true;
             input_type.forcing = false;
         }
     }


}

void King ::Do_Player( Map& map_data)
{
    cout<<input_type.falling<<"   "<<input_type.jump<<endl;
    x_val = 0;

    y_val += GRAVITY;



    if(y_val >= MAX_FALLING_VAL)
    {
        y_val = MAX_FALLING_VAL;

     }

    if(input_type.left)
    {
        x_val-=5;
    }

    else if(input_type.right)
    {
        x_val+=5;
    }
    else if(input_type.forcing)
    {
        if(JumpTime < MAX_JUMP_TIME)
             {
                 JumpTime++;
                 //cout<<JumpTime<<" ";
             }
    }
    else if(input_type.jump)
    {
        y_val -= MIN_JUMP_VAL + 20* JumpTime / MAX_JUMP_TIME;
        JumpTime = 0;
        OnGround = false;

        Mix_PlayChannel(-1, gjumpSound, 0);

        if(y_val <-MAX_JUMP_VAL)
        {
            input_type.jump = false;
            input_type.falling = true;
        }
    }
    else if(input_type.falling && !OnGround)
    {
        if(y_val < 0)
        {
            if(KingStatus == 0)
            {
               x_val += JUMP_VELX/6;
            }
            else
            {
            x_val -= JUMP_VELX/6;
            }
        }
        else {
        if(KingStatus == 0)
        {
            x_val += JUMP_VELX*2/3;
        }
        else
        {
            x_val -= JUMP_VELX*2/3;
        }}
    }

    if(Collision && !check)
    {
        if(KingStatus == 1)
        {
            KingStatus = 0;
            check = true;
        }
        else
        {
            KingStatus = 1;
            check = true;
        }
    }

    Check_map(map_data);
    SetCamera(map_data);
}


void King ::SetCamera(Map &map_data)
{
    if(y_pos + 1 > map_data.start_y + SCREEN_HEIGHT)
    {
        map_data.start_y += SCREEN_HEIGHT;
    }

    else if(y_pos + 1 < map_data.start_y)
    {
        map_data.start_y -= SCREEN_HEIGHT;
    }
}

void King ::Check_map(Map &map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;


    //Check va cham chieu ngang
    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + WidthFrame )/TILE_SIZE;

    y1 = y_pos/TILE_SIZE;
    y2 = (y_pos + HeightFrame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_x && y1 >= 0 && y2 <= MAX_MAP_y)
    {
        if(x_val > 0)
        {
            if(map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0)
            {
                x_val = 0;
                x_pos = x2*TILE_SIZE - WidthFrame ;
                if((input_type.jump || input_type.falling) && y_val >= 0)
                {
                    Collision = true;
                }
            }
            else
            {
                if(input_type.jump || input_type.falling)
                {
                    check = false;
                    Collision = false;
                }
            }
        }

        if(x_val < 0)
        {
            if(map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0)
            {
                x_val = 0;
                x_pos = (x1 + 1)*TILE_SIZE;
                if((input_type.jump || input_type.falling) && y_val >= 0)
                {
                    Collision = true;
                }
            }
            else
            {
                if(input_type.jump || input_type.falling)
                {
                    check = false;
                    Collision = false;
                }
            }
        }
    }
    //y_val = min( y_val + 1, MAX_FALLING_VAL);
    //check va cham chieu doc
    x1 = x_pos/TILE_SIZE;
    x2 = (x_pos + WidthFrame - 1)/TILE_SIZE;

    y1 = (y_pos + y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + HeightFrame)/TILE_SIZE;

    if((x1 >= 0 && x2 <= MAX_MAP_x) && (y1 >= 0 && y2 <= MAX_MAP_y))
    {
        if(y_val > 0)
        {
            if(map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0)
            {
                y_val = 0;
                y_pos = y2*TILE_SIZE - HeightFrame;
                OnGround = true;
                input_type.falling = false;
            }
            else OnGround = false;
        }

        if(y_val < 0)
        {
            if(map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0)
            {
                y_pos = (y1 + 1)*TILE_SIZE;
                y_val = 0;
            }

        }
    }


    y_pos += y_val;
    x_pos += x_val;


    if(x_pos < 0)
    {
        x_pos = 0;
    }

    else if(x_pos + WidthFrame > map_data.max_x)
    {
        x_pos = map_data.max_x - WidthFrame ;
    }
    //if (map_data.tile[((int)y_pos + HeightFrame) / 64][(int)x_pos / 64] == 0 && map_data.tile[((int)y_pos + HeightFrame) / 64][((int)x_pos + WidthFrame) / 64] == 0) OnGround = false;
    if(y_pos < 0)
    {
        y_pos = 0;
        y_val = 0;
    }
}
