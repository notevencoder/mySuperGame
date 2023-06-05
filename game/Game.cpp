#include "Game.h"


bool Game::init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cout << "SDL failed to init:" << SDL_GetError() << '\n';
		return false;
	}

	window = SDL_CreateWindow("MySuperGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!window) {
		std::cout << "SDL failed to init:" << SDL_GetError() << '\n';
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) {
		std::cout << "SDL failed to init:" << SDL_GetError() << '\n';
		return false;
	}

	return true;

}

void Game::GameLoop() {
	while (isRunning) {
		handleInput();
		update();
		draw();
	}
}

void Game::handleInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
	}

	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_ESCAPE])
		isRunning = false;
}

void Game::update() {}

void Game::draw() {
	SDL_SetRenderDrawColor(renderer, 40,40,40,255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}


void Game::ShutDown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}