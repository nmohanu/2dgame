#pragma once
#include <SFML/Audio.hpp>
#include "game_scene.h"

struct game_window
{
    sf::Clock frame_clock;
    sf::Clock delta_clock;
    Game_scene* current_scene = nullptr;
    Game_scene level_1;


    void open_game_window();
    void game_window_loop(sf::RenderWindow&);
    void game_window_update(sf::RenderWindow&);
    void game_window_draw(sf::RenderWindow&);
};

