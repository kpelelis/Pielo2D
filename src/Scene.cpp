#include "Scene.h"

Scene::Scene(std::string name) {
	name_ = name;
}

Scene::~Scene() {

}

void Scene::load() {
	for(auto& go : game_objects_) {
		if(go->is_active()) {
			go->load();
		}
	}	
}

void Scene::on_enter(Scene *previous_scene) {
	// For all objects : object.init
	for(auto& go : game_objects_) {
		if(go->is_active()) {
			go->start();
		}
	}
}

void Scene::update(const double delta_time) {
	// For all objects : object.update
	for(auto& go : game_objects_) {
		if(go->is_active()) {
			go->update(delta_time);
		}
	}
	prune_inactive_objects();
}

void Scene::render(sf::RenderTarget& canvas) {
	// For all objects : If object has renderer
	// object.render
	for(auto& go : game_objects_) {
		if(go->is_active()) {
			go->render(canvas);
		}
	}
}

void Scene::on_exit(Scene *next_scene) {
	// For all objects : object.close
	// delete all objects
	for(auto& go : game_objects_) {
		go->exit();
	}
}

void Scene::prune_inactive_objects() {
	// For each object. If object.active, delete object
}

void Scene::add_game_object(GameObject *go) {
	game_objects_.push_back(go);

}

std::vector<GameObject *> Scene::get_game_objects() {
	return game_objects_;
}

SceneManager *Scene::get_scene_manager() const {
	return scene_manager_;
}

void Scene::set_scene_manager(SceneManager *scene_manager) {
	scene_manager_ = scene_manager;
}

resource_map *Scene::get_resources() {
	resource_map * ret = new resource_map;
	for(auto& go : game_objects_) {
		auto go_resources = go->get_resources();
		ret->insert(go_resources->begin(), go_resources->end());
	}
	return ret;
}
