#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

const int SCREEN_WIDTH = 1920/2;
const int SCREEN_HEIGHT = 1080/2;
const float SCALE_FACTOR_X = 2;
const float SCALE_FACTOR_Y = 1.75;
const float PLAYER_SPEED = 2.f;

struct Sprite_loader
{
    // Player
    sf::Texture player_texture;
    sf::Sprite player_sprite;

    //UI elements
    sf::Texture UI_texture;
    sf::Sprite coin_sprite;

    // Floor tiles
    sf::Texture floor_texture;
    sf::Sprite floor_sprite;
    sf::Sprite floor2_sprite;

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
