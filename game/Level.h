#ifndef LEVEL_H
#define LEVEL_H

#include "Utils.h"

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include "SDL2\SDL.h"
#include "SDL2\SDL_image.h"
#include "Box2d\box2d.h"
#include "Vector2D.h"
#include "Sprite.h"

struct Object
{

    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

    std::string name;
    std::string type;
    SDL_FRect rect;
    //std::map<std::string, std::string> properties;
    std::unordered_map<std::string, std::string> properties;
    b2Body* body;
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
    Level(SDL_Renderer*, b2World*);
    ~Level();
    bool LoadFromFile(std::string filename);
    Object GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
    void draw(SDL_Renderer*, SDL_FRect);
    b2Vec2 GetTileSize();
   
    b2World* getWorld() { return world; }
    SDL_Renderer* getRenderer() { return renderer; }
    float getScale() { return scale; }
    void setScale(float s) { if (s > 1 && s < 20) scale = s; }
    SDL_Rect getViewport() { return viewport; }

private:

    int width, height, tileWidth, tileHeight;
    int firstTileID;
    SDL_Rect drawingBounds;
    SDL_Texture* tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
    SDL_Renderer* renderer;
    b2World* world;
    Object* player;
    float scale = 1;
    SDL_Rect viewport;
};

#endif
