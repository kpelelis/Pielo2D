#include "managers/SceneManager.h"

SceneManager* g_SceneManager;

SceneManager::SceneManager(Scene *initial_scene) {
	if(initial_scene == nullptr) { return; }
	INFO("SceneManager constructor", "Starting scene ", initial_scene->get_name())
	DEBUG("SceneManager constructor", "Scene Objects: ")
	std::vector<GameObject *> objs = initial_scene->get_game_objects();
	for(auto go : objs) {
		DEBUG("SceneManager constructor", *go)
	}
	current_scene_ = initial_scene;
	current_scene_->set_scene_manager(this);
	current_scene_->load();
	current_scene_->on_enter(nullptr);
}

SceneManager::~SceneManager() {
	if(next_scene_ != nullptr) {
		next_scene_->on_exit(nullptr);
		delete next_scene_;
	}
	if(current_scene_ != nullptr) {
		current_scene_->on_exit(nullptr);
		delete current_scene_;
	}
}

void SceneManager::update(const double delta_time) {
	current_scene_->update(delta_time);
	if(next_scene_ != nullptr) {
		current_scene_->on_exit(next_scene_);
		next_scene_->on_enter(current_scene_);
		delete current_scene_;
		current_scene_ = next_scene_;
		next_scene_ = nullptr;
	}
}

void SceneManager::set_next_scene(Scene *next_scene) {
	if(next_scene_ != nullptr) { delete next_scene_; }
	next_scene_ = next_scene;
	next_scene_->set_scene_manager(this);
}

void SceneManager::render(sf::RenderTarget& canvas) {
	current_scene_->render(canvas);
}

void SceneManager::quit() {
	current_scene_->on_exit(next_scene_);
	delete current_scene_;
	delete next_scene_;
}
