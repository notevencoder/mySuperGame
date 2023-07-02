#include "Player.h"
#include<iostream>
#include "Coordinator.h"
#include "Game.h"


Player::Player() {
	body = nullptr;
	level = nullptr;

}
void Player::init(Level* lvl) {

	entity = Coordinator::getInstance()->CreateEntity();
	level = lvl;

	desiredVel = currVel = {0,0};
	Object playerObject = level->GetObject("Player");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(level->getRenderer(), IMG_Load("Dungeon_Character.png"));
    
    

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(playerObject.rect.x + level->GetTileSize().x / 2 * (playerObject.rect.w / level->GetTileSize().x - 1),
						 playerObject.rect.y + level->GetTileSize().y / 2 * (playerObject.rect.h / level->GetTileSize().y - 1));
	
	body = level->getWorld()->CreateBody(&bodyDef);
	
	
	b2BodyDef bodyDef2;
	bodyDef2.type = b2_kinematicBody;
	bodyDef2.fixedRotation = true;
	
	bodyDef2.position.Set(playerObject.rect.x + 25 + level->GetTileSize().x / 2 * (playerObject.rect.w / level->GetTileSize().x - 1),
						 playerObject.rect.y  + level->GetTileSize().y / 2 * (playerObject.rect.h / level->GetTileSize().y - 1));


	b2FixtureDef fixDef;
	b2PolygonShape shape;
	shape.SetAsBox(playerObject.rect.w / 2 , playerObject.rect.h / 2 );
	fixDef.shape = &shape;
	

	b2FixtureDef fixDef2;
	fixDef2.isSensor = true;
	b2PolygonShape shape2;
	shape2.SetAsBox(playerObject.rect.w / 2, playerObject.rect.h / 2, b2Vec2(20,0), 0);
	fixDef2.shape = &shape2;



	body->CreateFixture(&fixDef2);
	body->CreateFixture(&fixDef);
	

	b2Vec2 pos = body->GetPosition();
	cam = { pos.x - 400 / 2, pos.y - 200 / 2, 0,0 };
	
	b2MassData md = body->GetMassData();
	md.mass = 4;
	body->SetMassData(&md);
	
	Drawable lol;
	lol.texture = tex;
	lol.srcrect = SDL_Rect{ 0,0,16,16 };
	lol.dstrect = SDL_FRect{ body->GetPosition().x, body->GetPosition().y,16,16 };
	
	Coordinator::getInstance()->AddComponent(entity, Transform{ pos.x, pos.y, playerObject.rect.w,playerObject.rect.h });
	Coordinator::getInstance()->AddComponent(entity, lol);
	Coordinator::getInstance()->AddComponent(entity, Body{body});


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
	move(vec);
}

void Player::draw(SDL_Renderer* ren) {
	//b2Vec2 ss = body->GetPosition();
	/**/
	auto camera = Game::getInstance()->getCamera();
	//sprite->draw(ren,*camera);
	
	
	auto center = body->GetFixtureList()[0].GetAABB(0).GetCenter();
	SDL_SetRenderDrawColor(ren,255,0,0,1);
	SDL_RenderDrawLineF(ren, center.x - camera->x, center.y - camera->y, desiredPosition.x - camera->x, desiredPosition.y - camera->y);
	/**/
	
}


void Player::update(){


}



float map(float value,
	float istart,
	float istop,
	float ostart,
	float ostop) {
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
void Player::move(b2Vec2 velocity) {
	

	

	auto lowerBound = body->GetFixtureList()[0].GetAABB(0).lowerBound;
	auto higherBound = body->GetFixtureList()[0].GetAABB(0).upperBound;

	float width = higherBound.x - lowerBound.x;

	auto maxVel = maxVelocity * 16;
	auto center = body->GetFixtureList()[0].GetAABB(0).GetCenter();
	if (velocity.Length() > 0) {
		desiredPosition = center;
		auto lol = velocity;
		lol *= width / 2;
		desiredPosition += lol;
		currVel = desiredPosition - center ;
		currVel *= maxVel;
	}
	else {
		currVel = body->GetLinearVelocity();
		currVel.Normalize();
		currVel *= map((desiredPosition - center).Length(),0,10,0,maxVel);
	}
	

	body->SetLinearVelocity(currVel);

	std::cout << "speed: " << body->GetLinearVelocity().Length() << '\n'
				<< "desiredPosition x: " << desiredPosition.x << " y: "<< desiredPosition.y << '\n';/**/

	
}

