#pragma once

#include "conf.h"
#include "GameObject.h"

class Component {

public:
	Component(GameObject *parent, resource_map *resources);
	
	virtual ~Component() { 
		delete parent_;
		delete resources_;
	}

	virtual void load() {};

	virtual void start() {};;

	virtual void update(const double delta_time) {};;

	virtual void render(sf::RenderTarget& canvas) {};;

	virtual void exit() {};;

	virtual void on_mouse_enter() {};;
	virtual void on_mouse_exit() {};;
	virtual void on_mouse_click(sf::Mouse::Button btn) {};;

	resource_map * get_resources() { return resources_; }	

protected:
	GameObject *parent_ = nullptr;
	resource_map *resources_;
};
