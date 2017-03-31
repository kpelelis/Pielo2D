#include "components/CharacterController.h"

CharacterController::CharacterController(GameObject *parent, resource_map * resources) : Component(parent, resources) {

}

CharacterController::~CharacterController() {

}

void CharacterController::start() {

}

void CharacterController::update(const double delta_time) {
	float vx = 0.f, vy = 0.f;
	if(g_InputManager->get_button("up")) {
		vy += speed_modifier_;
	}
	if(g_InputManager->get_button("down")) {
		vy -= speed_modifier_;
	}
	if(g_InputManager->get_button("left")) {
		vx -= speed_modifier_;
	}
	if(g_InputManager->get_button("right")) {
		vx += speed_modifier_;
	}
	sf::Vector2f speed (vx, vy);
	sf::Vector2f new_pos = parent_->get_position() + speed ;
	parent_->set_position(new_pos);
}

void CharacterController::exit() {
	
}