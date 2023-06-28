#pragma once
#include "Utils.h"
#include "Level.h"
#include "Box2d\Box2d.h"

class Game
{
public:
	bool init();
	void GameLoop();
	void ShutDown();
private:
	void handleInput();
	void update();
	void draw();
	bool isRunning = true;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Level* level = nullptr;
	Sprite* sprite;
	SDL_Rect camera;
};

