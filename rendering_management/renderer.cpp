#include "renderer.h"
#include <iostream>



sf::Vector2f world_offset(0.f, 0.f);
sf::Vector2f new_world_position(0.f, 0.f);
sf::Vector2f original_world_position(world_offset);

void Renderer::player_movement(float deltaTimeSeconds, Sprite_loader& sprite_loader)
{
    // Move player.
    move_player(deltaTimeSeconds, new_world_position, world_offset, original_world_position, collision_sprites, sprite_loader);
    clean_up(collision_sprites, npc_sprites);
}

void Renderer::render_everything(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Inventory& player_inventory)
{
    // UI elements.
    window.draw(sprite_loader.coin_sprite);
    window.draw(sprite_loader.coin_sprite);

    // Draw level.
    draw_level_tiles(window, mouse_position, sprite_loader);
    for(sf::Sprite sprite : render_tile_sprites)
    {
        window.draw(sprite);
    }
    
    for(sf::Sprite sprite : render_object_sprites)
    {
        window.draw(sprite);
    }

    draw_player_hotbar(window, sprite_loader, player_inventory);

    render_npc(window, sprite_loader);
    render_objects(window, sprite_loader);
    render_mouse_icon(window, mouse_position, sprite_loader, player_inventory);

    

    render_tile_sprites.clear();
    render_object_sprites.clear();
}

// Draw inventory hotbar.
void Renderer::draw_player_hotbar(sf::RenderWindow& window, Sprite_loader& sprite_loader, Inventory& player_inventory)
{
    window.draw(sprite_loader.inventory_sprite);

    for(int i = 0; i < 9; i++)
    {
        if(player_inventory.hotbar[i] != "00000000")
        {
            // Render the item found in the hotbar.
            
            for(Item* item : player_inventory.items)
            {
                if(item->ID == player_inventory.hotbar[i])
                {
                    int x_position = hotbar_item_1_pos.x + 16*i*INV_SCALE + i*INV_SCALE;
                    item->sprite.setPosition(x_position, hotbar_item_1_pos.y);
                    item->sprite.setScale(INV_SCALE, INV_SCALE);

                    // Display the amount.
                    player_inventory.amount.setPosition(x_position + 38, hotbar_item_1_pos.y + 18);
                    player_inventory.amount.setString(std::to_string(item->amount));

                    window.draw(item->sprite);
                    window.draw(player_inventory.amount);
                }
            }
        }
    }
    sprite_loader.hotbar_selection_sprite.setPosition(hotbar_item_1_pos.x + 17*player_inventory.current_selection*INV_SCALE - INV_SCALE, sprite_loader.inventory_sprite.getPosition().y);
    window.draw(sprite_loader.hotbar_selection_sprite);
}

// Render objects that are not tiles.
void Renderer::render_objects(sf::RenderWindow& window, Sprite_loader& sprite_loader)
{

    window.draw(sprite_loader.player_sprite);
}

