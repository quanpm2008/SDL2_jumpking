#ifndef King_h_
#define King_h_


#include "BaseObject.h"

class King : public BaseObject
{
public:

    King();
    //~King();

    void set_clip();
    void Show(SDL_Renderer* des);
    void HandleEvent(SDL_Event event);

    void Do_Player(Map &map_data);
    void Check_map(Map &map_data);
    void SetCamera(Map &map_data);
    void SetMap_y(int map_y)
    {
        this->map_y = map_y;
    }

    void firstPos()
    {
        x_pos = SCREEN_WIDTH / 2;
        y_pos = 4800;
    }
    void drawJumpForce(SDL_Renderer *renderer);


private:
    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int HeightFrame;
    int WidthFrame;
    int JumpTime;

    SDL_Rect frame_clip[8];
    Input input_type;
    int frame;
    int KingStatus;
    bool OnGround;
    bool Collision;

    bool check;
    int map_y;
    int currentFrame;

    Mix_Chunk* gjumpSound;
    Mix_Chunk* gFallSound;
    Mix_Chunk* gCollisionSound;
};


#endif // King_h_
