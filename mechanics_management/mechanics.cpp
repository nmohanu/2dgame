#include "mechanics.h"
#include <iostream>
#include <cmath>


void clean_up(std::vector<sf::FloatRect>& collision_sprites, std::vector<sf::Sprite>& clickable_sprites)
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

void move_player(float deltaTimeSeconds, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, sf::Vector2f& original_world_position, std::vector<sf::FloatRect>& collision_sprites, Sprite_loader& sprite_loader)
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



bool check_collision(std::vector<sf::FloatRect>& collision_sprites, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, Sprite_loader& sprite_loader)
{
    sf::FloatRect player_bounds = sprite_loader.player_sprite.getGlobalBounds();

    sf::FloatRect adjustedPlayerBounds(
        player_bounds.left + 20,      // Adjust left
        player_bounds.top + 46,       // Adjust top
        player_bounds.width - 40,     // Adjust width
        player_bounds.height - 60     // Adjust height
    );

    
    // Check collision with each wall sprite
    for (const sf::FloatRect& COL : collision_sprites)
    {
        sf::FloatRect new_position = COL;
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

void handle_clicks(sf::RenderWindow& window, sf::Event& event,  sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Dialogue_manager& manager, Level& level, Inventory& player_inventory, bool click)
{
    // Only check once after a click.
    if(event.mouseButton.button == sf::Mouse::Left && click)
    {
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

        player_inventory.progress_bar_clock.restart();
        player_inventory.progress_x_clock.restart();
        player_inventory.progress_counter = 0;
        player_inventory.draw_progress = false;
    }
    // Button is clicked but needs to be checked each frame.
    else
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && level.level_1_objects[sprite_loader.mouse_pos_y][sprite_loader.mouse_pos_x] != "00000000")
        {
            std::string tile_ID = level.level_1_objects[sprite_loader.mouse_pos_y][sprite_loader.mouse_pos_x];
            Item* item_clicked;

            // Figure out what item belongs to the clicked tile.
            for(Item* item: player_inventory.items)
            {
                if(item->ID == tile_ID)
                {
                    item_clicked = item;
                }
            }

            // Player is picking up.
            if(player_inventory.progress_bar_clock.getElapsedTime().asMilliseconds() > item_clicked->ms_to_pick_up)
            {
                level.level_1_objects[sprite_loader.mouse_pos_y][sprite_loader.mouse_pos_x] = '0';
                if(item_clicked != nullptr)
                {
                    item_clicked->amount++;

                    // Item is added to inventory.
                    if(item_clicked->amount == 1)
                    {
                        for(int i  = 0; i < 9; i++)
                        {
                            // Find first empty spot.
                            if(player_inventory.hotbar[i] == "00000000")
                            {
                                // Set spot to item code.
                                player_inventory.hotbar[i] = tile_ID;
                                
                                return;
                                
                            }
                        }
                    }
                }
                player_inventory.progress_bar_clock.restart();
                player_inventory.progress_x_clock.restart();
                player_inventory.progress_counter = 0;
            }
            else
            {
                if(player_inventory.progress_x_clock.getElapsedTime().asMilliseconds() >= item_clicked->ms_to_pick_up/16)
                {
                    player_inventory.progress_counter++;
                    if(player_inventory.progress_counter >= 15)
                    {
                        player_inventory.progress_counter = 0;
                    }
                    player_inventory.progress_x_clock.restart();
                }
                sprite_loader.progress_bar_sprite.setTextureRect(sf::IntRect(player_inventory.progress_counter*16, 32, 16, 16));
                sprite_loader.progress_bar_sprite.setPosition(mouse_position.x, mouse_position.y + 8*SCALE_FACTOR_X);
                player_inventory.draw_progress = true;
            }         
        }
        else if(level.level_1_objects[sprite_loader.mouse_pos_y][sprite_loader.mouse_pos_x] == "00000000")
        {
            player_inventory.progress_bar_clock.restart();
            player_inventory.progress_x_clock.restart();
            player_inventory.progress_counter = 0;
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

// Get the cords of a tile based on the x and y position relative to the map.
sf::Vector2f get_tile_cords(int x, int y, sf::Vector2f& world_offset, Dialogue_manager& manager)
{
    sf::Vector2f position(x * SCALE_FACTOR_X * TILE_SIZE + (SCREEN_WIDTH  - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR_X))/2 + manager.current_level->LEVEL_WIDTH*SCALE_FACTOR_X*TILE_SIZE/2,
                                  y * SCALE_FACTOR_Y * TILE_SIZE + (SCREEN_HEIGHT - (TILE_SIZE*TILE_SIZE*SCALE_FACTOR_Y))/2 + manager.current_level->LEVEL_HEIGHT*SCALE_FACTOR_Y*TILE_SIZE/2);
    position += world_offset;
    return position;
}

void get_xy_cord(sf::Vector2f position, int& xcord, int& ycord, sf::Vector2f& world_offset, Dialogue_manager& manager)
{

    // Subtract the world offset
    position -= world_offset;

    // Reverse the scaling and translation operations
    xcord = (float)(position.x - (SCREEN_WIDTH - (TILE_SIZE * TILE_SIZE * SCALE_FACTOR_X)) / 2 - manager.current_level->LEVEL_WIDTH * SCALE_FACTOR_X * TILE_SIZE / 2) / (SCALE_FACTOR_X * TILE_SIZE);
    ycord = (float)(position.y - (SCREEN_HEIGHT - (TILE_SIZE * TILE_SIZE * SCALE_FACTOR_Y)) / 2 - manager.current_level->LEVEL_HEIGHT * SCALE_FACTOR_Y * TILE_SIZE / 2) / (SCALE_FACTOR_Y * TILE_SIZE);

}

void update_npc_locations(Dialogue_manager& manager, sf::Vector2f& world_offset, float delta_time)
{
    for(NPC* npc : *manager.npcs)
    {
        if(npc->position != npc->goal_position)
        {
            if(npc->path == nullptr)
            {
                npc->path = new Path;
                npc->path->path = generate_npc_path(npc->position, npc->goal_position, manager, *npc, world_offset);
                if(&npc->path != nullptr && &npc->path->path != nullptr && npc->path->path[0]!= nullptr)
                {
                    npc->next_destination_vec = npc->path->path[npc->path->path.size()-1]->position;
                }
                
                npc->next_destination_x = npc->path->path[npc->path->path.size()-1]->x;
                npc->next_destination_y = npc->path->path[npc->path->path.size()-1]->y;
            }
            else if(npc->position == npc->next_destination_vec)
            {
                npc->path->path[npc->path->path.size()-1]->is_visited = true;
                for(int i = npc->path->path.size()-1; i > 0; i--)
                {
                    if(npc->path->path[i] != nullptr && !npc->path->path[i]->is_visited)
                    {
                        npc->next_destination_vec = npc->path->path[i]->position;
                        npc->next_destination_x = npc->path->path[i]->x;
                        npc->next_destination_y = npc->path->path[i]->y;
                    }
                }
            }
            float move_distance = 20.f * PLAYER_SPEED * delta_time;
            if(&npc->next_destination_vec != nullptr)
            {

                if(std::abs(npc->next_destination_vec.x - npc->position.x) > move_distance)
                {
                    npc->position.x += (npc->next_destination_vec.x > npc->position.x) ? move_distance : -move_distance;
                }
                else
                {
                    npc->position.x = npc->next_destination_vec.x;
                }
                if(npc->position.x == npc->next_destination_vec.x)
                {
                    if(std::abs(npc->next_destination_vec.y - npc->position.y) > move_distance)
                    {
                        npc->position.y += (npc->next_destination_vec.y > npc->position.y) ? move_distance : -move_distance;
                    }
                    else
                    {
                        npc->position.y = npc->next_destination_vec.y;
                    }
                }
            }
        }
    }
}

bool cast_collision(sf::Vector2f& current_position)
{
    
}

std::vector<Path_Node*> generate_npc_path(sf::Vector2f& current_position, sf::Vector2f& goal_position, Dialogue_manager& manager, NPC& npc, sf::Vector2f& world_offset)
{
    int start_x = npc.position_int.x;
    int start_y = npc.position_int.y;
    
    int goal_x = npc.current_event->walk_to_pos.x;
    int goal_y = npc.current_event->walk_to_pos.y;

    // get_xy_cord(current_position, start_x, start_y, world_offset, manager);

    int counter = 0;

    bool is_finished = false;
    
    std::vector<Path_Node*> path;
    std::vector<Path_Node*> board;

    std::vector<Path_Node*> winning_path;
    Path_Node *starting_node = new Path_Node;
    Path_Node *finish_node = new Path_Node;
    starting_node->x = start_x;
    starting_node->y = start_y;
    path.push_back(starting_node);

    for(int y = 0; y < manager.current_level->LEVEL_HEIGHT; y++)
    {
        for(int x = 0; x < manager.current_level->LEVEL_WIDTH; x++)
        {
            Path_Node* node = new Path_Node(x, y);
            board.push_back(node);
            if(y == start_y && x == start_x)
            {
                starting_node = node;
            }
            else if (y == goal_y &&  x == goal_x)
            {
                finish_node = node;
            }
        }
    }

    // std::vector<Path_Node> available = generate_npc_path_nodes(current_position, goal_position, manager, npc, world_offset);
    Path_Node winner;
    look_around(path, is_finished, *starting_node, goal_x, goal_y, board, manager, winner);
    if(&winner != nullptr)
    {
        Path_Node* walk = &winner;
        if(walk != nullptr)
        {
            while (walk->parent != nullptr && counter < 100)
            {
                Path_Node* new_walk = new Path_Node();
                new_walk->position = get_tile_cords(walk->x, walk->y, world_offset, manager);
                new_walk->x = walk->x;
                new_walk->y = walk->y;
                new_walk->is_visited = false;
                winning_path.push_back(new_walk);
                counter++;
                walk = walk->parent;
            }
        }
        
    }
    for(Path_Node* node : path)
    {
        if(node != nullptr)
            delete node;
    }
    for(Path_Node* node : board)
    {
        if(node != nullptr)
            delete node;
    }

    npc.goal_position = get_tile_cords(npc.goal_position.x, npc.goal_position.y, world_offset, manager);

    return winning_path;
}

void look_around(std::vector<Path_Node*>& path, bool& is_finished, Path_Node& parent, int goal_x, int goal_y, std::vector<Path_Node*>& board, Dialogue_manager& manager, Path_Node& winner)
{
    
    for(int i = -1; i < 1; i++)
    {
        for(int j = -1; j < 1; j++)
        {
            if(parent.x + j <= manager.current_level->LEVEL_WIDTH && parent.x + j >= 0 && parent.y + i <= manager.current_level->LEVEL_HEIGHT && parent.y + i >= 0
                && is_free(manager, parent.x + j, parent.y + i))
                {
                    // TO DO: CHECK IF X AND Y ARE ALREADY CHECKED.
                Path_Node* node = new Path_Node();

                if(&parent != nullptr)
                {
                    node->parent = &parent;
                
                    node->x = node->parent->x + j;
                    node->y = node->parent->y + i;
                }
                if(node->x == goal_x && node->y == goal_y)
                {
                    winner.x = node->x;
                    winner.y = node->y;
                    winner.parent = node->parent;
                    return;
                }
                bool is_visited = false;
                Path_Node* board_node;
                for(Path_Node* check_node : board)
                {
                    if(check_node->x == node->x && check_node->y == node->y)
                    {
                        board_node = check_node;
                    }
                }
                
                if(board_node != nullptr && !board_node->is_visited)
                {
                    node->is_visited = true;
                    board_node->is_visited = true;
                    path.push_back(node);
                    look_around(path, is_finished, *node, goal_x, goal_y, board, manager, winner);
                }
            }
        }
    }
}



/*
std::vector<Path_Node> generate_npc_path_nodes(sf::Vector2f& current_position, sf::Vector2f& goal_position, Dialogue_manager& manager, NPC& npc, sf::Vector2f& world_offset)
{
    std::vector<Path_Node> all_nodes;
    for(int y = 0; y < manager.current_level->LEVEL_HEIGHT; y++)
    {
        for(int x = 0; x < manager.current_level->LEVEL_WIDTH; x++)
        {
            if(manager.current_level->level_1_objects[y][x] != "00000000" || manager.current_level->level_1_objects[y][x] != "0000LEAF")
            {
                all_nodes.push_back(Path_Node(get_tile_cords(x, y, world_offset, manager)));
            }
        }
    }
    return all_nodes;
}
*/

bool is_free(Dialogue_manager& manager, int x, int y)
{
    return (manager.current_level->level_1_objects[y][x] == "00000000" || manager.current_level->level_1_objects[y][x] == "0000LEAF");
}