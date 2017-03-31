#include "managers/ResourceManager.h"
#include "managers/InputManager.h"

ResourceManager *g_ResourceManager;


ResourceManager::ResourceManager() {
    
}

ResourceManager::~ResourceManager() {

}


void ResourceManager::load_script(const std::string& filename) {
	load_resource<ScriptResource>(scripts_, filename, filename);
}
	
void ResourceManager::load_texture(const std::string& filename, const std::string& name) {
	load_resource<sf::Texture>(textures_, name, filename);
}

template<typename T> void ResourceManager::load_resource(std::map<std::string, T*>& lookup, const std::string& name, const std::string& filename) {	
	if(filename.empty()) { return; }

	//If we have already loaded the resource
	if(lookup.count(name) > 0) { return; }

	T *res = new T();
	if(res->loadFromFile(filename)) {
		INFO("ResourceManager load_resource", "Loaded Resource ", filename)
		lookup[filename] = res;
	}
}

void ResourceManager::batch_load(resource_map resources) {
	for(auto resource : resources) {
		switch(resource.second.first) {
		case(ResourceType::IMAGE):
			load_texture(resource.first, resource.first);
			break;
		case(ResourceType::SCRIPT):
			load_script(resource.first);
			break;			
		}
	}
}

sf::Texture	*ResourceManager::get_texture(const std::string& name) {
	const auto& txt = textures_.find(name);
	if(txt != textures_.end()) {
		return txt->second;
	} 
	ERROR("ResourceManager get_texture", "Texture ", name, " not found")
	return nullptr;
}

ScriptResource	*ResourceManager::get_script(const std::string& name) {
	const auto& txt = scripts_.find(name);
	if(txt != scripts_.end()) {
		return txt->second;
	} 
	ERROR("ResourceManager get_script", "Script ", name, " not found")
	return nullptr;
}

