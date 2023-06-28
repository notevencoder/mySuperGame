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
	void setPosition(int, int);
	void setScale(int,int);
	void draw(SDL_Renderer*,SDL_Rect);
	SDL_Rect getSize();
private:
	SDL_Rect size;
	SDL_Rect dstrect , srcrect;
	SDL_Texture* texture = nullptr;
};

