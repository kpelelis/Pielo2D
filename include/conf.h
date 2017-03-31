#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <cstring>
#include <sstream>
#include <ctime>

#include "utils/Logger.h"

#ifdef USE_DEBUG

#define DEBUG(FROM,...) Logger::get_instance().log(Level::DEBUG, FROM, __VA_ARGS__);
#define INFO(FROM,...) Logger::get_instance().log(Level::INFO, FROM, __VA_ARGS__);
#define WARN(FROM,...) Logger::get_instance().log(Level::WARN, FROM, __VA_ARGS__);
#define ERROR(FROM,...) Logger::get_instance().log(Level::ERROR, FROM, __VA_ARGS__);
#define CRITICAL(FROM,...) Logger::get_instance().log(Level::CRITICAL, FROM, __VA_ARGS__);

#else

#define DEBUG(...) 
#define INFO(...) 
#define WARN(...) 
#define ERROR(...)
#define CRITICAL(...)

#endif

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

enum ResourceType
{
	IMAGE,
	SOUND,
	SCRIPT
};

typedef std::map<std::string, std::pair<ResourceType, std::string>> resource_map;

class InputManager;
class SceneManager;
class ResourceManager;
class ScriptManager;

extern ResourceManager *g_ResourceManager;
extern InputManager *g_InputManager;
extern SceneManager *g_SceneManager;
extern ScriptManager *g_ScriptManager;
