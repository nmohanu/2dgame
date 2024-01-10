#pragma once
#include "sprites.h"
#include "level.h"
#include <iostream>

struct Game_scene
{   
    int tick = 0;
    int frame_offset = 0;
    const int CHANGE_FRAME = 180;
    Level* level_1 = new Level(8, 8, 1);
    Level* current_level = nullptr;
    Sprite_loader sprite_loader;
    void render_objects(sf::RenderWindow& window);
    void update_sprites(sf::Clock& timer, sf::RenderWindow& window, float deltaTimeSeconds);
    void draw_level(sf::RenderWindow& window, sf::Vector2f mouse_position);
    void move_player(float deltaTimeSeconds);
    bool check_collision();
    void change_sprite_bounds(sf::Clock& timer);
    sf::Vector2f get_velocity(float deltaTimeSeconds);
    void draw_level_objects(sf::Vector2f& position, int x, int y, sf::RenderWindow& window, sf::Vector2f mouse_position);
};
