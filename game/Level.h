#ifndef LEVEL_H
#define LEVEL_H


#include <string>
#include <vector>
#include <memory>
#include <map>
#include "SDL2\SDL.h"
#include "SDL2\SDL_image.h"
#include "Vector2D.h"
#include "Sprite.h"


struct Object
{
    
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

    std::string name;
    std::string type;
    SDL_Rect rect;
    std::map<std::string, std::string> properties;

	Sprite* sprite;
};

struct Layer
{
    int opacity;
    std::vector<Sprite*> tiles;
};


class Level
{
public:
    Level(SDL_Renderer*);
    ~Level();
    bool LoadFromFile(std::string filename);
    Object GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
    void draw(SDL_Renderer *, SDL_Rect);
	Vector2D GetTileSize();


private:
    
    int width, height, tileWidth, tileHeight;
    int firstTileID;
    SDL_Rect drawingBounds;
    SDL_Texture* tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
    SDL_Renderer* renderer;

};

#endif
