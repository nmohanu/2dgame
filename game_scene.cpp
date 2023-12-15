#include "game_scene.h"
#include "level.h"
#include <iostream>

const int TILE_SIZE = 16;

// Save all sprites for which collision should be checked.
std::vector<sf::Sprite> collision_sprites;
sf::Vector2f world_offset(0.f, 0.f);
sf::Vector2f new_world_position(0.f, 0.f);
sf::Vector2f original_world_positio(0.f, 0.f);

// Render objects that are not tiles.
void Game_scene::render_objects(sf::RenderWindow& window)
{
    window.draw(sprite_loader.player_sprite);
}

// This is where the tiles are drawn.
void Game_scene::draw_level(sf::RenderWindow& window)
{
    for (int y = 0; y < current_level->LEVEL_HEIGHT; y++)
    {
        for (int x = 0; x < current_level->LEVEL_WIDTH; x++)
        {
            if (current_level->level_1_terrain[x][y] == '#')
            {
                sf::Vector2f position(x * SCALE_FACTOR * TILE_SIZE + (SCREEN_WIDTH - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR))/2,
                                       y * SCALE_FACTOR * TILE_SIZE + (SCREEN_HEIGHT - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR))/2);

                // Apply world offset to position
                position += world_offset;

                sprite_loader.wall_sprite.setPosition(position);
                window.draw(sprite_loader.wall_sprite);

                collision_sprites.push_back(sprite_loader.wall_sprite);
            }
            else if (level_1->level_1_terrain[x][y] == 'F')
            {
                sf::Vector2f position(x * SCALE_FACTOR * TILE_SIZE + (SCREEN_WIDTH - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR))/2,
                                       y * SCALE_FACTOR * TILE_SIZE + (SCREEN_HEIGHT - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR))/2);

                // Apply world offset to position
                position += world_offset;

                sprite_loader.floor_sprite.setPosition(position);
                window.draw(sprite_loader.floor_sprite);
            }
        }
    }
}

void Game_scene::move_player(float deltaTimeSeconds)
{
    // Store the original camera position.
    sf::Vector2f original_world_position(world_offset);

    // New camera position.
    new_world_position = world_offset;

    // Move camera position.
    new_world_position -= get_velocity(deltaTimeSeconds);

    // // Print offset.
    std::cout << (int) world_offset.x << " " << (int) world_offset.y << '\n';

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

    // Clear walls (if this is the appropriate place to do so)
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

    // Character sprite is 12 pixels wide.
    playerBounds.left += (playerBounds.width - 12) / 2;
    playerBounds.width = 12;

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
    if ((int)timer.getElapsedTime().asMilliseconds() % 3000 > 2000)
    {
        sf::IntRect textureRect(32, 0, 16, 16); // Adjusted sprite for the first version
        this->sprite_loader.player_sprite.setTextureRect(textureRect);
    }
    else if ((int)timer.getElapsedTime().asMilliseconds() % 3000 > 1000)
    {
        sf::IntRect textureRect(16, 0, 16, 16); // Adjusted sprite for the second version
        this->sprite_loader.player_sprite.setTextureRect(textureRect);
    }
    else
    {
        sf::IntRect textureRect(0, 0, 16, 16); // Adjusted sprite for the third version
        this->sprite_loader.player_sprite.setTextureRect(textureRect);
    }
}



