#include "Map.h"
#include <fstream>

void GameMap::LoadMap(string path)
{
    fstream file;
    file.open(path);
    game_map.max_x=0;
    game_map.max_y=0;

    string line;
    while(getline(file, line))
    {
        game_map.max_x=0;
        stringstream ss(line);
        while(ss>>line)
        {
            int val = stoi(line);
            game_map.tile[game_map.max_y][game_map.max_x] = val;
            game_map.max_x++;
        }
        game_map.max_y++;
    }

    game_map.max_x = game_map.max_x*TILE_SIZE;
    game_map.max_y = game_map.max_y*TILE_SIZE;

    game_map.start_x=0;
    game_map.start_y=4480;

    file.close();
}



void GameMap::LoadTile(SDL_Renderer* renderer)
{
   fstream file;

   for(int i=0; i < MAX_TILE;i++)
   {
       string file_name ="map/" + to_string(i) + ".png";
       file.open(file_name);

       if(file.is_open())
       {
           file.close();
           tile_map[i].LoadImage(file_name, renderer);
       }

   }
}

void GameMap::Drawmap(SDL_Renderer* renderer)
{

    int x = 0;
    int y = 0;

    int map_y1 = game_map.start_y/TILE_SIZE;
    int map_y2 = (game_map.start_y + SCREEN_HEIGHT)/TILE_SIZE;

    for(int i = map_y1 ; i < map_y2 ; i++ )
    {
        x=0;
        for(int j = 0 ; j < SCREEN_WIDTH/TILE_SIZE ; j++)
        {
            int val = game_map.tile[i][j];
            if(val > 0)
            {
                tile_map[val].SetRect(x, y);
                tile_map[val].Render(renderer, NULL);
            }
            x+=TILE_SIZE;
        }
        y+=TILE_SIZE;

    }

}
