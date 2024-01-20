#ifndef mechanics

#include <cmath>
#include "items.h"

const int TILE_SIZE = 16;

void set_npc_locations(sf::Vector2f world_offset, Dialogue_manager& manager);

// Save all sprites for which collision should be checked.

void clean_up(std::vector<sf::FloatRect>& collision_sprites, std::vector<sf::Sprite>& clickable_sprites);

void move_player(float deltaTimeSeconds, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, sf::Vector2f& original_world_position, std::vector<sf::FloatRect>& collision_sprites, Sprite_loader& sprite_loader);

sf::Vector2f get_velocity(float deltaTimeSeconds);

bool check_collision(std::vector<sf::FloatRect>& collision_sprites, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, Sprite_loader& sprite_loader);

void handle_clicks(sf::RenderWindow& window, sf::Event& event, sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Dialogue_manager& manager, Level& level, Inventory& inventory, bool click);

void update_world(sf::RenderWindow& window, Sprite_loader& sprite_loader, Level& level, sf::Clock& game_clock);

void update_hotbar(Sprite_loader& sprite_loader, Inventory& inventory);

void update_npc_locations(Dialogue_manager& manager, sf::Vector2f& world_offset, float deltatime);

// std::vector<Path_Node> generate_npc_path_nodes(sf::Vector2f& current_position, sf::Vector2f& goal_position, Dialogue_manager& manager, NPC& npc, sf::Vector2f& world_offset);

sf::Vector2f get_tile_cords(int x, int y, sf::Vector2f& world_offset, Dialogue_manager& manager);

sf::Vector2f get_tile_cords(int x, int y, sf::Vector2f& world_offset, Dialogue_manager& manager);

void get_xy_cord(sf::Vector2f position, int& xcord, int& ycord, sf::Vector2f& world_offset, Dialogue_manager& manager);

bool is_free(Dialogue_manager& manager, int x, int y);

bool look_around(std::vector<Path_Node*>& path, bool& is_finished, Path_Node& parent, int goal_x, int goal_y, std::vector<Path_Node*>& board, Dialogue_manager& manager, Path_Node& winner);

// Hotbar render positions.
const sf::Vector2f hotbar_item_1_pos(SCREEN_WIDTH/2-(154)*INV_SCALE/2 + 1*INV_SCALE, SCREEN_HEIGHT-18*INV_SCALE - 20);

std::vector<Path_Node*> generate_npc_path(sf::Vector2f& current_position, sf::Vector2f& goal_position, Dialogue_manager& manager, NPC& npc, sf::Vector2f& world_offset);




#endif