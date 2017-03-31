#pragma once

#include "conf.h"

class Scene;
class Component;

class GameObject {
public:
	GameObject(const GameObject& go);
	GameObject& operator=(const GameObject& go);

	GameObject(std::string name);
	~GameObject();

	void load();

	void start();

	void update(const double delta_time);
	
	void render(sf::RenderTarget& canvas);

	void exit();

	void add_component(Component *component);

	bool is_active() const { return active_; };

	std::vector<Component *> get_components();
	
	std::string get_name() const { return name_; };
	void set_name(const std::string name) { name_ = name; };

	sf::Vector2f get_position() const { return position_; };
	void set_position(const sf::Vector2f new_pos) { position_ = new_pos; };
	void set_position(float x, float y) { position_ = sf::Vector2f(x, y); };

	sf::Vector2f get_scale() const { return size_; };
	void set_scale(const sf::Vector2f new_scale) { size_ = new_scale; };

	float get_angle() const { return angle_; };	
	void set_angle(const float new_angle) { angle_ = new_angle; }

	void on_mouse_enter();
	void on_mouse_exit();
	void on_mouse_click(sf::Mouse::Button btn);

	friend std::ostream& operator<<(std::ostream& os, const GameObject& go);

	resource_map *get_resources();

protected:
	std::vector<Component *> components_;
	
	std::string name_;
	
	sf::Vector2f position_;
	sf::Vector2f size_;
	float angle_;

	bool active_;

	Scene *parent_scene;
};
