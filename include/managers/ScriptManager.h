#pragma "once"

#include "managers/ResourceManager.h"
#include "LuaBridge/LuaBridge.h"

using namespace luabridge;

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void eval_script(const std::string& script, const std::string& ns);
	typedef void (*binder_fn)(void);
	void bind_function(const std::string ns, const std::string& function_name, binder_fn binder);
	
private:
	void init_lua_env();
	lua_State *L;

};