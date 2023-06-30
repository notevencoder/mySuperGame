#include "Player.h"
#include<iostream>
Player::Player() {
	body = nullptr;
	level = nullptr;
}
void Player::init(Level* lvl) {
	level = lvl;
	Object playerObject = level->GetObject("Player");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(level->getRenderer(), IMG_Load("Dungeon_Character.png"));
    
    

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(playerObject.rect.x + level->GetTileSize().x / 2 * (playerObject.rect.w / level->GetTileSize().x - 1),
						 playerObject.rect.y + level->GetTileSize().y / 2 * (playerObject.rect.h / level->GetTileSize().y - 1));
	
	body = level->getWorld()->CreateBody(&bodyDef);
	
	b2FixtureDef fixDef;
	b2PolygonShape shape;
	shape.SetAsBox(playerObject.rect.w / 2, playerObject.rect.h / 2);
	fixDef.friction = 1;
	fixDef.density = 1;
	fixDef.shape = &shape;
	body->CreateFixture(&fixDef);

	sprite = new Sprite();
	sprite->setTexture(tex);
	sprite->setTextureRect(SDL_Rect{ 16,16,16,16 });
	sprite->setPosition(playerObject.rect.x, playerObject.rect.y);
	sprite->setScale(1, 1);

	b2Vec2 pos = getBody()->GetPosition();
	cam = { pos.x - 400 / 2, pos.y - 200 / 2, 0,0 };

}

void Player::handleInput() {
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	b2Vec2 vec(0,0);
	if (keystates[SDL_SCANCODE_D]) {
		vec.x += 1.0;
	}
	if (keystates[SDL_SCANCODE_A]) {
		vec.x += -1.0;

	}
	if (keystates[SDL_SCANCODE_W]) {
		vec.y += -1.0;
	}
	if (keystates[SDL_SCANCODE_S]) {
		vec.y += 1.0;
	}
	vec *= 10000;
	move(vec);
}

void Player::draw(SDL_Renderer* ren, SDL_FRect camera) {
	//b2Vec2 ss = body->GetPosition();
	auto shape = body->GetFixtureList()[0].GetShape();
	body->SetTransform(body->GetPosition(), 0.f);
	b2AABB aabb;
	shape->ComputeAABB(&aabb, body->GetTransform(), 0);


	b2Vec2 center = body->GetFixtureList()[0].GetAABB(0).GetCenter();
	auto lowerBound = body->GetFixtureList()[0].GetAABB(0).lowerBound;
	auto higherBound = body->GetFixtureList()[0].GetAABB(0).upperBound;

	float width = higherBound.x - lowerBound.x;
	float height = higherBound.y - lowerBound.y;
	sprite->setPosition(center.x - width / 2 + 1, center.y - height/2 + 1);
	sprite->draw(ren,cam);
}


void Player::update(){
	b2Vec2 ss = body->GetPosition();
	
	cam.x = ss.x - level->getViewport().w / 2 / level->getScale();
	cam.y = ss.y - level->getViewport().h / 2 / level->getScale();/**/

}
