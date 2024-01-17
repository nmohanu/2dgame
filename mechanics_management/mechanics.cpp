#include "mechanics.h"
#include <iostream>


void clean_up(std::vector<sf::Sprite>& collision_sprites, std::vector<sf::Sprite>& clickable_sprites)
{
    collision_sprites.clear();
    clickable_sprites.clear();
}

void update_hotbar(Sprite_loader& sprite_loader, Inventory& inventory)
{
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        inventory.current_selection = 0;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        inventory.current_selection = 1;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        inventory.current_selection = 2;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        inventory.current_selection = 3;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        inventory.current_selection = 4;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        inventory.current_selection = 5;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        inventory.current_selection = 6;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        inventory.current_selection = 7;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
        inventory.current_selection = 8;
        
}

void move_player(float deltaTimeSeconds, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, sf::Vector2f& original_world_position, std::vector<sf::Sprite>& collision_sprites, Sprite_loader& sprite_loader)
{
    // New camera position.
    new_world_position = world_offset;

    // Wether or not to update the world position.
    bool update_world = false;

    // Move camera position.
    new_world_position -= get_velocity(deltaTimeSeconds);

    // Print offset.
    // std::cout << (int) world_offset.x << " " << (int) world_offset.y << '\n';

    // Check for collision after movement
    if (check_collision(collision_sprites, new_world_position, world_offset, sprite_loader))
    {
        // Try if there is collision without one of the keys pressed.
        new_world_position = original_world_position;
        sf::Vector2f adjusted_velocity = get_velocity(deltaTimeSeconds);
        new_world_position -= adjusted_velocity;
        new_world_position.x = world_offset.x;
        if(!check_collision(collision_sprites, new_world_position, world_offset, sprite_loader))
        {
            update_world = true;
        }
        // Try again but without y.
        else
        {
            new_world_position = original_world_position;
            adjusted_velocity = get_velocity(deltaTimeSeconds);
            new_world_position -= adjusted_velocity;
            new_world_position.y = world_offset.y;
            if(!check_collision(collision_sprites, new_world_position, world_offset, sprite_loader))
            {
                update_world = true;
            }
        }
    } 
    else
    {
        update_world = true;
    }

    // No collision, update camera position.
    if(update_world)
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
    sf::FloatRect player_bounds = sprite_loader.player_sprite.getGlobalBounds();

    sf::FloatRect adjustedPlayerBounds(
        player_bounds.left + 20,      // Adjust left
        player_bounds.top + 46,       // Adjust top
        player_bounds.width - 40,     // Adjust width
        player_bounds.height - 60     // Adjust height
    );

    
    // Check collision with each wall sprite
    for (const sf::Sprite& wallSprite : collision_sprites)
    {
        sf::FloatRect new_position = wallSprite.getGlobalBounds();
        new_position.left -= world_offset.x;
        new_position.top -= world_offset.y;
        new_position.left += new_world_position.x;
        new_position.top += new_world_position.y;
        if (adjustedPlayerBounds.intersects(new_position))
        {
            return true; // Collision detected
        }
    }

    return false; // No collision
}

void handle_clicks(sf::RenderWindow& window, sf::Event& event,  sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Dialogue_manager& manager, Level& level, Inventory& player_inventory)
{
    
    if(event.mouseButton.button == sf::Mouse::Left)
    {
        std::cout << "VECTOR MEM: " << &manager.spork_dialogues << std::endl;
        sf::Vector2f mouse_click_location = mouse_position;
        if(sprite_loader.old_man_npc.getGlobalBounds().contains(mouse_click_location))
        {
            if(manager.current != nullptr && manager.current->finished && manager.current->next != nullptr)
            {
                manager.current = manager.current->next;
            }
            if(manager.current != nullptr && manager.current->finished != true)
            {
                manager.current->in_dialogue = true;
                std::cout << &manager.current;
            } else
            {
                manager.current = nullptr;
            }
        }
        if(level.level_1_objects[sprite_loader.mouse_pos_y][sprite_loader.mouse_pos_x] == "0000LEAF")
        {
            
            level.level_1_objects[sprite_loader.mouse_pos_y][sprite_loader.mouse_pos_x] = '0';
            if(player_inventory.leafs != nullptr)
            {
                player_inventory.leafs->amount++;
                if(player_inventory.leafs->amount == 1)
                {
                    for(int i  = 0; i < 9; i++)
                    {
                        // Find first empty spot.
                        if(player_inventory.hotbar[i] == "00000000")
                        {
                            // Set spot to item code.
                            player_inventory.hotbar[i] = "0000LEAF";
                            break;
                            
                        }
                        std::cout << "INVENTORY SPOT: " << i << " ITEM: " << player_inventory.hotbar[i] << '\n';
                    }
                }
            }
            
            std::cout << "WEED: " << player_inventory.leafs->amount << std::endl;
            // std::cout << &player_inventory.weed->amount << " IN M \n";
        }
    }
}

void update_world(sf::RenderWindow& window, Sprite_loader& sprite_loader, Level& level, sf::Clock& game_clock)
{
    // Update world every 5 seconds
    if((float) game_clock.getElapsedTime().asSeconds() >= 5)
    {
        game_clock.restart();
        
        for(int y = 1; y < level.LEVEL_HEIGHT-1; y++)
        {
            for(int x = 1; x < level.LEVEL_WIDTH-1; x++)
            {
                int random_num = std::rand() % 10000;
                
                if(random_num > 9900 && level.level_1_objects[y][x] == "00000000")
                {
                    // Spawn weeds
                    level.level_1_objects[y][x] = "0000LEAF";
                }
                //std::cout<< random_num << std::endl;
            }
        }
        std::cout << "world updated" << '\n';
    }
}