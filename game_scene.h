#pragma once
#include "sprites.h"
#include "level.h"
#include <iostream>

struct Game_scene
{
    Level* level_1 = new Level(8, 8, 1);
    Level* current_level = nullptr;
    Sprite_loader sprite_loader;
    void render_objects(sf::RenderWindow& window);
    void update_sprites(sf::Clock& timer, sf::RenderWindow& window);
    void draw_level(sf::RenderWindow& window);
    void move_player(float deltaTimeSeconds);
    bool check_collision();
    sf::Vector2f get_velocity(float deltaTimeSeconds);
};
