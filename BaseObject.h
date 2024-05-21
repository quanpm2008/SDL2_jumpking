#ifndef Base_object_
#define Base_object_

#include "CommonFun.h"

class BaseObject
{

public:
    BaseObject();
    //~BaseObject();

    void SetRect(const int x, const int y)
    {
        rect.x=x;
        rect.y=y;
    }

    SDL_Rect GetRect()
    {
        return rect;
    }

    SDL_Texture* GetTexture()
    {
        return p_object;
    }

    void LoadImage(string path, SDL_Renderer* renderer);
    void Render(SDL_Renderer* des, SDL_Rect* clip);


protected:
    SDL_Texture* p_object;
    SDL_Rect rect;
};






#endif // Base_object_
