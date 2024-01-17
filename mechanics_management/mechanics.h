#ifndef mechanics

#include <cmath>
#include "items.h"

const int TILE_SIZE = 16;

// Save all sprites for which collision should be checked.\

void clean_up(std::vector<sf::Sprite>& collision_sprites, std::vector<sf::Sprite>& clickable_sprites);

void move_player(float deltaTimeSeconds, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, sf::Vector2f& original_world_position, std::vector<sf::Sprite>& collision_sprites, Sprite_loader& sprite_loader);

sf::Vector2f get_velocity(float deltaTimeSeconds);

bool check_collision(std::vector<sf::Sprite>& collision_sprites, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, Sprite_loader& sprite_loader);

void handle_clicks(sf::RenderWindow& window, sf::Event& event, sf::Vector2f mouse_position, Sprite_loader& sprite_loader, Dialogue_manager& manager, Level& level, Inventory& inventory);

void update_world(sf::RenderWindow& window, Sprite_loader& sprite_loader, Level& level, sf::Clock& game_clock);

void update_hotbar(Sprite_loader& sprite_loader, Inventory& inventory);


// Hotbar render positions.
const sf::Vector2f hotbar_item_1_pos(SCREEN_WIDTH/2-(154)*INV_SCALE/2 + 1*INV_SCALE, SCREEN_HEIGHT-18*INV_SCALE - 20);




#endif