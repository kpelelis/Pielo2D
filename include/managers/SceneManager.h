#pragma once

#include "conf.h"
#include "Scene.h"

class SceneManager {
public:
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	SceneManager(Scene *initial_scene);
	~SceneManager();

	void update(const double delta_time);
	void render(sf::RenderTarget& canvas);
	void set_next_scene(Scene *next_scene);
	void quit();

private:
	// Should we use a linked data structure?
	// Will it add too much overhead?
	Scene *current_scene_ = nullptr;
	Scene *next_scene_ = nullptr;
};
