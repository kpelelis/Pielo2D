#pragma once

#include "conf.h"
#include "utils/Inputs.h"

enum ButtonState {
	IDLE = 1,
	PRESSING,
	PRESSED,
	RELEASING,
};


enum EventType {
	KEY_DOWN,
	KEY_UP
};


struct InputEvent {
	EventType type;
	Button btn;
};

class InputManager {
public:
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	InputManager(std::map<std::string, Button> config);
	InputManager();
	~InputManager();

	void set_config(std::map<std::string, Button> config);

	void key_pressed(Button key);
	void key_released(Button key); 

	bool get_button(std::string key);
	bool get_button_down(std::string key);
	bool get_button_up(std::string key);

	void update();


private:
	std::map<std::string, Button> configuration_;
	std::map<Button, bool> pressed_buttons_;

	std::map<Button, ButtonState> button_states_;
};

