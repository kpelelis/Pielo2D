#pragma once

#include <LuaBridge/LuaBridge.h>

#include "conf.h"
#include "components/Component.h"
#include "managers/ResourceManager.h"
#include "managers/ScriptManager.h"


using namespace luabridge;

class Script : public Component {
public:
	Script(GameObject *parent, resource_map *resources);
	~Script();

	void load() override;

	void start() override;
	void update(const double delta_time) override;
	void exit() override;
private:
	std::string script_file_;
	
	typedef void (*callback_fn)();
	callback_fn script_start_;
	// std::unique_ptr<luabridge::LuaRef> lua_update;
	// std::unique_ptr<luabridge::LuaRef> lua_exit;
};