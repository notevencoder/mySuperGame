#include "bodyFactory.h"
#include <iostream>

b2Body* bodyFactory::createRectBody(b2World* world, const tmx::Object& obj, const  b2BodyType type = b2_staticBody) {
	
	auto width = obj.getAABB().width;
	auto height = obj.getAABB().height;
	
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position.Set(obj.getPosition().x + width / 2, obj.getPosition().y + height / 2);
	b2Body* body = world->CreateBody(&bodyDef);
	std::cout << bodyDef.position.x << " " << bodyDef.position.y << '\n';
	


	b2FixtureDef fixDef;
	b2PolygonShape shape;

	shape.SetAsBox(width / 2, height / 2);

	fixDef.shape = &shape;
	body->CreateFixture(&fixDef);


	return body;
}


