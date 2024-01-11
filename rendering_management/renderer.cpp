#include "renderer.h"
#include <iostream>

const int TILE_SIZE = 16;




// Save all sprites for which collision should be checked.
std::vector<sf::Sprite> collision_sprites;
std::vector<sf::Sprite> npc_sprites;
std::vector<sf::Sprite> clickable_sprites;
sf::Vector2f world_offset(0.f, 0.f);
sf::Vector2f new_world_position(0.f, 0.f);
sf::Vector2f original_world_positio(0.f, 0.f);
sf::Vector2f original_world_position(world_offset);

// Render objects that are not tiles.
void Renderer::render_objects(sf::RenderWindow& window)
{
    window.draw(animation_manager.sprite_loader.player_sprite);
}

void Renderer::draw_level_objects(sf::Vector2f& position, int x, int y, sf::RenderWindow& window, sf::Vector2f mouse_position)
{
    

}

// This is where the tiles are drawn.
void Renderer::draw_level_tiles(sf::RenderWindow& window, sf::Vector2f mouse_position)
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
                animation_manager.sprite_loader.edge_0_sprite.setPosition(position);
                window.draw(animation_manager.sprite_loader.edge_0_sprite);
                
                collision_sprites.push_back(animation_manager.sprite_loader.edge_0_sprite);
            } // Edge 0
            else if (current_level->level_1_terrain[x][y] == '1')
            {
                animation_manager.sprite_loader.edge_1_sprite.setPosition(position);
                window.draw(animation_manager.sprite_loader.edge_1_sprite);

                collision_sprites.push_back(animation_manager.sprite_loader.edge_1_sprite);
            } // Edge 1
            else if (current_level->level_1_terrain[x][y] == '2')
            {
                animation_manager.sprite_loader.edge_2_sprite.setPosition(position);
                window.draw(animation_manager.sprite_loader.edge_2_sprite);

                collision_sprites.push_back(animation_manager.sprite_loader.edge_2_sprite);
            } // Edge 2
            else if (current_level->level_1_terrain[x][y] == '3')
            {
                animation_manager.sprite_loader.edge_3_sprite.setPosition(position);
                window.draw(animation_manager.sprite_loader.edge_3_sprite);

                collision_sprites.push_back(animation_manager.sprite_loader.edge_3_sprite);
            } // Edge 3
            else if (current_level->level_1_terrain[x][y] == '4')
            {
                animation_manager.sprite_loader.edge_4_sprite.setPosition(position);
                window.draw(animation_manager.sprite_loader.edge_4_sprite);

                collision_sprites.push_back(animation_manager.sprite_loader.edge_4_sprite);
            } // Edge 4
            else if (current_level->level_1_terrain[x][y] == '5')
            {
                animation_manager.sprite_loader.edge_5_sprite.setPosition(position);
                window.draw(animation_manager.sprite_loader.edge_5_sprite);

                collision_sprites.push_back(animation_manager.sprite_loader.edge_5_sprite);
            } // Edge 5
            else if (current_level->level_1_terrain[x][y] == '6')
            {
                animation_manager.sprite_loader.edge_6_sprite.setPosition(position);
                window.draw(animation_manager.sprite_loader.edge_6_sprite);

                collision_sprites.push_back(animation_manager.sprite_loader.edge_6_sprite);
            } // Edge 6
            else if (current_level->level_1_terrain[x][y] == '7')
            {
                animation_manager.sprite_loader.edge_7_sprite.setPosition(position);
                window.draw(animation_manager.sprite_loader.edge_7_sprite);

                collision_sprites.push_back(animation_manager.sprite_loader.edge_7_sprite);
            } // Edge 7
            
            else if (level_1->level_1_terrain[x][y] == 'F')
            {
                animation_manager.sprite_loader.floor_sprite.setPosition(position);
                window.draw(animation_manager.sprite_loader.floor_sprite);

                sf::FloatRect sprite = animation_manager.sprite_loader.floor_sprite.getGlobalBounds();

                // Draw selection square
                if(sprite.contains(mouse_position))
                {
                    animation_manager.sprite_loader.selection_sprite.setPosition(position);
                    window.draw(animation_manager.sprite_loader.selection_sprite);
                }
            } // Floor 1 
            else if (level_1->level_1_terrain[x][y] == 'L')
            {
                animation_manager.sprite_loader.floor2_sprite.setPosition(position);
                window.draw(animation_manager.sprite_loader.floor2_sprite);

                sf::FloatRect sprite = animation_manager.sprite_loader.floor2_sprite.getGlobalBounds();
                if(sprite.contains(mouse_position))
                {
                    animation_manager.sprite_loader.selection_sprite.setPosition(position);
                    window.draw(animation_manager.sprite_loader.selection_sprite);
                }
            } // Floor 2

            draw_level_objects(position, x, y, window, mouse_position);
        }
    }
    render_nps(window);
    render_mouse_icon(window, mouse_position);
}

void Renderer::render_nps(sf::RenderWindow& window)
{
    sf::Vector2f new_position = sf::Vector2f(animation_manager.sprite_loader.original_position_old_man_npc);
    new_position += world_offset;
    animation_manager.sprite_loader.old_man_npc.setPosition(new_position);
    window.draw(animation_manager.sprite_loader.old_man_npc);
    collision_sprites.push_back(animation_manager.sprite_loader.old_man_npc);
    npc_sprites.push_back(animation_manager.sprite_loader.old_man_npc);


}
void Renderer::render_mouse_icon(sf::RenderWindow& window, sf::Vector2f mouse_position)
{    
    for(sf::Sprite sprite : npc_sprites)
    {
        if(sprite.getGlobalBounds().contains(mouse_position))
        {
            if( sprite.getGlobalBounds().getPosition().x < SCREEN_WIDTH/2 + 100 && 
                sprite.getGlobalBounds().getPosition().x > SCREEN_WIDTH/2 - 100 && 
                sprite.getGlobalBounds().getPosition().y < SCREEN_HEIGHT/2 + 150 && 
                sprite.getGlobalBounds().getPosition().y > SCREEN_HEIGHT/2 - 150 && 
                sprite.getGlobalBounds().contains(mouse_position))
            {
                animation_manager.sprite_loader.talk_icon_sprite.setPosition(mouse_position);
                window.draw(animation_manager.sprite_loader.talk_icon_sprite);  
            }
                      
        }
    }

    // Clear npc sprite vector when done.
    npc_sprites.clear();
}

void Renderer::handle_clicks(sf::RenderWindow& window, sf::Vector2f mouse_position)
{
    // Handle click
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f mouse_click_location = mouse_position;
        if(this->animation_manager.sprite_loader.old_man_npc.getGlobalBounds().contains(mouse_click_location))
        {
            std::cout << "OLD MAN CLICKED" << std::endl;
        }
    }

    // Clear walls
    
}

void Renderer::clean_up()
{
    collision_sprites.clear();
    clickable_sprites.clear();
}

void Renderer::move_player(float deltaTimeSeconds)
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
        // world_offset = original_world_position;
        std::cout << "COLLISION" << '\n';
    }
    // No collision, update camera position.
    else
    {
        original_world_position = world_offset;
        world_offset = new_world_position;
    }

    
}

// Get player velocity
sf::Vector2f Renderer::get_velocity(float deltaTimeSeconds)
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


bool Renderer::check_collision()
{
    sf::FloatRect playerBounds = this->animation_manager.sprite_loader.player_sprite.getGlobalBounds();

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



