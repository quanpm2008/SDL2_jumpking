
#include "CommonFun.h"




void logSDLError(std::ostream& os,
                  const std::string &msg, bool fatal)
{
     os << msg << " Error: " << SDL_GetError() << std::endl;
           if (fatal) {
             SDL_Quit();
             exit(1);
}
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,int SCREEN_WIDTH,int SCREEN_HEIGHT, const string &WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logSDLError(std::cout, "SDL_Init", true);

         window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                  SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

//Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                    SDL_RENDERER_PRESENTVSYNC);
//Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
//renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer,SCREEN_WIDTH, SCREEN_HEIGHT);


    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        cout<<"SDL could not initialize! SDL Error:";
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    cout<<"SDL_mixer could not initialize! SDL_mixer Error:";
                }



}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
                ( e.type == SDL_QUIT ))
            return;

            SDL_Delay(100);
}
}
