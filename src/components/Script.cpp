#include "components/Script.h"

Script::Script(GameObject *parent, resource_map * resources) : Component(parent, resources) {
	for(auto resource : *resources) {
		if(std::strcmp(resource.second.second.c_str(), "script_file") == 0)
			script_file_ = resource.first;
	}
}

void Script::load() {
	auto script = g_ResourceManager->get_script(script_file_);
	INFO("Script load", "Binding start function")
 //    if(resources_->count("src") < 0) {
 //        return;
 //    }
 //    std::string script_name = (*resources_)["src"];
	// lua_State *L = g_ResourceManager->load_script(script_name);
	// LuaRef table = getGlobal(L, "script");
 //    if (table.isTable()) {
 //        if (table["start"].isFunction()) {
 //        	std::cout << "start found " << std::endl;
 //            lua_start = std::make_unique<LuaRef>(table["start"]);
 //        }
 //        if (table["update"].isFunction()) {
 //        	std::cout << "update found " << std::endl;
 //            lua_update = std::make_unique<LuaRef>(table["update"]);
 //        }
 //        if (table["exit"].isFunction()) {
 //        	std::cout << "exit found " << std::endl;
 //            lua_exit = std::make_unique<LuaRef>(table["exit"]);
 //        }
 //    }
}

Script::~Script() {
	// lua_start.reset();
	// lua_update.reset();
	// lua_exit.reset();
}

void Script::start() {
	// if (lua_start) {
 //        try {
 //            (*lua_start)();
 //        }
 //        catch (LuaException const& e) {
 //            std::cout << "LuaException: " << e.what() << std::endl;
 //        }
 //    }
}

void Script::update(double delta_time) {
	// if (lua_update) {
 //        try {
 //            (*lua_update)(delta_time);
 //        }
 //        catch (LuaException const& e) {
 //            std::cout << "LuaException: " << e.what() << std::endl;
 //        }
 //    }
}

void Script::exit() {
	// if (lua_exit) {
 //        try {
 //            (*lua_exit)();
 //        }
 //        catch (LuaException const& e) {
 //            std::cout << "LuaException: " << e.what() << std::endl;
 //        }
 //    }
}
