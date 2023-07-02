#include "DrawingSystem.h"
#include "Coordinator.h"
#include "Game.h"



void DrawingSystem::draw() {
	
	for (auto& entity : enteties) {

		auto& sprite = Coordinator::getInstance()->GetComponent<Drawable>(entity);
		auto& transform = Coordinator::getInstance()->GetComponent<Transform>(entity);



		b2Vec2 center = { transform.rect.x + transform.rect.w / 2,transform.rect.y + transform.rect.h / 2 };


		sprite.dstrect.x = center.x - transform.rect.w / 2;
		sprite.dstrect.y = center.y - transform.rect.h / 2;
		
		auto window = Game::getInstance()->getWindow();
		auto ren = SDL_GetRenderer(window);
		
		SDL_Rect vp;
		SDL_FPoint scale;
		SDL_RenderGetViewport(ren, &vp);
		SDL_RenderGetScale(ren, &scale.x, &scale.y);
		auto camera = Game::getInstance()->getCamera();
		sprite.dstrect = { sprite.dstrect.x - (camera->x - vp.x /scale.x /2), sprite.dstrect.y - (camera->y - vp.y / scale.y / 2),  
											  (float)sprite.srcrect.w ,  (float) sprite.srcrect.h  };
		//-level->getViewport().w / 2 / level->getScale()
		SDL_RenderCopyF(ren, sprite.texture, &sprite.srcrect, &sprite.dstrect);

	}

}