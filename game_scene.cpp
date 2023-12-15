#include "game_scene.h"
#include "level.h"
#include <iostream>

const int TILE_SIZE = 16;

// Save all sprites for which collision should be checked.
std::vector<sf::Sprite> collision_sprites;

// Render objects that are not tiles.
void Game_scene::render_objects(sf::RenderWindow& window)
{
    window.draw(sprite_loader.player_sprite);
}

// This is where the tiles are drawn.
void Game_scene::draw_level(sf::RenderWindow& window)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            int index = y * 16 + x;

            if (level_loader.level_1_terrain[index] == '#')
            {
                sprite_loader.wall_sprite.setPosition(x * SCALE_FACTOR * TILE_SIZE + (SCREEN_WIDTH - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR))/2, y * SCALE_FACTOR * TILE_SIZE + (SCREEN_HEIGHT - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR))/2);
                window.draw(sprite_loader.wall_sprite);

                // Save in collision sprites.
                collision_sprites.push_back(sprite_loader.wall_sprite);
            }
            else if (level_loader.level_1_terrain[index] == 'F')
            {
                sprite_loader.floor_sprite.setPosition(x * SCALE_FACTOR * TILE_SIZE + (SCREEN_WIDTH - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR))/2, y * SCALE_FACTOR * TILE_SIZE + (SCREEN_HEIGHT - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR))/2);
                window.draw(sprite_loader.floor_sprite);
            }
        }
    }
}

void Game_scene::move_player(float deltaTimeSeconds)
{
    // Store the original player position
    sf::Vector2f originalPosition = this->sprite_loader.player_sprite.getPosition();

    // Handle player movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->sprite_loader.player_sprite.move(0.f, -100.f * deltaTimeSeconds * PLAYER_SPEED); // Move upward
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->sprite_loader.player_sprite.move(-100.f * deltaTimeSeconds * PLAYER_SPEED, 0.f); // Move to the left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->sprite_loader.player_sprite.move(0.f, 100.f * deltaTimeSeconds * PLAYER_SPEED); // Move downward
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->sprite_loader.player_sprite.move(100.f * deltaTimeSeconds * PLAYER_SPEED, 0.f); // Move to the right
    }

    // Check for collision after movement
    if (check_collision())
    {
        // If collision occurred, reset player position
        this->sprite_loader.player_sprite.setPosition(originalPosition);
    }

    // Clear walls (if this is the appropriate place to do so)
    collision_sprites.clear();
}

bool Game_scene::check_collision()
{
    sf::FloatRect playerBounds = this->sprite_loader.player_sprite.getGlobalBounds();

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
        sf::IntRect textureRect(32, 0, 16, 16); // Adjusted coordinates for the first version
        this->sprite_loader.player_sprite.setTextureRect(textureRect);
    }
    else if ((int)timer.getElapsedTime().asMilliseconds() % 3000 > 1000)
    {
        sf::IntRect textureRect(16, 0, 16, 16); // Adjusted coordinates for the second version
        this->sprite_loader.player_sprite.setTextureRect(textureRect);
    }
    else
    {
        sf::IntRect textureRect(0, 0, 16, 16); // Adjusted coordinates for the third version
        this->sprite_loader.player_sprite.setTextureRect(textureRect);
    }
}



