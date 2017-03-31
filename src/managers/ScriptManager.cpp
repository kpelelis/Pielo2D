#include "managers/ScriptManager.h"

ScriptManager * g_ScriptManager;

ScriptManager::ScriptManager() {
	init_lua_env();
}


ScriptManager::~ScriptManager() {

}

void ScriptManager::init_lua_env() {
	L = luaL_newstate();
    luaL_openlibs(L);
	// getGlobalNamespace(L)
	// 	.beginNamespace("InputManager")
	// 		.beginClass<InputManager>("Input")
	// 			.addFunction("get_button_down", &InputManager::get_button_down)
	// 		.endClass()
	// 	.endNamespace();
	// push(L, g_InputManager);
	// lua_setglobal(L, "Input");
}

void ScriptManager::eval_script(const std::string& script, const std::string& ns) {
	if(luaL_dostring(L, script.c_str())) {
		std::cout << "Error while loading script" << std::endl;
		std::cout << lua_tostring(L, -1) << std::endl;
		return;
	}
}

void ScriptManager::bind_function(const std::string ns, const std::string& function_name, binder_fn binder) {

}