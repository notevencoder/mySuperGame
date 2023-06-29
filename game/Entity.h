#pragma once
#include "Box2d\box2d.h"
#include "Sprite.h"
class Entity
{
public:
	Entity() {}
	virtual void update() = 0;
protected:
	Sprite *sprite = nullptr;
	b2Body *body = nullptr;
};

