#pragma once
#include "Box2d\box2d.h"
#include "SDL2\SDL.h"
#include "Sprite.h"
#include  <set>
#include  <bitset>
#include  <vector>




using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 256;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;


struct Transform {
	b2Vec2 position;
};

struct Drawable {
	SDL_Renderer* ren;
	Sprite sprite;
};

struct Animated {
	int size;
	std::vector<Sprite> frames;
	float speed;
};

struct Body {
	b2Body* body;
};

class System
{
public:
	std::set<Entity> enteties;
};

