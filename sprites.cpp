#include "sprites.h"
#include <iostream>

Sprite_loader::Sprite_loader()
{
    Sprite_loader::add_sprites();
}

void Sprite_loader::add_sprites()
{
    // Add player sprite.
    if (!player_texture.loadFromFile("../Assets/Characters/player_sprite_sheet.png")) {
        // Error handling if the image fails to load
        std::cout << "ERR" << '\n';
    }
    player_sprite.setTexture(player_texture);
    player_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
    player_sprite.setPosition(SCREEN_WIDTH/2-(16 * SCALE_FACTOR)/2, SCREEN_HEIGHT/2-(16 * SCALE_FACTOR)/2);

    // Add wall sprite.
    if (!wall_texture.loadFromFile("../Assets/Tiles/wall.png")) {
        // Error handling if the image fails to load
        std::cout << "ERR" << '\n';
    }
    wall_sprite.setTexture(wall_texture);
    wall_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);

    // Add floor sprite.
    if (!floor_texture.loadFromFile("../Assets/Tiles/floor.png")) {
        // Error handling if the image fails to load
        std::cout << "ERR" << '\n';
    }
    floor_sprite.setTexture(floor_texture);
    floor_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
}


