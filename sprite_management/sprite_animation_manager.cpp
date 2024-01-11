#include "sprite_animation_manager.h"

// Animation logic.
void Animation_manager::update_sprites(sf::Clock& timer, sf::RenderWindow& window, float deltaTimeSeconds)
{
    
    if((int) timer.getElapsedTime().asMilliseconds()%200 > CHANGE_FRAME)
    {
        tick++;
        timer.restart();
        
    }
    tick %= 10;
    frame_offset = tick;
    frame_offset *= 16;

    change_sprite_bounds(timer);
}

// Actually change the bounds of the sprite.
void Animation_manager::change_sprite_bounds(sf::Clock& timer)
{
    if(frame_offset != last_frame_offset)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->sprite_loader.player_sprite.setTextureRect(sf::IntRect(80, frame_offset, 16, 16));
            if(yawn || blink)
            {
                animation_frame_counter++;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->sprite_loader.player_sprite.setTextureRect(sf::IntRect(64, frame_offset, 16, 16));
            if(yawn || blink)
            {
                animation_frame_counter++;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->sprite_loader.player_sprite.setTextureRect(sf::IntRect(48, frame_offset, 16, 16));
            if(yawn || blink)
            {
                animation_frame_counter++;
            }
        }
        else if(yawn)
        {
            this->sprite_loader.player_sprite.setTextureRect(sf::IntRect(32, frame_offset, 16, 16));
            animation_frame_counter++;
        }
        else if(blink)
        {
            this->sprite_loader.player_sprite.setTextureRect(sf::IntRect(16, frame_offset, 16, 16));
            animation_frame_counter++;
        }
        else
        {
            this->sprite_loader.player_sprite.setTextureRect(sf::IntRect(0, frame_offset, 16, 16));
            
        }
        last_frame_offset = frame_offset;
    }
    

    // Check if it's time for player character to blink or yawn.
    if(idle_animation_timer.getElapsedTime().asMilliseconds() > 10000 && frame_offset == 0)
    {
        blink = true;
        idle_animation_timer.restart();
    }
    else if(idle_animation2_timer.getElapsedTime().asMilliseconds() > 50000 && frame_offset == 0)
    {
        yawn = true;
        idle_animation2_timer.restart();
    }

    if(animation_frame_counter >= 9)
    {
        yawn = false;
        blink = false;
        animation_frame_counter = 0;
    }
}