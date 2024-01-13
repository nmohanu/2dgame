#pragma once

#include <vector>
#include "../level_management/level.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int CENTER_X = SCREEN_WIDTH/2;
const int CENTER_Y = SCREEN_HEIGHT/2;
const float SCALE_FACTOR_X = 4;
const float SCALE_FACTOR_Y = 3.5;
const float PLAYER_SPEED = 3.f;

struct Sprite_loader
{
    // Player
    sf::Texture player_texture;
    sf::Sprite player_sprite;

    // Old man npc
    sf::Sprite old_man_npc;
    sf::Vector2f original_position_old_man_npc = sf::Vector2f(CENTER_X-(16 * SCALE_FACTOR_X)/2 + 40*SCALE_FACTOR_X, CENTER_Y-(16 * SCALE_FACTOR_X)/2);

    // UI elements
    sf::Texture UI_texture;
    sf::Sprite coin_sprite;
    sf::Sprite talk_icon_sprite;

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
