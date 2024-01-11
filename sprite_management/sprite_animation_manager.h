#pragma once
#include <SFML/Graphics.hpp>
#include "sprites.h"

struct Animation_manager{
    bool blink;
    bool yawn;
    sf::Clock idle_animation_timer;
    sf::Clock idle_animation2_timer;
    int animation_frame_counter = 0;
    int tick = 0;
    int frame_offset = 0;
    int last_frame_offset = 0;
    const int CHANGE_FRAME = 180;
    Sprite_loader sprite_loader;
    void update_sprites(sf::Clock& timer, sf::RenderWindow& window, float deltaTimeSeconds);
    void change_sprite_bounds(sf::Clock& timer);
};
