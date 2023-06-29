#pragma once
#include "Sprite.h"
#include "Level.h"
#include "Box2d\box2d.h"
class Player
{
public:
	explicit Player();
	void init(Level*);
	void handleInput();
	void update();
	void setBody(b2Body* b) { body = b; }
	SDL_FRect* getCamera() { return &cam; }
	b2Body* getBody() { return body; }
	void setViewport(SDL_Rect vp) { viewport = vp; }
	void inline move(b2Vec2 pos) { body->ApplyLinearImpulseToCenter(pos, true); }

	void draw(SDL_Renderer* ren, SDL_FRect rec);
private:
	b2Body* body = nullptr;
	Sprite* sprite = nullptr;
	Level* level;
	SDL_Rect viewport;
	SDL_FRect cam = {0,0,0,0};

};

