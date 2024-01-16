#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
//#include "../level_management/level.h"

// Temporary scale stuff, for development.
const float TEMP_SCALE = 0.8;

// Screen width.
const int SCREEN_WIDTH = 1920*TEMP_SCALE;

// Screen height.
const int SCREEN_HEIGHT = 1080*TEMP_SCALE;

// Center of screen X.
const int CENTER_X = SCREEN_WIDTH/2;

// Center of screen Y.
const int CENTER_Y = SCREEN_HEIGHT/2;

// Scale factor, y is smaller for '3d-ish effect'
const float SCALE_FACTOR_X = 4;
const float SCALE_FACTOR_Y = 3.5;

// Player movement speed.
const float PLAYER_SPEED = 3.f;

// Time period after which the world updates.
const float UPDATE_TIME_AFTER = 5.0f;

const float PLAYER_REACH = 80.f;

struct Sprite_loader
{
    // Where the mouse is positioned on the grid.
    int mouse_pos_x;
    int mouse_pos_y;

    // Inventory
    sf::Texture inventory_texture;
    sf::Sprite inventory_sprite;

    // Player
    sf::Texture player_texture;
    sf::Sprite player_sprite;

    sf::IntRect* player_reach_rect = new sf::IntRect(CENTER_X - PLAYER_REACH, CENTER_Y- PLAYER_REACH, PLAYER_REACH*2, PLAYER_REACH*2);

    // Old man npc
    sf::Sprite old_man_npc;
    sf::Vector2f original_position_old_man_npc = sf::Vector2f(CENTER_X-(16 * SCALE_FACTOR_X)/2 + 24*SCALE_FACTOR_X, CENTER_Y-(16 * SCALE_FACTOR_X)/2);

    // UI elements
    sf::Texture UI_texture;
    sf::Sprite coin_sprite;

    // Mouse sprites (using UI texture)
    sf::Sprite talk_icon_sprite;
    sf::Sprite grab_icon_sprite;
    sf::Sprite default_mouse_icon_sprite;

    // Dialogue sprites
    sf::Texture dialogue_texture;
    sf::Sprite dialogue_sprite;

    // Selection square
    sf::Texture selection_texture;
    sf::Sprite selection_sprite;

    // Floor tiles
    sf::Texture floor_texture;
    sf::Sprite floor_sprite;
    sf::Sprite floor2_sprite;

    // Objects
    sf::Sprite pumpkin_sprite;
    sf::Sprite boat_sprite;
    sf::Sprite weed_sprite;
    sf::Sprite gate_sprite;

    // Edges tiles.
    sf::Texture edges_texture;
    sf::Sprite edge_0_sprite;
    sf::Sprite edge_1_sprite;
    sf::Sprite edge_2_sprite;
    sf::Sprite edge_3_sprite;
    sf::Sprite edge_4_sprite;
    sf::Sprite edge_5_sprite;
    sf::Sprite edge_6_sprite;
    sf::Sprite edge_7_sprite;

    Sprite_loader();
    void add_sprites();
};
