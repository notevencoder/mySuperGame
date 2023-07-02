#pragma once
#include "Sprite.h"
#include "Level.h"
#include "Box2d\box2d.h"
#include "Utils.h"
#include "System.h"
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
	void move(b2Vec2 pos);

	void draw(SDL_Renderer* ren, SDL_FRect rec);
private:
	b2Vec2 desiredVel, currVel;
	float maxVelocity = 3;
	b2Body* body = nullptr;
	b2Vec2 desiredPosition;
	Sprite* sprite = nullptr;
	Level* level;
	SDL_FRect cam = {0,0,0,0};



};

