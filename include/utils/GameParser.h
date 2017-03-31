#pragma once

#include "components/ComponentFactory.h"

#include "components/Script.h"
#include "components/SpriteRenderer.h"
#include "components/CharacterController.h"

#include "Game.h"
#include "Scene.h"
#include "Inputs.h"
#include "pugixml.hpp"

class GameParser
{
public:
	GameParser();
	~GameParser();

	void load_from_file(const std::string& file_name);
	std::map<std::string, Button> get_button_config() { return button_config_; }
	Game *get_game() { return game_; }
	std::vector<Scene *> get_scenes() { return scenes_; }

private:
	typedef std::map<std::string, InputType> InputTypeMap;
	static InputTypeMap input_type_mapping;

	typedef std::map<char, sf::Keyboard::Key> KeyboardKeyMap;
	static  KeyboardKeyMap keyboard_key_mapping;

	struct ComponentFactory *component_factory_;

	Game* game_;
	std::vector<Scene*> scenes_;
	std::map<std::string, Button> button_config_;
	pugi::xml_document game_file_;

	GameObject *parse_game_object(pugi::xml_node go_node);
	Component *parse_component(pugi::xml_node component_node, GameObject *parent);
};