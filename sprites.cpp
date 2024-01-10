#include "sprites.h"
#include <iostream>

Sprite_loader::Sprite_loader()
{
    Sprite_loader::add_sprites();
}

void Sprite_loader::add_sprites()
{
    // Add player texture.
    if (!player_texture.loadFromFile("../Assets/Characters/player_sprite_sheet.png")) {
        // Error handling if the image fails to load
        std::cout << "ERR" << '\n';
    }
    player_sprite.setTexture(player_texture);
    player_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_X);
    player_sprite.setPosition(SCREEN_WIDTH/2-(16 * SCALE_FACTOR_X)/2, SCREEN_HEIGHT/2-(16 * SCALE_FACTOR_X)/2);

    // Add floor texture.
    if (!floor_texture.loadFromFile("../Assets/Tiles/tile_sheet.png")) {
        // Error handling if the image fails to load
        std::cout << "ERR" << '\n';
    }

    // Add edges texture.
    if (!UI_texture.loadFromFile("../Assets/Tiles/UI_elements.png")) {
        // Error handling if the image fails to load
        std::cout << "ERR" << '\n';
    }

    // Add UI texture.
    if (!edges_texture.loadFromFile("../Assets/Tiles/edges.png")) {
        // Error handling if the image fails to load
        std::cout << "ERR" << '\n';
    }

    // Add UI texture.
    if (!selection_texture.loadFromFile("../Assets/Tiles/selection.png")) {
        // Error handling if the image fails to load
        std::cout << "ERR" << '\n';
    }

    // Selection square
    selection_sprite.setTexture(selection_texture);
    selection_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);

    // UI sprites
    coin_sprite.setTexture(UI_texture);
    coin_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_X);
    sf::IntRect coin_rect(0, 0, 16, 16);
    edge_0_sprite.setTextureRect(coin_rect);

    // Objects
    pumpkin_sprite.setTexture(floor_texture);
    pumpkin_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect pumpkin_rect(32, 0, 16, 16);
    pumpkin_sprite.setTextureRect(pumpkin_rect);

    // Edges sprites
    edge_0_sprite.setTexture(edges_texture);
    edge_0_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_0_rect(0, 0, 16, 16);
    edge_0_sprite.setTextureRect(edge_0_rect);
    
    edge_1_sprite.setTexture(edges_texture);
    edge_1_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_1_rect(0, 16, 16, 16);
    edge_1_sprite.setTextureRect(edge_1_rect);

    edge_2_sprite.setTexture(edges_texture);
    edge_2_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_2_rect(0, 32, 16, 16);
    edge_2_sprite.setTextureRect(edge_2_rect);

    edge_3_sprite.setTexture(edges_texture);
    edge_3_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_3_rect(16, 32, 16, 16);
    edge_3_sprite.setTextureRect(edge_3_rect);

    edge_4_sprite.setTexture(edges_texture);
    edge_4_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_4_rect(32, 32, 16, 16);
    edge_4_sprite.setTextureRect(edge_4_rect);

    edge_5_sprite.setTexture(edges_texture);
    edge_5_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_5_rect(32, 16, 16, 16);
    edge_5_sprite.setTextureRect(edge_5_rect);

    edge_6_sprite.setTexture(edges_texture);
    edge_6_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_6_rect(32, 0, 16, 16);
    edge_6_sprite.setTextureRect(edge_6_rect);

    edge_7_sprite.setTexture(edges_texture);
    edge_7_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_7_rect(16, 0, 16, 16);
    edge_7_sprite.setTextureRect(edge_7_rect);

    // Floor 1 sprite
    floor_sprite.setTexture(floor_texture);
    floor_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect floor_rect(0, 0, 16, 16);
    floor_sprite.setTextureRect(floor_rect);

    // Floor 2 sprite
    floor2_sprite.setTexture(floor_texture);
    floor2_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect floor2_rect(16, 0, 16, 16);
    floor2_sprite.setTextureRect(floor2_rect);  
}
