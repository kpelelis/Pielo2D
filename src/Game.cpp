#include "Game.h"

Game::Game() {
    main_texture_.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    canvas_.setTexture(main_texture_.getTexture());
    window_.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Interesting window title");
}

Game::~Game() {

}

void Game::run() {
    sf::Clock frame_clock;
    sf::Time frame_time;
    frame_time = frame_clock.restart();

    while (window_.isOpen())
    {
        sf::Event ev;
        sf::Time delta_time;
        
        // Update Input
        g_InputManager->update();
        
        delta_time = frame_clock.restart();        
        while (window_.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) {
                window_.close();
            }
            else if (ev.type == sf::Event::KeyPressed) {
                g_InputManager->key_pressed({InputType::KEYBOARD, {ev.key.code}});
            }
            else if (ev.type == sf::Event::KeyReleased) {
                g_InputManager->key_released({InputType::KEYBOARD, {ev.key.code}});
            }
            else if(ev.type == sf::Event::MouseButtonPressed) {
                Button btn = {InputType::MOUSE, {.mouse_button=ev.mouseButton.button}};
                g_InputManager->key_pressed(btn);
            }
            else if(ev.type == sf::Event::MouseButtonReleased) {
                Button btn = {InputType::MOUSE, {.mouse_button=ev.mouseButton.button}};
                g_InputManager->key_released(btn);
            }
        }

        // Calculate delta time of frame
        frame_clock.restart();
        if (delta_time.asMilliseconds() > 50) {
            frame_time = sf::milliseconds(50);
        } else {
            frame_time = delta_time;
        }

        // Scene Update Based on the delta time
        float fps = 1.f / (frame_time.asMicroseconds() * 0.000001);
        if(fps < 100.f)
            std::cout << "FPS: " << fps << '\r' << std::flush;  
        double dt = (double) (frame_time.asMicroseconds() * 0.000001);
        g_SceneManager->update(dt);
        
        window_.clear();
        main_texture_.clear();

        // Render Everything
        g_SceneManager->render(main_texture_);

        window_.draw(canvas_);
        window_.display();
    }
}

