#pragma once

#include "conf.h"
#include "utils/ScriptResource.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	
	void batch_load(resource_map resources);

	void load_texture(const std::string& filename, const std::string& name);
	void load_script(const std::string& filename);

	sf::Texture	*get_texture(const std::string& filename);
	ScriptResource *get_script(const std::string& script);

private:

	template<typename T>
	void load_resource(std::map<std::string, T*>& lookup, const std::string& name, const std::string& filename);
	void init_lua_env();

	std::map<std::string, sf::Texture*> textures_;
	std::map<std::string, ScriptResource*> scripts_;
};