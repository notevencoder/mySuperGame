#pragma once
#include "Box2d\box2d.h"
#include "Level.h"
#include "memory.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

class bodyFactory
{


public:
	
	static bodyFactory& getInstance() {
		static bodyFactory  instance;
		return instance;
	}
	b2Body* createRectBody(b2World*, const tmx::Object&, b2BodyType);
	~bodyFactory() {}
private:
	bodyFactory() {}
	bodyFactory(const bodyFactory&);
	bodyFactory& operator=(bodyFactory&);
};

