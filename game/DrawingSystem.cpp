#include "DrawingSystem.h"
#include "Coordinator.h"
#include "Game.h"



void DrawingSystem::draw() {
	
	for (auto& entity : enteties) {

		auto& sprite = Coordinator::getInstance()->GetComponent<Drawable>(entity);
		auto& body = Coordinator::getInstance()->GetComponent<Body>(entity).body;

		auto shape = body->GetFixtureList()[0].GetShape();
		body->SetTransform(body->GetPosition(), 0.f);
		b2AABB aabb;
		shape->ComputeAABB(&aabb, body->GetTransform(), 0);


		b2Vec2 center = body->GetFixtureList()[0].GetAABB(0).GetCenter();
		auto lowerBound = body->GetFixtureList()[0].GetAABB(0).lowerBound;
		auto higherBound = body->GetFixtureList()[0].GetAABB(0).upperBound;

		float width = higherBound.x - lowerBound.x;
		float height = higherBound.y - lowerBound.y;

		sprite.dstrect.x = center.x - width / 2;
		sprite.dstrect.y = center.y - height / 2;

		auto window = Game::getInstance()->getWindow();
		auto ren = SDL_GetRenderer(window);
		
		SDL_Rect vp;
		SDL_FPoint scale;
		SDL_RenderGetViewport(ren, &vp);
		SDL_RenderGetScale(ren, &scale.x, &scale.y);
		auto camera = Game::getInstance()->getCamera();
		//sprite.dstrect = { sprite.dstrect.x - camera->x, sprite.dstrect.y - camera->y};

		SDL_RenderCopyF(ren, sprite.texture, &sprite.srcrect, &sprite.dstrect);

	}

}