#include "Player.h"
#include<iostream>
Player::Player() {
	body = nullptr;
	level = nullptr;
}
void Player::init(Level* lvl) {
	level = lvl;

	desiredVel = currVel = {0,0};
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
	//fixDef.friction = 1;
	fixDef.density = 1;

	fixDef.shape = &shape;
	body->CreateFixture(&fixDef);

	sprite = new Sprite();
	sprite->setTexture(tex);
	sprite->setTextureRect(SDL_Rect{ 0,0,16,16 });
	sprite->setPosition(playerObject.rect.x, playerObject.rect.y);
	sprite->setScale(1, 1);

	b2Vec2 pos = body->GetPosition();
	cam = { pos.x - 400 / 2, pos.y - 200 / 2, 0,0 };
	
	b2MassData md = body->GetMassData();
	md.mass = 4;
	body->SetMassData(&md);
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
	sprite->setPosition(center.x - width / 2, center.y - height/2);
	sprite->draw(ren,cam);
	
	
	center = body->GetFixtureList()[0].GetAABB(0).GetCenter();
	SDL_SetRenderDrawColor(ren,255,0,0,1);
	SDL_RenderDrawLineF(ren, center.x - cam.x, center.y - cam.y, desiredPosition.x - cam.x, desiredPosition.y - cam.y);
	
	
}


void Player::update(){
	b2Vec2 ss = body->GetPosition();
	cam.x = ss.x - level->getViewport().w / 2 / level->getScale();
	cam.y = ss.y - level->getViewport().h / 2 / level->getScale();/**/

}



float map(float value,
	float istart,
	float istop,
	float ostart,
	float ostop) {
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
void Player::move(b2Vec2 velocity) {
	/*auto maxVel = maxVelocity * 0.16 * 100;

	velocity *= maxVel;

	currVel = body->GetLinearVelocity();
	

	

	desiredVel = velocity;

	if (desiredVel.Length() == 0 && body->GetLinearVelocity().Length() > 0) {
		desiredVel = currVel;
		desiredVel *= -0.1f * maxVel;

	}
	currVel = desiredVel - currVel;

	body->ApplyForceToCenter(currVel, true);
	body->ApplyForceToCenter(desiredVel, true);

	std::cout << "currVel: " << currVel.Length() << "desiredVel: " << desiredVel.Length() << '\n'
		<< "speed: " << body->GetLinearVelocity().Length();/**/

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

	/*if (velocity.Length() == 0) {
		currVel = body->GetLinearVelocity();
		currVel *= map(maxVel, 0,100, 0,maxVel);
	}
	else {
		currVel = velocity;
		currVel *= maxVel;
	}

	body->SetLinearVelocity(currVel);
	std::cout << "speed: " << body->GetLinearVelocity().Length()<<'\n';/**/
}

