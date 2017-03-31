#pragma once

#include "conf.h"

#include "GameObject.h"

class SceneManager;


class Scene {
public:
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	Scene(std::string name);
	// C++ note for future me:
	// virtual functions are meant to be derived
	// the non virtual are uniform
	virtual ~Scene();


	void load();
	
	void on_enter(Scene  *previous_scene);

	void update(const double delta_time);
	void render(sf::RenderTarget& canvas);

	void on_exit(Scene *next_scene);


	void add_game_object(GameObject *go);

	std::vector<GameObject *> get_game_objects();

	void prune_inactive_objects();

	SceneManager *get_scene_manager() const;
	void set_scene_manager(SceneManager *scene_manager);

	std::string get_name() const { return name_; };

	resource_map *get_resources();

private:
	SceneManager* scene_manager_;
	std::vector<GameObject *> game_objects_;
	std::string name_;
};
