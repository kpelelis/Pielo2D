#include "managers/InputManager.h"

InputManager *g_InputManager;

std::ostream& operator << (std::ostream &o, const Button b)
{
	switch(b.type) {
	case InputType::KEYBOARD:
		return o << "Keyboard_" << b.key;
		break;
	case InputType::MOUSE:
		return o << "Mouse_" << b.mouse_button;
		break;
	}
}

InputManager::InputManager() {

}

InputManager::~InputManager() {
	
}

void InputManager::set_config(std::map<std::string, Button> config) {
	Button a = {InputType::KEYBOARD, {sf::Keyboard::Key::W}};
	Button b = {InputType::KEYBOARD, {sf::Keyboard::Key::W}};

	INFO("InputManager set_config", "Setting new keyboard confing")
	configuration_ = config;
	for(auto itt : configuration_) {
		button_states_[itt.second] = ButtonState::IDLE;
		pressed_buttons_[itt.second] = false;
		DEBUG("InputManager set_config", itt.first, ": ", itt.second)
	}
}

void InputManager::key_pressed(Button btn) {
	if(!button_states_[btn]) { return; }
	pressed_buttons_[btn] = true;
}
 	
void InputManager::key_released(Button btn) {
	if(!button_states_[btn]) { return; }	
	pressed_buttons_[btn] = false;
}

void InputManager::update() {
	for(auto itt : pressed_buttons_) {
		/* If pressed */
		if(itt.second) {
			switch(button_states_[itt.first]) {
			case ButtonState::IDLE:
				button_states_[itt.first] = ButtonState::PRESSING;
				break;
			case ButtonState::PRESSING:
				button_states_[itt.first] = ButtonState::PRESSED;
				break;
			case ButtonState::RELEASING:
				button_states_[itt.first] = ButtonState::IDLE;
				break;
			case ButtonState::PRESSED:
				break;
			}
		}
		/* If it is released */
		else {
			switch(button_states_[itt.first]) {
			case ButtonState::PRESSED:
				button_states_[itt.first] = ButtonState::RELEASING;
				break;
			case ButtonState::PRESSING:
				button_states_[itt.first] = ButtonState::PRESSED;
				break;
			case ButtonState::RELEASING:
				button_states_[itt.first] = ButtonState::IDLE;
				break;
			case ButtonState::IDLE:
				break;
			}
		}

	}
}

bool InputManager::get_button(std::string key) {
	// Should we raise an exception?
	if(configuration_.count(key) == 0) { return false; }
	ButtonState state = button_states_[configuration_[key]];
	return state != ButtonState::IDLE; 
}

bool InputManager::get_button_down(std::string key) {
	// Should we raise an exception?
	if(configuration_.count(key) == 0) { return false; }
	ButtonState state = button_states_[configuration_[key]];
	return state == ButtonState::PRESSING; 
}

bool InputManager::get_button_up(std::string key) {
	// Should we raise an exception?
	if(configuration_.count(key) == 0) { return false; }
	ButtonState state = button_states_[configuration_[key]];
	return state == ButtonState::RELEASING; 
}


