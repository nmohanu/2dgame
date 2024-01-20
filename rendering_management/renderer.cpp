#include "renderer.h"
#include <iostream>





void Renderer::player_movement(float deltaTimeSeconds, Sprite_loader& sprite_loader)
{
    // Move player.
    move_player(deltaTimeSeconds, new_world_position, world_offset, original_world_position, collision_sprites, sprite_loader);
    clean_up(collision_sprites, npc_sprites);
}

void Renderer::render_everything(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Inventory& player_inventory, Dialogue_manager& manager)
{
    // UI elements.
    window.draw(sprite_loader.coin_sprite);
    window.draw(sprite_loader.coin_sprite);

    // Draw level.
    draw_level_tiles(window, mouse_position, sprite_loader, manager);
    for(sf::Sprite sprite : sprite_loader.render_tile_sprites)
    {
        window.draw(sprite);
    }
    
    for(sf::Sprite sprite : render_object_sprites)
    {
        window.draw(sprite);
    }

    draw_player_hotbar(window, sprite_loader, player_inventory);

    render_npc(window, sprite_loader, manager);
    render_objects(window, sprite_loader);
    render_mouse_icon(window, mouse_position, sprite_loader, player_inventory);

    

    sprite_loader.render_tile_sprites.clear();
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

void Renderer::draw_level_objects(sf::RenderWindow& window, Sprite_loader& sprite_loader, int x, int y, sf::Vector2f position, Dialogue_manager& manager)
{
    if(manager.current_level->level_1_objects[y][x] == "0000LEAF")
    {
        sprite_loader.weed_sprite.setPosition(position);
        render_object_sprites.push_back(sprite_loader.weed_sprite);
    }

    else if(manager.current_level->level_1_objects[y][x] == "000TREE1")
    {
        sprite_loader.tree1_sprite.setPosition(position.x - 16*SCALE_FACTOR_X, position.y - 32*SCALE_FACTOR_Y);
        
        render_object_sprites.push_back(sprite_loader.tree1_sprite);
        sf::FloatRect tree1_sprite_bounds = sprite_loader.tree1_sprite.getGlobalBounds();
        sf::FloatRect adjustedTreeBounds(
            tree1_sprite_bounds.left,      // Adjust left
            tree1_sprite_bounds.top + 16*SCALE_FACTOR_X,       // Adjust top
            tree1_sprite_bounds.width - 16*SCALE_FACTOR_X,     // Adjust width
            tree1_sprite_bounds.height - 16*SCALE_FACTOR_Y     // Adjust height
        );
        collision_sprites.push_back(adjustedTreeBounds);
    }
    else if(manager.current_level->level_1_objects[y][x] == "000TREE2")
    {
        sprite_loader.tree2_sprite.setPosition(position);
        render_object_sprites.push_back(sprite_loader.tree2_sprite);
        collision_sprites.push_back(sprite_loader.tree2_sprite.getGlobalBounds());
    }
    else if(manager.current_level->level_1_objects[y][x] == "00GRAVE1")
    {
        sprite_loader.grave1_sprite.setPosition(position);
        render_object_sprites.push_back(sprite_loader.grave1_sprite);
        collision_sprites.push_back(sprite_loader.grave1_sprite.getGlobalBounds());
    }
}

// This is where the tiles are drawn.
void Renderer::draw_level_tiles(sf::RenderWindow& window, sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Dialogue_manager& manager)
{
    for (int y = 0; y < manager.current_level->LEVEL_HEIGHT; y++)
    {
        for (int x = 0; x < manager.current_level->LEVEL_WIDTH; x++)
        {
            sf::Vector2f position = get_tile_cords(x, y, world_offset, manager);

            if (manager.current_level->level_1_terrain[y][x] == '0')
            {
                sprite_loader.edge_0_sprite.setPosition(position);
                sprite_loader.render_tile_sprites.push_back(sprite_loader.edge_0_sprite);
                
                collision_sprites.push_back(sprite_loader.edge_0_sprite.getGlobalBounds());
            } // Edge 0
            else if (manager.current_level->level_1_terrain[y][x] == '1')
            {
                sprite_loader.edge_1_sprite.setPosition(position);
                sprite_loader.render_tile_sprites.push_back(sprite_loader.edge_1_sprite);

                collision_sprites.push_back(sprite_loader.edge_1_sprite.getGlobalBounds());
            } // Edge 1
            else if (manager.current_level->level_1_terrain[y][x] == '2')
            {
                sprite_loader.edge_2_sprite.setPosition(position);
                sprite_loader.render_tile_sprites.push_back(sprite_loader.edge_2_sprite);

                collision_sprites.push_back(sprite_loader.edge_2_sprite.getGlobalBounds());
            } // Edge 2
            else if (manager.current_level->level_1_terrain[y][x] == '3')
            {
                sprite_loader.edge_3_sprite.setPosition(position);
                sprite_loader.render_tile_sprites.push_back(sprite_loader.edge_3_sprite);

                collision_sprites.push_back(sprite_loader.edge_3_sprite.getGlobalBounds());
            } // Edge 3
            else if (manager.current_level->level_1_terrain[y][x] == '4')
            {
                sprite_loader.edge_4_sprite.setPosition(position);
                sprite_loader.render_tile_sprites.push_back(sprite_loader.edge_4_sprite);

                collision_sprites.push_back(sprite_loader.edge_4_sprite.getGlobalBounds());
            } // Edge 4
            else if (manager.current_level->level_1_terrain[y][x] == '5')
            {
                sprite_loader.edge_5_sprite.setPosition(position);
                sprite_loader.render_tile_sprites.push_back(sprite_loader.edge_5_sprite);

                collision_sprites.push_back(sprite_loader.edge_5_sprite.getGlobalBounds());
            } // Edge 5
            else if (manager.current_level->level_1_terrain[y][x] == '6')
            {
                sprite_loader.edge_6_sprite.setPosition(position);
                sprite_loader.render_tile_sprites.push_back(sprite_loader.edge_6_sprite);

                collision_sprites.push_back(sprite_loader.edge_6_sprite.getGlobalBounds());
            } // Edge 6
            else if (manager.current_level->level_1_terrain[y][x] == '7')
            {
                sprite_loader.edge_7_sprite.setPosition(position);
                sprite_loader.render_tile_sprites.push_back(sprite_loader.edge_7_sprite);

                collision_sprites.push_back(sprite_loader.edge_7_sprite.getGlobalBounds());
            } // Edge 7
            
            else if (level_1->level_1_terrain[y][x] == 'F')
            {
                sprite_loader.floor_sprite.setPosition(position);
                sprite_loader.render_tile_sprites.push_back(sprite_loader.floor_sprite);

                sf::FloatRect sprite = sprite_loader.floor_sprite.getGlobalBounds();

                // Draw selection square
                if(sprite.contains(mouse_position) && abs(mouse_position.x - CENTER_X) < PLAYER_REACH
                    && abs(mouse_position.y - CENTER_Y) < PLAYER_REACH)
                {
                    sprite_loader.selection_sprite.setPosition(position);
                    sprite_loader.render_tile_sprites.push_back(sprite_loader.selection_sprite);
                    sprite_loader.mouse_pos_x = x;
                    sprite_loader.mouse_pos_y = y;
                }
            } // Floor 1 
            else if (level_1->level_1_terrain[y][x] == 'L')
            {
                sprite_loader.floor2_sprite.setPosition(position);
                sprite_loader.render_tile_sprites.push_back(sprite_loader.floor2_sprite);

                sf::FloatRect sprite = sprite_loader.floor2_sprite.getGlobalBounds();
                if(sprite.contains(mouse_position) && abs(mouse_position.x - CENTER_X) < PLAYER_REACH
                    && abs(mouse_position.y - CENTER_Y) < PLAYER_REACH)
                {
                    sprite_loader.selection_sprite.setPosition(position);
                    sprite_loader.render_tile_sprites.push_back(sprite_loader.selection_sprite);
                    sprite_loader.mouse_pos_x = x;
                    sprite_loader.mouse_pos_y = y;
                }
            } // Floor 2
            draw_level_objects(window, sprite_loader, x, y, position, manager);
        }
    }
}

// Render the npcs.
void Renderer::render_npc(sf::RenderWindow& window, Sprite_loader& sprite_loader, Dialogue_manager& manager)
{
    sf::Vector2f new_position = manager.spork->position;
    new_position += world_offset;
    sprite_loader.old_man_npc.setPosition(new_position);
    window.draw(sprite_loader.old_man_npc);
    collision_sprites.push_back(sprite_loader.old_man_npc.getGlobalBounds());
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
        if(sprite.getGlobalBounds().contains(mouse_position) && !cursor_drawn)
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
    if(player_inventory.draw_progress)
    {
        window.draw(sprite_loader.progress_bar_sprite);
        player_inventory.draw_progress = false;
        cursor_drawn = true;
    }
    if(!cursor_drawn)
    {
        sprite_loader.default_mouse_icon_sprite.setPosition(mouse_position.x-8, mouse_position.y-8);
        window.draw(sprite_loader.default_mouse_icon_sprite);
    }
    
}





