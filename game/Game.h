#pragma once
#include "Utils.h"
#include "Level.h"
#include "Box2d\Box2d.h"
#include "Player.h"
#include "DebugRenderer.h"
#include <iostream>
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
	SDL_Renderer* renderer = nullptr, *debugRen = nullptr;
	Level* level = nullptr;
	Sprite* sprite;
	SDL_FRect camera;
	b2World* world = nullptr;
	Player player;
	DebugRenderer* debug ;
};

