#pragma once

enum InputType {
	KEYBOARD,
	MOUSE
};

struct Button {
	InputType type;
	
	union {
		sf::Keyboard::Key key;
		sf::Mouse::Button mouse_button;		
	};

	bool operator<(const Button& b)  const {
		if(type != b.type) { return type < b.type; }
	    switch(type) {
	    case InputType::KEYBOARD:
	    	return key < b.key;
	    	break;
	    case InputType::MOUSE:
	    	return mouse_button < b.mouse_button;
	    	break;
	    }
	}
};
