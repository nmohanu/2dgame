#pragma once
#include "../level_management/level.h"
#include "../sprite_management/sprite_animation_manager.h"

#include <iostream>

struct Renderer
{   
    Animation_manager animation_manager;
    Level* level_1 = new Level(8, 8, 1);
    Level* current_level = nullptr;
    
    void render_objects(sf::RenderWindow& window);
    void draw_level(sf::RenderWindow& window, sf::Vector2f mouse_position);
    void move_player(float deltaTimeSeconds);
    bool check_collision();
    sf::Vector2f get_velocity(float deltaTimeSeconds);
    void draw_level_objects(sf::Vector2f& position, int x, int y, sf::RenderWindow& window, sf::Vector2f mouse_position);
};
