#ifndef mechanics
#include "../sprite_management/sprite_animation_manager.h"

const int TILE_SIZE = 16;

// Save all sprites for which collision should be checked.

void clean_up(std::vector<sf::Sprite>& collision_sprites, std::vector<sf::Sprite>& clickable_sprites);

void move_player(float deltaTimeSeconds, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, sf::Vector2f& original_world_position, std::vector<sf::Sprite>& collision_sprites, Sprite_loader& sprite_loader);

sf::Vector2f get_velocity(float deltaTimeSeconds);

bool check_collision(std::vector<sf::Sprite>& collision_sprites, sf::Vector2f& new_world_position, sf::Vector2f& world_offset, Sprite_loader& sprite_loader);


#endif