#ifndef Princess_h_
#define Princess_h_

#include "BaseObject.h"

class Princess : public BaseObject
{
public:
    Princess();
    //~King();

    void set_clip();
    void Show(SDL_Renderer* des);
private:

    int HeightFrame;
    int WidthFrame;
    int frame = 0;
    SDL_Rect frame_clip[8];

};

#endif // Princess_h_

