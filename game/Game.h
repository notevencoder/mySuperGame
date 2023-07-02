#pragma once
#include "Utils.h"
#include "Level.h"
#include "Box2d\Box2d.h"
#include "Player.h"
#include "DebugRenderer.h"
#include "DrawingSystem.h"
#include <iostream>

class Game
{
public:
	static Game* getInstance() { static Game instance; return& instance; }
	void GameLoop();
	void ShutDown();

	SDL_FRect* getCamera() { return &camera; }
private:
	bool init();
	Game() { init(); }
	void handleInput();
	void update();
	void draw();
	bool isRunning = true;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr, *debugRen = nullptr;
	Level* level = nullptr;
	Sprite* sprite;
	b2World* world = nullptr;
	Player player;
	DebugRenderer* debug;
	std::shared_ptr<DrawingSystem> drawingSystem;
	SDL_FRect camera;
};

