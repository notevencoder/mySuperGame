#include "Game.h"
#include "Coordinator.h"




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
	Coordinator::getInstance()->Init();

	Coordinator::getInstance()->RegisterComponent<Animated>();
	Coordinator::getInstance()->RegisterComponent<Drawable>();
	Coordinator::getInstance()->RegisterComponent<Transform>();
	Coordinator::getInstance()->RegisterComponent<Body>();

	drawingSystem = Coordinator::getInstance()->RegisterSystem<DrawingSystem>();

	

	b2Vec2 gravity(0.0f, 0.0f);
	world = new b2World(gravity);
	
	
	level = new Level(renderer, world);
	level->LoadFromFile("level1/level1.tmx");
	level->setScale(5);

	player.init(level);
	
	camera = { player.getBody()->GetPosition().x - 400 / 2, player.getBody()->GetPosition().y - 200 / 2, 0,0 };
	
	debug = new DebugRenderer(renderer);
	debug->SetFlags(b2Draw::e_shapeBit);
	world->SetDebugDraw(debug);

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
	if (keystates[SDL_SCANCODE_RIGHT]) {
		std::cout << "right\n";
	}
	if (keystates[SDL_SCANCODE_LEFT]) {
		std::cout << "left\n";
		camera.x -= 5;

	}
	if (keystates[SDL_SCANCODE_UP]) {
		level->setScale(level->getScale() + 0.5f);
		std::cout << "\nup";
		camera.y -= 5;
	}
		if (keystates[SDL_SCANCODE_DOWN]) {
			level->setScale(level->getScale() - 0.5f);
			std::cout << "down\n";
			camera.y += 5;
		}
	if (keystates[SDL_SCANCODE_ESCAPE])
		isRunning = false;

	player.handleInput();
}

void Game::update() {
	world->Step(1.0f / 60.0f, 1, 1);
	auto camera = getCamera();
	b2Vec2 ss = player.getBody()->GetPosition();

	camera->x = ss.x - level->getViewport().w / 2 / level->getScale();
	camera->y = ss.y - level->getViewport().h / 2 / level->getScale();/**/
}

void Game::draw() {
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);

	SDL_Rect vp = level->getViewport();
	SDL_RenderSetScale(renderer, level->getScale(), level->getScale());
	SDL_RenderSetViewport(renderer, &vp);
	
	drawingSystem.get()->draw();
	world->DebugDraw();
	
	SDL_RenderPresent(renderer);
}


void Game::ShutDown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyRenderer(debugRen);
	SDL_DestroyWindow(window);
	SDL_Quit();

}