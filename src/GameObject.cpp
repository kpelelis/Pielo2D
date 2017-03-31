#include "GameObject.h"
#include "components/Component.h"

GameObject::GameObject(std::string name) {
	name_ = name;
	active_ = true;
}

GameObject::~GameObject() {

}

void GameObject::load() {
	for(auto& component : components_) {
		component->load();
	}	
}

void GameObject::start() {
	for(auto& component : components_) {
		component->start();
	}
}

void GameObject::update(const double delta_time) {
	for(auto& component : components_) {
		component->update(delta_time);
	}
}

void GameObject::exit() {
	for(auto& component : components_) {
		component->exit();
	}
}

void GameObject::render(sf::RenderTarget& canvas) {
	for(auto& component : components_) {
		component->render(canvas);
	}
}

void GameObject::add_component(Component *component) {
	if(component == nullptr) { return; }
	components_.push_back(component);
}

std::ostream& operator<<(std::ostream& os, const GameObject& go) {
	os << "[Game Object] " << go.name_;
}

resource_map *GameObject::get_resources() {
	resource_map * ret = new resource_map;
	for(auto& component : components_) {
		auto component_resources = component->get_resources();
		ret->insert(component_resources->begin(), component_resources->end());
	}
	return ret;
}

