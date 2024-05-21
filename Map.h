
#ifndef Map_h
#define Map_h

#include "BaseObject.h"

#define MAX_TILE 100

class TileMap : public BaseObject
{
public:
    TileMap() {;}
};

class GameMap
{
public:
    GameMap() {;}
    void LoadMap(string path);
    void LoadTile(SDL_Renderer* renderer);
    void Drawmap(SDL_Renderer* renderer);
    Map GetMap()
    {
        return game_map;
    }

    void SetMap(Map &map_data)
    {
        game_map = map_data;
    }

private:
    Map game_map;
    TileMap tile_map[MAX_TILE];
};










#endif // Map_h
