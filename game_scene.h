#pragma once
#include "sprites.h"
#include "level.h"


struct Game_scene
{
    Level level_loader;
    Sprite_loader sprite_loader;
    void render_objects(sf::RenderWindow& window);
    void update_sprites(sf::Clock& timer, sf::RenderWindow& window);
    void draw_level(sf::RenderWindow& window);
    void move_player(float deltaTimeSeconds);
    bool check_collision();
};
