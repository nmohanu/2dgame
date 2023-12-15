#include "game_scene.h"
#include "level.h"
#include <iostream>

const int TILE_SIZE = 16;

// Save all sprites for which collision should be checked.
std::vector<sf::Sprite> collision_sprites;
sf::Vector2f world_offset(0.f, 0.f);

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

                // No need to save in collision_sprites here
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
    // Store the original player position
    sf::Vector2f originalPosition = this->sprite_loader.player_sprite.getPosition();

    // Calculate the world offset based on player position

    sf::RectangleShape rectangle(sf::Vector2f(200.f, 200.f)); // Width and height of the rectangle
    rectangle.setPosition(SCREEN_WIDTH/2 - 100.f, SCREEN_HEIGHT/2 - 100.f);

    bool move_camera = true;

    sf::FloatRect rectBounds = rectangle.getGlobalBounds();

    for (const sf::Sprite& wallSprite : collision_sprites)
    {
        if (rectBounds.intersects(wallSprite.getGlobalBounds()))
        {
            move_camera = false;
        }
    }

    // Move player
    if(move_camera)
    {
        // Handle player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->sprite_loader.player_sprite.move(get_velocity(deltaTimeSeconds)); // Move upward
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->sprite_loader.player_sprite.move(get_velocity(deltaTimeSeconds)); // Move to the left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->sprite_loader.player_sprite.move(get_velocity(deltaTimeSeconds)); // Move downward
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->sprite_loader.player_sprite.move(get_velocity(deltaTimeSeconds)); // Move to the right
        }
    }

    std::cout << (int) world_offset.x << " " << (int) world_offset.y << '\n';


    // Check for collision after movement
    if (check_collision())
    {
        // If collision occurred, reset player position
        this->sprite_loader.player_sprite.setPosition(originalPosition);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            world_offset.y = world_offset.y - get_velocity(deltaTimeSeconds).y;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            world_offset.x = world_offset.x - get_velocity(deltaTimeSeconds).x;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            world_offset.y = world_offset.y - get_velocity(deltaTimeSeconds).y;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            world_offset.x = world_offset.x - get_velocity(deltaTimeSeconds).x;
        }
        std::cout << "check" << '\n';
    }

    // Move screen...

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
    // Correct velocity
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
    (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
    (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
    (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
    {
        player_velocity = sf::Vector2f(player_velocity.x/2, player_velocity.y/2);
    }
    return player_velocity;
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
    if(this->sprite_loader.player_sprite.getPosition().x <= SCREEN_WIDTH/2 - 100 ||
       this->sprite_loader.player_sprite.getPosition().x >= SCREEN_WIDTH/2 + 100 ||
       this->sprite_loader.player_sprite.getPosition().y <= SCREEN_HEIGHT/2 - 100 ||
       this->sprite_loader.player_sprite.getPosition().y >= SCREEN_HEIGHT/2 + 100)
    {
        return true;
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



