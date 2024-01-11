#pragma once

#include "../mechanics_management/mechanics.h"

#include <iostream>



struct Renderer
{   
    Animation_manager animation_manager;
    Level* level_1 = new Level(8, 8, 1);
    Level* current_level = nullptr;
    
    void player_movement(float deltaTimeSeconds, Sprite_loader& sprite_loader);
    void render_everything(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader);
    void handle_clicks(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader);
    void render_mouse_icon(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader);
    void render_npc(sf::RenderWindow& window, Sprite_loader& sprite_loader);
    void render_objects(sf::RenderWindow& window, Sprite_loader& sprite_loader);
    void draw_level_tiles(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader);
    void draw_level_objects(sf::Vector2f& position, int x, int y, sf::RenderWindow& window, sf::Vector2f mouse_position);
};
