#include "utils/GameParser.h"

GameParser::GameParser() {
	component_factory_ = new ComponentFactory();
	component_factory_->register_component<CharacterController>("CharacterController");
	component_factory_->register_component<Script>("Script");
	component_factory_->register_component<SpriteRenderer>("SpriteRenderer");
}

GameParser::~GameParser() {
	delete component_factory_;
};


GameParser::InputTypeMap GameParser::input_type_mapping = []
{
	GameParser::InputTypeMap ret = {
		{"keyboard", InputType::KEYBOARD},
		{"mouse", InputType::MOUSE}		
	};
	return ret;
}();

GameParser::KeyboardKeyMap GameParser::keyboard_key_mapping = []
{
	GameParser::KeyboardKeyMap ret = {	
		{'A', sf::Keyboard::Key::A},
		{'B', sf::Keyboard::Key::B},
		{'C', sf::Keyboard::Key::C},
		{'D', sf::Keyboard::Key::D},
		{'E', sf::Keyboard::Key::E},
		{'F', sf::Keyboard::Key::F},
		{'G', sf::Keyboard::Key::G},
		{'H', sf::Keyboard::Key::H},
		{'I', sf::Keyboard::Key::I},
		{'J', sf::Keyboard::Key::J},
		{'K', sf::Keyboard::Key::K},
		{'L', sf::Keyboard::Key::L},
		{'M', sf::Keyboard::Key::M},
		{'N', sf::Keyboard::Key::N},
		{'O', sf::Keyboard::Key::O},
		{'P', sf::Keyboard::Key::P},
		{'Q', sf::Keyboard::Key::Q},
		{'R', sf::Keyboard::Key::R},
		{'S', sf::Keyboard::Key::S},
		{'T', sf::Keyboard::Key::T},
		{'U', sf::Keyboard::Key::U},
		{'V', sf::Keyboard::Key::V},
		{'W', sf::Keyboard::Key::W},
		{'X', sf::Keyboard::Key::X},
		{'Y', sf::Keyboard::Key::Y},
		{'Z', sf::Keyboard::Key::Z}
	};
	return ret;
}();

void GameParser::load_from_file(const std::string& file_name) {
	std::string error_msg = "Error while parsing game configuration";

	pugi::xml_parse_result result = game_file_.load_file(file_name.c_str());
	if(result) {
		INFO("GameParser", "Game configuration [", file_name, "] opened!")
	} else {
		ERROR("GameParser", "Game configuration [", file_name, "] failed to open!")	
		ERROR("GameParser", "Error: ", result.description())
		return;
	}

	pugi::xml_node game_node = game_file_.child("Game");
	Game *game;
	if(!game_node) {
		ERROR("GameParser", error_msg)
		ERROR("GameParser", "File must contain a Game root node")
		return;
	} else {
		DEBUG("GameParser", "Loading game", game_node.attribute("name").value())
		game_ = new Game();
	}

	pugi::xml_node screen_node = game_node.child("Screen");
	int width = screen_node.child("width").text().as_int(); 
	int height = screen_node.child("height").text().as_int(); 

	pugi::xml_node input_cfg_node = game_node.child("InputConfig");
	for(pugi::xml_node input : input_cfg_node.children("Input")) {
		Button btn;
		auto input_type = input.attribute("type").value();
		if(GameParser::input_type_mapping.count(input_type) > 0) {
			btn.type = GameParser::input_type_mapping[input_type];
		} else {
			WARN("GameParser", "Unknown Input type: ", input_type);
			return;			
		}
		if(std::strcmp(input_type, "keyboard") == 0) {
			auto key = input.attribute("key").value();
			btn.key = GameParser::keyboard_key_mapping[key[0]];
		}
		auto input_name = input.attribute("name").value();
		button_config_[input_name] = btn;
		DEBUG("GameParser", "Added Button: ", input_name);
	}

	for(pugi::xml_node scene_node : game_node.children("Scene")) {
		auto scene_name = scene_node.attribute("name").value();
		Scene *scene = new Scene(scene_name);
		for(pugi::xml_node go_node : scene_node.children("GameObject")) {
			GameObject * new_obj = parse_game_object(go_node);
			scene->add_game_object(new_obj);
		}
		scenes_.push_back(scene);
	}
	DEBUG("GameParser", "Game Succefully loaded");
	return;
}

GameObject *GameParser::parse_game_object(pugi::xml_node go_node) {
	auto go_name = go_node.attribute("name").value();
	GameObject *go = new GameObject(go_name);

	float x = go_node.child("Position").attribute("x").as_float();
	float y = go_node.child("Position").attribute("y").as_float();
	go->set_position(x, y);
	for(pugi::xml_node component : go_node.child("Components")) {
		Component * comp = parse_component(component, go);
		go->add_component(comp);
	}
	return go;
}

Component * GameParser::parse_component(pugi::xml_node component_node, GameObject *parent) {
	auto comp_name = component_node.name();
	resource_map *resources = new resource_map();
	for(pugi::xml_node resource : component_node.children("Resource")) {	
		auto resource_type_str = resource.attribute("type").value();
		auto resource_name = resource.attribute("name").value();
		auto resource_value = resource.attribute("src").value();
		ResourceType res_type;
		if(std::strcmp(resource_type_str, "image") == 0)
			res_type = ResourceType::IMAGE;
		else if(std::strcmp(resource_type_str, "script") == 0)
			res_type = ResourceType::SCRIPT;

		resources->insert(std::make_pair(resource_value, std::make_pair(res_type, resource_name)));
	}
	return component_factory_->create_instance(comp_name, parent, resources);
}
