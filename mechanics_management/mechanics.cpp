#include "mechanics.h"
#include <iostream>

void clean_up(std::vector<sf::Sprite>& collision_sprites, std::vector<sf::Sprite>& clickable_sprites)
{
    collision_sprites.clear();
    clickable_sprites.clear();
}

void move_player(float deltaTimeSeconds, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, sf::Vector2f& original_world_position, std::vector<sf::Sprite>& collision_sprites, Sprite_loader& sprite_loader)
{
    // New camera position.
    new_world_position = world_offset;

    // Move camera position.
    new_world_position -= get_velocity(deltaTimeSeconds);

    // Print offset.
    // std::cout << (int) world_offset.x << " " << (int) world_offset.y << '\n';

    // Check for collision after movement
    if (check_collision(collision_sprites, new_world_position, world_offset, sprite_loader))
    {
        // Restore position to previous working one.
        // world_offset = original_world_position;
    }
    // No collision, update camera position.
    else
    {
        original_world_position = world_offset;
        world_offset = new_world_position;
    }

    
}

// Get player velocity
sf::Vector2f get_velocity(float deltaTimeSeconds)
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


bool check_collision(std::vector<sf::Sprite>& collision_sprites, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, Sprite_loader& sprite_loader)
{
    sf::FloatRect playerBounds = sprite_loader.player_sprite.getGlobalBounds();

    playerBounds.height -= 4;
    playerBounds.width -= 4;
    
    // Check collision with each wall sprite
    for (const sf::Sprite& wallSprite : collision_sprites)
    {
        sf::FloatRect new_position = wallSprite.getGlobalBounds();
        new_position.left -= world_offset.x;
        new_position.top -= world_offset.y;
        new_position.left += new_world_position.x;
        new_position.top += new_world_position.y;
        if (playerBounds.intersects(new_position))
        {
            return true; // Collision detected
        }
    }

    return false; // No collision
}

void handle_clicks(sf::RenderWindow& window, sf::Event& event,  sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Dialogue_manager& manager)
{
    
    if(event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mouse_click_location = mouse_position;
        if(sprite_loader.old_man_npc.getGlobalBounds().contains(mouse_click_location))
        {
            std::cout << "Old man clicked\n";
            // std::cout << manager.dialogues.size() << " dialogues in vector at click." <<'\n';
            for(Dialogue& dialogue : manager.dialogues)
            {
                if(dialogue.ID == "SPORK_1")
                {
                    dialogue.in_dialogue = true;
                }
            }
        }
    }
}