#pragma once
#include "Utils.h"
#include "Level.h"
#include "Box2d\Box2d.h"
#include "Player.h"
#include "DebugRenderer.h"
#include "DrawingSystem.h"
#include <iostream>
#include "Enemy.h"




class Game
{
public:
	static Game* getInstance() { static Game instance; return& instance; }
	void GameLoop();
	void ShutDown();

	SDL_FRect* getCamera() { return &camera; }
	SDL_Renderer* getRenderer() { return renderer; }
	SDL_Window* getWindow() { return window; }

private:
	bool init();
	Game() { init(); }
	void handleInput();
	void update();
	void draw();
	bool isRunning = true;
	SDL_Window* window;
	SDL_Renderer* renderer = nullptr, *debugRen = nullptr;
	Level* level = nullptr;
	b2World* world = nullptr;
	Player player;
	DebugRenderer* debug;
	std::shared_ptr<DrawingSystem> drawingSystem;
	SDL_FRect camera;
};

