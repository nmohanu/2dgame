#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>

// General data.
const int SCREEN_WIDTH = 1920/2;
const int SCREEN_HEIGHT = 1080/2;
const int SCALE_FACTOR = 2;
const float PLAYER_SPEED = 2.f;

struct Sprite_loader
{
    sf::Texture player_texture;
    sf::Sprite player_sprite;

    sf::Texture wall_texture;
    sf::Sprite wall_sprite;

    sf::Texture floor_texture;
    sf::Sprite floor_sprite;

    Sprite_loader();
    void add_sprites();
};
