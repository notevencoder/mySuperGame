#pragma once

#include "SDL2\SDL.h"
#include "memory"
class Sprite
{
public:
	Sprite();
	~Sprite();
	void setTexture(SDL_Texture*);
	void setTextureRect( SDL_Rect);
	void setPosition(float, float);
	void setScale(int,int);
	void draw(SDL_Renderer*,SDL_FRect);
	SDL_FRect getSize();
private:
	SDL_FRect size;
	SDL_FRect dstrect;
	SDL_Rect srcrect;
	SDL_Texture* texture = nullptr;
};

