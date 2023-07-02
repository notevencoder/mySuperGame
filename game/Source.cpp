#include "Game.h"
#include "Sprite.h"

int main(int argc, char* argv[]) {

	/**/
	Game* game = Game::getInstance();

	if(game)
		game->GameLoop();

	game->ShutDown();
	/*
	SDL_Window* window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	SDL_Surface* surface = IMG_Load("tileset.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	Layer layer;
	Sprite* sprite = new Sprite();

	layer.tiles.push_back(sprite);
	sprite->setTexture(texture);

	sprite->setTextureRect({ 64,64,400,400 });
	sprite->setPosition(0, 0);
	sprite->setScale(1, 1);

	bool quit = false;
	while (!quit)
	{
		SDL_Event e;
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//Clear screen
		SDL_RenderClear(renderer);
		//SDL_Rect srcrect = { 0,0,100,100}, dstrect = { 0,0,800,400 };
		//SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
		SDL_Rect vp = { 200,200,400,400 };
		SDL_RenderSetViewport(renderer, &vp);
		layer.tiles[0]->setScale(4,4);
		layer.tiles[0]->draw(renderer);
		//Update screen
		SDL_RenderPresent(renderer);
	}
		/**/
	return 0;
}