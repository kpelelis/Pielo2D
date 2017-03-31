#include "Game.h"
#include "utils/GameParser.h"

int main()
{
    GameParser *g_GameParser = new GameParser();
    g_GameParser->load_from_file("../my_game.pielo");

    auto input_config = g_GameParser->get_button_config();
    g_ScriptManager = new ScriptManager();
    g_InputManager = new InputManager();
    g_InputManager->set_config(input_config); 
    g_ResourceManager = new ResourceManager();

    Game * game = g_GameParser->get_game();

    auto scene = g_GameParser->get_scenes().back();
    auto resources = scene->get_resources();
    g_ResourceManager->batch_load(*resources);
    g_SceneManager = new SceneManager(scene);

    game->run();
    
    delete g_ScriptManager;
    delete g_ResourceManager;
    delete g_SceneManager;
    delete g_InputManager;

    return 0;
}
