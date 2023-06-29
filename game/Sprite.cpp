#include "Sprite.h"


Sprite::Sprite() {
	
	dstrect = { 0,0,0,0 };
	srcrect = { 0,0,0,0 };

}
Sprite::~Sprite() {}
void Sprite::setTexture(SDL_Texture* tex) {
	texture = tex;
}
void Sprite::setTextureRect(SDL_Rect src) {

	srcrect = src;
	size.w = srcrect.w;
	size.h = srcrect.h;

	if (dstrect.w == 0)
		dstrect.w = size.w;

	if (dstrect.h == 0)
		dstrect.h = size.h;

}
void Sprite::setPosition(int x, int y) {
	
	size.x = dstrect.x = x;
	size.y = dstrect.y = y;

}
void Sprite::draw(SDL_Renderer* ren, SDL_FRect camera) {
	SDL_Rect finalDstrect = dstrect;
	finalDstrect.x -= camera.x;
	finalDstrect.y -= camera.y;
	SDL_RenderCopy(ren, texture, &srcrect, &finalDstrect);
	

}

void Sprite::setScale(int swidth, int sheight) {

	dstrect.w = size.w * swidth;
	dstrect.h = size.h * sheight;
}

SDL_Rect Sprite::getSize() {
	return size;

}


