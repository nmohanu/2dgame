#pragma once
#include <SFML/Audio.hpp>
#include "../rendering_management/renderer.h"

struct game_window
{
    Dialogue_manager* dialogue_manager = new Dialogue_manager;
    
    sf::Clock frame_clock;
    sf::Clock delta_clock;
    Renderer* current_scene = nullptr;
    Renderer level_1;

    int player_money = 100;
    sf::Text player_money_text;
    sf::Vector2f mouse_position;
    Sprite_loader sprite_loader;

    sf::SoundBuffer ladybug_buffer;
    sf::Sound ladybug;


    sf::Font font;

    game_window() 
    {
        if (!font.loadFromFile("../Assets/fonts/pixels.ttf")) 
        {
            // handle error if the font fails to load
            std::cout << "ERR\n";
        }
        

        if (!ladybug_buffer.loadFromFile("../Assets/music/blossoms.wav")) 
        {
            std::cout << "Failed to load audio file." << std::endl;
        }
        ladybug.setBuffer(ladybug_buffer);

        player_money_text.setFont(font);
        player_money_text.setCharacterSize(100);
        player_money_text.setFillColor(sf::Color::White);
        player_money_text.setPosition(64, 0);
        player_money_text.setScale(0.48, 0.48);

        dialogue_manager->message.setFont(font);
        dialogue_manager->message.setCharacterSize(100*TEMP_SCALE);
        dialogue_manager->message.setFillColor(sf::Color::White);
        dialogue_manager->message.setPosition(990*TEMP_SCALE, 750*TEMP_SCALE);
        dialogue_manager->message.setScale(0.48, 0.48);
    }


    void open_game_window();
    void game_window_loop(sf::RenderWindow&);
    void game_window_update(sf::RenderWindow&);
    void game_window_draw(sf::RenderWindow&);
};

