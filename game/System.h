#pragma once
#include "Box2d\box2d.h"
#include "SDL2\SDL.h"
#include  <set>
#include  <bitset>
#include  <vector>




using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;


struct Transform {
	SDL_FRect rect;
};

struct Drawable {
	SDL_FRect size;
	SDL_FRect dstrect;
	SDL_Rect srcrect;
	SDL_Texture* texture = nullptr;
};

struct Animated {
	int size;
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

