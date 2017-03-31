#pragma once

#include "managers/InputManager.h"
#include "managers/SceneManager.h"
#include "managers/ResourceManager.h"

#include "conf.h"

class Game {
public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	Game();
	~Game();

	void run();
private:
	sf::RenderTexture main_texture_;
	sf::Sprite canvas_;
	sf::RenderWindow window_;
};
