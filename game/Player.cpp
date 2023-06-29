#include "Player.h"

Player::Player() {
	body = nullptr;
}
void Player::init(Level* lvl) {
	level = lvl;
	Object playerObject = level->GetObject("Player");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(level->getRenderer(), IMG_Load("Dungeon_Character.png"));
    
    sprite = new Sprite();
    sprite->setTexture(tex);
    sprite->setTextureRect(SDL_Rect{ 16,16,16,16 });
    sprite->setPosition(playerObject.rect.x, playerObject.rect.y);
    sprite->setScale(1, 1);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(playerObject.rect.x + level->GetTileSize().getX() / 2 * (playerObject.rect.w / level->GetTileSize().getX() - 1),
						 playerObject.rect.y + level->GetTileSize().getY() / 2 * (playerObject.rect.h / level->GetTileSize().getY() - 1));
	
	body = level->getWorld()->CreateBody(&bodyDef);
	b2FixtureDef fixDef;
	b2PolygonShape shape;
	shape.SetAsBox(playerObject.rect.w / 2, playerObject.rect.h / 2);
	fixDef.friction = 1;
	fixDef.density = 1;
	fixDef.shape = &shape;
	body->CreateFixture(&fixDef);

	b2Vec2 pos = getBody()->GetPosition();
	cam = { pos.x - 400 / 2, pos.y - 200 / 2,0,0 };

}

void Player::handleInput() {
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	b2Vec2 vec(0,0);
	if (keystates[SDL_SCANCODE_D]) {
		vec.x = 1.0f;
	}
	if (keystates[SDL_SCANCODE_A]) {
		vec.x = -1.0f;

	}
	if (keystates[SDL_SCANCODE_W]) {
		vec.y = -1.0f;
	}
	if (keystates[SDL_SCANCODE_S]) {
		vec.y = 1.0f;
	}
	vec *= 100;
	move(vec);
}

void Player::draw(SDL_Renderer* ren, SDL_FRect camera) {
	b2Vec2 ss = body->GetPosition();
	sprite->setPosition(ss.x,ss.y);
	sprite->draw(ren,cam);
}


void Player::update(){
	b2Vec2 ss = body->GetPosition();
	cam.x = ss.x - viewport.w / 2 / level->getScale();
	cam.y = ss.y - viewport.h/2 / level->getScale();/**/
}