void Renderer::draw_level_objects(sf::RenderWindow& window, Sprite_loader& sprite_loader, int x, int y, sf::Vector2f position)
{
    if(current_level->level_1_objects[y][x] == "0000LEAF")
    {
        sprite_loader.weed_sprite.setPosition(position);
        render_object_sprites.push_back(sprite_loader.weed_sprite);
    }
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

            if (current_level->level_1_terrain[y][x] == '0')
            {
                sprite_loader.edge_0_sprite.setPosition(position);
                render_tile_sprites.push_back(sprite_loader.edge_0_sprite);
                
                collision_sprites.push_back(sprite_loader.edge_0_sprite);
            } // Edge 0
            else if (current_level->level_1_terrain[y][x] == '1')
            {
                sprite_loader.edge_1_sprite.setPosition(position);
                render_tile_sprites.push_back(sprite_loader.edge_1_sprite);

                collision_sprites.push_back(sprite_loader.edge_1_sprite);
            } // Edge 1
            else if (current_level->level_1_terrain[y][x] == '2')
            {
                sprite_loader.edge_2_sprite.setPosition(position);
                render_tile_sprites.push_back(sprite_loader.edge_2_sprite);

                collision_sprites.push_back(sprite_loader.edge_2_sprite);
            } // Edge 2
            else if (current_level->level_1_terrain[y][x] == '3')
            {
                sprite_loader.edge_3_sprite.setPosition(position);
                render_tile_sprites.push_back(sprite_loader.edge_3_sprite);

                collision_sprites.push_back(sprite_loader.edge_3_sprite);
            } // Edge 3
            else if (current_level->level_1_terrain[y][x] == '4')
            {
                sprite_loader.edge_4_sprite.setPosition(position);
                render_tile_sprites.push_back(sprite_loader.edge_4_sprite);

                collision_sprites.push_back(sprite_loader.edge_4_sprite);
            } // Edge 4
            else if (current_level->level_1_terrain[y][x] == '5')
            {
                sprite_loader.edge_5_sprite.setPosition(position);
                render_tile_sprites.push_back(sprite_loader.edge_5_sprite);

                collision_sprites.push_back(sprite_loader.edge_5_sprite);
            } // Edge 5
            else if (current_level->level_1_terrain[y][x] == '6')
            {
                sprite_loader.edge_6_sprite.setPosition(position);
                render_tile_sprites.push_back(sprite_loader.edge_6_sprite);

                collision_sprites.push_back(sprite_loader.edge_6_sprite);
            } // Edge 6
            else if (current_level->level_1_terrain[y][x] == '7')
            {
                sprite_loader.edge_7_sprite.setPosition(position);
                render_tile_sprites.push_back(sprite_loader.edge_7_sprite);

                collision_sprites.push_back(sprite_loader.edge_7_sprite);
            } // Edge 7
            
            else if (level_1->level_1_terrain[y][x] == 'F')
            {
                sprite_loader.floor_sprite.setPosition(position);
                render_tile_sprites.push_back(sprite_loader.floor_sprite);

                sf::FloatRect sprite = sprite_loader.floor_sprite.getGlobalBounds();

                // Draw selection square
                if(sprite.contains(mouse_position) && abs(mouse_position.x - CENTER_X) < PLAYER_REACH
                    && abs(mouse_position.y - CENTER_Y) < PLAYER_REACH)
                {
                    sprite_loader.selection_sprite.setPosition(position);
                    render_tile_sprites.push_back(sprite_loader.selection_sprite);
                    sprite_loader.mouse_pos_x = x;
                    sprite_loader.mouse_pos_y = y;
                }
            } // Floor 1 
            else if (level_1->level_1_terrain[y][x] == 'L')
            {
                sprite_loader.floor2_sprite.setPosition(position);
                render_tile_sprites.push_back(sprite_loader.floor2_sprite);

                sf::FloatRect sprite = sprite_loader.floor2_sprite.getGlobalBounds();
                if(sprite.contains(mouse_position) && abs(mouse_position.x - CENTER_X) < PLAYER_REACH
                    && abs(mouse_position.y - CENTER_Y) < PLAYER_REACH)
                {
                    sprite_loader.selection_sprite.setPosition(position);
                    render_tile_sprites.push_back(sprite_loader.selection_sprite);
                    sprite_loader.mouse_pos_x = x;
                    sprite_loader.mouse_pos_y = y;
                }
            } // Floor 2
            draw_level_objects(window, sprite_loader, x, y, position);
        }
    }
}

// Render the npcs.
void Renderer::render_npc(sf::RenderWindow& window, Sprite_loader& sprite_loader)
{
    sf::Vector2f new_position = sf::Vector2f(sprite_loader.original_position_old_man_npc);
    new_position += world_offset;
    sprite_loader.old_man_npc.setPosition(new_position);
    window.draw(sprite_loader.old_man_npc);
    collision_sprites.push_back(sprite_loader.old_man_npc);
    npc_sprites.push_back(sprite_loader.old_man_npc);
}


// Render the mouse.
void Renderer::render_mouse_icon(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Inventory& player_inventory)
{    
    bool cursor_drawn = false;
    for(sf::Sprite sprite : npc_sprites)
    {
        if(sprite.getGlobalBounds().contains(mouse_position))
        {
            if( abs(mouse_position.x - CENTER_X) < PLAYER_REACH
                && abs(mouse_position.y - CENTER_Y) < PLAYER_REACH && 
                sprite.getGlobalBounds().contains(mouse_position))
            {
                sprite_loader.talk_icon_sprite.setPosition(mouse_position.x-8, mouse_position.y-8);
                window.draw(sprite_loader.talk_icon_sprite);  
                cursor_drawn = true;
            }          
        }
    }
    for(sf::Sprite sprite : render_object_sprites)
    {
        if(sprite.getGlobalBounds().contains(mouse_position))
        {
            if( abs(mouse_position.x - CENTER_X) < PLAYER_REACH
                && abs(mouse_position.y - CENTER_Y) < PLAYER_REACH&& 
                sprite.getGlobalBounds().contains(mouse_position))
            {
                sprite_loader.grab_icon_sprite.setPosition(mouse_position.x-8, mouse_position.y-8);
                window.draw(sprite_loader.grab_icon_sprite);  
                cursor_drawn = true;
            }          
        }
    }
    if(!cursor_drawn)
    {
        sprite_loader.default_mouse_icon_sprite.setPosition(mouse_position.x-8, mouse_position.y-8);
        window.draw(sprite_loader.default_mouse_icon_sprite);
    }
    if(player_inventory.draw_progress)
    {
        window.draw(sprite_loader.progress_bar_sprite);
        player_inventory.draw_progress = false;
    }
}





