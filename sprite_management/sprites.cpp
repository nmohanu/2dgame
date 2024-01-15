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

    // Add inventory texture.
    if (!inventory_texture.loadFromFile("../Assets/Tiles/inventory.png")) {
        // Error handling if the image fails to load
        std::cout << "ERR" << '\n';
    }

    // Add player texture.
    if (!dialogue_texture.loadFromFile("../Assets/Tiles/dialogue_frame.png")) {
        // Error handling if the image fails to load
        std::cout << "ERR" << '\n';
    }

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

    // Dialogue sprites ----------------------------------------------
    dialogue_sprite.setTexture(dialogue_texture);
    dialogue_sprite.setScale(10*TEMP_SCALE, 10*TEMP_SCALE);
    dialogue_sprite.setPosition(0,0);

    // Inventory sprite
    inventory_sprite.setTexture(inventory_texture);
    inventory_sprite.setScale(3, 3);
    inventory_sprite.setPosition(SCREEN_WIDTH/2-(136)*3/2, SCREEN_HEIGHT-64);

    // Player sprite -------------------------------------------------
    player_sprite.setTexture(player_texture);
    player_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_X);
    player_sprite.setPosition(SCREEN_WIDTH/2-(16 * SCALE_FACTOR_X)/2, SCREEN_HEIGHT/2-(16 * SCALE_FACTOR_X)/2);
    player_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

    // NPC Sprites ---------------------------------------------------

    // Old man
    old_man_npc.setTexture(player_texture);
    old_man_npc.setScale(SCALE_FACTOR_X, SCALE_FACTOR_X);
    old_man_npc.setTextureRect(sf::IntRect(96, 0, 16, 16));
    old_man_npc.setPosition(CENTER_X-(16 * SCALE_FACTOR_X)/2 + 16*SCALE_FACTOR_X, CENTER_Y-(16 * SCALE_FACTOR_X)/2);

    
    // Selection square ----------------------------------------------
    selection_sprite.setTexture(selection_texture);
    selection_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);

    // UI sprites ----------------------------------------------------

    // Coin
    coin_sprite.setTexture(UI_texture);
    coin_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_X);
    sf::IntRect coin_rect(0, 0, 16, 16);
    coin_sprite.setTextureRect(coin_rect);

    // Talk icon
    talk_icon_sprite.setTexture(UI_texture);
    talk_icon_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_X);
    sf::IntRect talk_icon_rect(16, 0, 16, 16);
    talk_icon_sprite.setTextureRect(talk_icon_rect);

    //----------------------------------------------------------------

    // Objects
    pumpkin_sprite.setTexture(floor_texture);
    pumpkin_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect pumpkin_rect(32, 0, 16, 16);
    pumpkin_sprite.setTextureRect(pumpkin_rect);

    gate_sprite.setTexture(edges_texture);
    gate_sprite.setTextureRect(sf::IntRect(48, 16, 32, 32));
    gate_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);

    boat_sprite.setTexture(edges_texture);
    boat_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    boat_sprite.setTextureRect(sf::IntRect(48, 16, 16, 32));

    weed_sprite.setTexture(floor_texture);
    weed_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    weed_sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));


    // Edges sprites
    edge_0_sprite.setTexture(edges_texture);
    edge_0_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_0_rect(0, 0, 16, 16);
    edge_0_sprite.setTextureRect(edge_0_rect);
    
    edge_1_sprite.setTexture(edges_texture);
    edge_1_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_1_rect(16, 0, 16, 16);
    edge_1_sprite.setTextureRect(edge_1_rect);

    edge_2_sprite.setTexture(edges_texture);
    edge_2_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_2_rect(32, 0, 16, 16);
    edge_2_sprite.setTextureRect(edge_2_rect);

    edge_3_sprite.setTexture(edges_texture);
    edge_3_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_3_rect(32, 16, 16, 16);
    edge_3_sprite.setTextureRect(edge_3_rect);

    edge_4_sprite.setTexture(edges_texture);
    edge_4_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_4_rect(32, 32, 16, 16);
    edge_4_sprite.setTextureRect(edge_4_rect);

    edge_5_sprite.setTexture(edges_texture);
    edge_5_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_5_rect(16, 32, 16, 16);
    edge_5_sprite.setTextureRect(edge_5_rect);

    edge_6_sprite.setTexture(edges_texture);
    edge_6_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_6_rect(0, 32, 16, 16);
    edge_6_sprite.setTextureRect(edge_6_rect);

    edge_7_sprite.setTexture(edges_texture);
    edge_7_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);
    sf::IntRect edge_7_rect(0, 16, 16, 16);
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
