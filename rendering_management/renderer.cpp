#include "renderer.h"
#include <iostream>

std::vector<sf::Sprite> collision_sprites;
std::vector<sf::Sprite> npc_sprites;
std::vector<sf::Sprite> clickable_sprites;
sf::Vector2f world_offset(0.f, 0.f);
sf::Vector2f new_world_position(0.f, 0.f);
sf::Vector2f original_world_position(world_offset);


void Renderer::player_movement(float deltaTimeSeconds, Sprite_loader& sprite_loader)
{
    // Move player.
    move_player(deltaTimeSeconds, new_world_position, world_offset, original_world_position, collision_sprites, sprite_loader);
    clean_up(collision_sprites, npc_sprites);
}

void Renderer::render_everything(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader)
{
    // UI elements.
    window.draw(sprite_loader.coin_sprite);
    window.draw(sprite_loader.coin_sprite);

    // Draw level.
    draw_level_tiles(window, mouse_position, sprite_loader);
    render_objects(window, sprite_loader);
}

// Render objects that are not tiles.
void Renderer::render_objects(sf::RenderWindow& window, Sprite_loader& sprite_loader)
{
    window.draw(sprite_loader.player_sprite);
    
}

void Renderer::draw_level_objects(sf::Vector2f& position, int x, int y, sf::RenderWindow& window, sf::Vector2f mouse_position)
{
    

}

// This is where the tiles are drawn.
void Renderer::draw_level_tiles(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader)
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

                // Draw selection square
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

            draw_level_objects(position, x, y, window, mouse_position);
        }
    }
    render_npc(window, sprite_loader);
    render_mouse_icon(window, mouse_position, sprite_loader);
}

void Renderer::render_npc(sf::RenderWindow& window, Sprite_loader& sprite_loader)
{
    sf::Vector2f new_position = sf::Vector2f(sprite_loader.original_position_old_man_npc);
    new_position += world_offset;
    sprite_loader.old_man_npc.setPosition(new_position);
    window.draw(sprite_loader.old_man_npc);
    collision_sprites.push_back(sprite_loader.old_man_npc);
    npc_sprites.push_back(sprite_loader.old_man_npc);
}

void Renderer::render_mouse_icon(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader)
{    
    for(sf::Sprite sprite : npc_sprites)
    {
        if(sprite.getGlobalBounds().contains(mouse_position))
        {
            if( sprite.getPosition().x < SCREEN_WIDTH/2 + 100 && 
                sprite.getPosition().x > SCREEN_WIDTH/2 - 100 && 
                sprite.getPosition().y < SCREEN_HEIGHT/2 + 150 && 
                sprite.getPosition().y > SCREEN_HEIGHT/2 - 150 && 
                sprite.getGlobalBounds().contains(mouse_position))
            {
                sprite_loader.talk_icon_sprite.setPosition(mouse_position);
                window.draw(sprite_loader.talk_icon_sprite);  
            }          
        }
    }
}





