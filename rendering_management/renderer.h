#pragma once

#include "../mechanics_management/mechanics.h"

#include <iostream>




struct Renderer
{   
    Animation_manager animation_manager;
    Level* level_1 = new Level(8, 8, 1);
    Level* current_level = nullptr;
    
    void player_movement(float deltaTimeSeconds, Sprite_loader& sprite_loader);
    void render_everything(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Inventory& player_inventory);
    void render_mouse_icon(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Inventory& player_inventory);
    void render_npc(sf::RenderWindow& window, Sprite_loader& sprite_loader);
    void render_objects(sf::RenderWindow& window, Sprite_loader& sprite_loader);
    void draw_level_tiles(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader);
    void draw_level_objects(sf::RenderWindow& window, Sprite_loader& sprite_loader, int x, int y, sf::Vector2f position);
    void draw_player_hotbar(sf::RenderWindow& window, Sprite_loader& sprite_loader, Inventory& player_inventory);

    std::vector<sf::Sprite> collision_sprites;
    std::vector<sf::Sprite> npc_sprites;
    std::vector<sf::Sprite> clickable_sprites;
    std::vector<sf::Sprite> render_tiles;
    std::vector<sf::Sprite> render_object_sprites;
    std::vector<sf::Sprite> render_tile_sprites;

    

};

