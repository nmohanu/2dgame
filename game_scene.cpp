#include "game_scene.h"
#include "level.h"
#include <iostream>

const int TILE_SIZE = 16;


// Save all sprites for which collision should be checked.
std::vector<sf::Sprite> collision_sprites;
sf::Vector2f world_offset(0.f, 0.f);
sf::Vector2f new_world_position(0.f, 0.f);
sf::Vector2f original_world_positio(0.f, 0.f);
sf::Vector2f original_world_position(world_offset);

// Render objects that are not tiles.
void Game_scene::render_objects(sf::RenderWindow& window)
{
    window.draw(sprite_loader.player_sprite);
}

// This is where the tiles are drawn.
void Game_scene::draw_level(sf::RenderWindow& window, sf::Vector2f mouse_position)
{
    for (int y = 0; y < current_level->LEVEL_HEIGHT; y++)
    {
        for (int x = 0; x < current_level->LEVEL_WIDTH; x++)
        {
            sf::Vector2f position(x * SCALE_FACTOR_X * TILE_SIZE + (SCREEN_WIDTH  - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR_X))/2 + current_level->LEVEL_WIDTH*SCALE_FACTOR_X*TILE_SIZE/2,
                                  y * SCALE_FACTOR_Y * TILE_SIZE + (SCREEN_HEIGHT - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR_Y))/2 + current_level->LEVEL_HEIGHT*SCALE_FACTOR_Y*TILE_SIZE/2);
            position += world_offset;
            if (current_level->level_1_terrain[x][y] == '0')
            {
                sprite_loader.edge_0_sprite.setPosition(position);
                window.draw(sprite_loader.edge_0_sprite);
                
                collision_sprites.push_back(sprite_loader.edge_0_sprite);
            } // Edge 0
            else if (current_level->level_1_terrain[x][y] == '1')
            {
                sprite_loader.edge_1_sprite.setPosition(position);
                window.draw(sprite_loader.edge_1_sprite);

                collision_sprites.push_back(sprite_loader.edge_1_sprite);
            } // Edge 1
            else if (current_level->level_1_terrain[x][y] == '2')
            {
                sprite_loader.edge_2_sprite.setPosition(position);
                window.draw(sprite_loader.edge_2_sprite);

                collision_sprites.push_back(sprite_loader.edge_2_sprite);
            } // Edge 2
            else if (current_level->level_1_terrain[x][y] == '3')
            {
                sprite_loader.edge_3_sprite.setPosition(position);
                window.draw(sprite_loader.edge_3_sprite);

                collision_sprites.push_back(sprite_loader.edge_3_sprite);
            } // Edge 3
            else if (current_level->level_1_terrain[x][y] == '4')
            {
                sprite_loader.edge_4_sprite.setPosition(position);
                window.draw(sprite_loader.edge_4_sprite);

                collision_sprites.push_back(sprite_loader.edge_4_sprite);
            } // Edge 4
            else if (current_level->level_1_terrain[x][y] == '5')
            {
                sprite_loader.edge_5_sprite.setPosition(position);
                window.draw(sprite_loader.edge_5_sprite);

                collision_sprites.push_back(sprite_loader.edge_5_sprite);
            } // Edge 5
            else if (current_level->level_1_terrain[x][y] == '6')
            {
                sprite_loader.edge_6_sprite.setPosition(position);
                window.draw(sprite_loader.edge_6_sprite);

                collision_sprites.push_back(sprite_loader.edge_6_sprite);
            } // Edge 6
            else if (current_level->level_1_terrain[x][y] == '7')
            {
                sprite_loader.edge_7_sprite.setPosition(position);
                window.draw(sprite_loader.edge_7_sprite);

                collision_sprites.push_back(sprite_loader.edge_7_sprite);
            } // Edge 7
            
            else if (level_1->level_1_terrain[x][y] == 'F')
            {
                sprite_loader.floor_sprite.setPosition(position);
                window.draw(sprite_loader.floor_sprite);

                sf::FloatRect sprite = sprite_loader.floor_sprite.getGlobalBounds();
                if(sprite.contains(mouse_position))
                {
                    sprite_loader.selection_sprite.setPosition(position);
                    window.draw(sprite_loader.selection_sprite);
                }
            } // Floor 1 
            else if (level_1->level_1_terrain[x][y] == 'L')
            {
                sprite_loader.floor2_sprite.setPosition(position);
                window.draw(sprite_loader.floor2_sprite);

                sf::FloatRect sprite = sprite_loader.floor2_sprite.getGlobalBounds();
                if(sprite.contains(mouse_position))
                {
                    sprite_loader.selection_sprite.setPosition(position);
                    window.draw(sprite_loader.selection_sprite);
                }
            } // Floor 2
        }
    }
}

