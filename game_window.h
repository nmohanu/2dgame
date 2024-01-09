#pragma once
#include <SFML/Audio.hpp>
#include "game_scene.h"

struct game_window
{
    sf::Clock frame_clock;
    sf::Clock delta_clock;
    Game_scene* current_scene = nullptr;
    Game_scene level_1;

    int player_money = 100;
    sf::Text player_money_text;
    sf::Vector2f mouse_position;

    sf::Font font;
    game_window() 
    {
        if (!font.loadFromFile("../Assets/fonts/pixels.ttf")) 
        {
            // handle error if the font fails to load
            std::cout << "ERR\n";
        }

        player_money_text.setFont(font);
        player_money_text.setCharacterSize(100);
        player_money_text.setFillColor(sf::Color::White);
        player_money_text.setPosition(32, 0);
        player_money_text.setScale(0.24, 0.24);
    }


    void open_game_window();
    void game_window_loop(sf::RenderWindow&);
    void game_window_update(sf::RenderWindow&);
    void game_window_draw(sf::RenderWindow&);
};

