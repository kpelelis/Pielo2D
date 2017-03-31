#pragma once

#include "components/Component.h"

class ComponentManager
{
public:
	ComponentManager(ComponentManager const&) = delete;
	void operator=(ComponentManager const&) = delete;
	
	void load_all();

	void load_texture(const std::string& filename, const std::string& name);
	lua_State *load_script(const std::string& filename);

	sf::Texture	*get_texture(const std::string& filename);

private:
	ComponentManager() {};
	template<typename T>
	void load_resource(std::map<std::string, T*>& lookup, const std::string& name, const std::string& filename);
	void init_lua_env();

	std::map<std::string, sf::Texture*> textures_;
	std::map<std::string, bool> scripts_;
	lua_State *L;
};