void Game_scene::move_player(float deltaTimeSeconds)
{
    // New camera position.
    new_world_position = world_offset;

    // Move camera position.
    new_world_position -= get_velocity(deltaTimeSeconds);

    // Print offset.
    // std::cout << (int) world_offset.x << " " << (int) world_offset.y << '\n';

    // Check for collision after movement
    if (check_collision())
    {
        // Restore position to previous working one.
        world_offset = original_world_position;
        std::cout << "COLLISION" << '\n';
    }
    // No collision, update camera position.
    else
    {
        original_world_position = (sf::Vector2f(world_offset.x, world_offset.y));
        world_offset = new_world_position;
    }

    // Clear walls
    collision_sprites.clear();
}

// Get player velocity
sf::Vector2f Game_scene::get_velocity(float deltaTimeSeconds)
{
    sf::Vector2f player_velocity(0.f, 0.f);

    // Set player velocity
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player_velocity += sf::Vector2f(0.f, -100.f * deltaTimeSeconds * PLAYER_SPEED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player_velocity += sf::Vector2f(-100.f * deltaTimeSeconds * PLAYER_SPEED, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player_velocity += sf::Vector2f(0.f, 100.f * deltaTimeSeconds * PLAYER_SPEED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player_velocity += sf::Vector2f(100.f * deltaTimeSeconds * PLAYER_SPEED, 0.f);
    }
    // Correct velocity (pythagoras theorem approximation).
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
    {
        player_velocity = sf::Vector2f(player_velocity.x/100*60, player_velocity.y/100*60);
    }
    return player_velocity;
}


bool Game_scene::check_collision()
{
    sf::FloatRect playerBounds = this->sprite_loader.player_sprite.getGlobalBounds();

    playerBounds.height -= 8;
    playerBounds.width -= 8;
    playerBounds.top += 6;
    playerBounds.left += 6;
    
    // Check collision with each wall sprite
    for (const sf::Sprite& wallSprite : collision_sprites)
    {
        if (playerBounds.intersects(wallSprite.getGlobalBounds()))
        {
            return true; // Collision detected
        }
    }

    return false; // No collision
}

// Animations of sprites are handled here.
void Game_scene::update_sprites(sf::Clock& timer, sf::RenderWindow& window)
{
    int animation_offset = (int)timer.getElapsedTime().asMilliseconds() % 1500;
    animation_offset -= animation_offset%100;
    animation_offset -= animation_offset%10;
    animation_offset /= 150;
    animation_offset *= 16;

    sf::IntRect textureRect(0, 0, 16, 16);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        textureRect = sf::IntRect(80, 0, 16, 16); // Adjusted coordinates for the first version
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        textureRect = sf::IntRect(64, animation_offset, 16, 16); // Adjusted coordinates for the first version
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        textureRect = sf::IntRect(48, animation_offset, 16, 16); // Adjusted coordinates for the first version
        
    }
    else if ((int)timer.getElapsedTime().asMilliseconds() % 3000 > 2000)
    {
        textureRect = sf::IntRect(32, 0, 16, 16); // Adjusted coordinates for the first version
    }
    else if ((int)timer.getElapsedTime().asMilliseconds() % 3000 > 1000)
    {
        textureRect = sf::IntRect(16, 0, 16, 16); // Adjusted coordinates for the second version
    }
    else
    {
        textureRect = sf::IntRect(0, 0, 16, 16); // Adjusted coordinates for the third version
    }
    this->sprite_loader.player_sprite.setTextureRect(textureRect);
}

