#include "game_window.h"
#include <cmath>

// Background color
const sf::Color BG_color(124, 116, 97);

// This is where the window is created.
void game_window::open_game_window()
{

    current_scene = &level_1;
    current_scene->current_level = current_scene->level_1;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Bruh");
    game_window_loop(window);
}

// This is where the updates of the window are called.
void game_window::game_window_loop(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        game_window_update(window);
        game_window_draw(window);
    }
}

// Draw objects.
void game_window::game_window_draw(sf::RenderWindow& window)
{
    window.clear(BG_color);

    // UI elements.
    window.draw(current_scene->sprite_loader.coin_sprite);
    window.draw(current_scene->sprite_loader.coin_sprite);

    // Draw level.
    current_scene->draw_level(window);
    current_scene->render_objects(window);

    // Update player money.
    std::string player_money_string = std::to_string(player_money);
    player_money_text.setString(player_money_string);

    // Draw player money
    window.draw(player_money_text);

    // Display window.
    window.display();
}

// Update objects and events.
void game_window::game_window_update(sf::RenderWindow& window)
{
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window.close();
    }
    // Calculate delta time
    sf::Time deltaTime = delta_clock.restart();

    // Update game logic based on delta time
    float deltaTimeSeconds = deltaTime.asSeconds();

    // Move player.
    current_scene->move_player(deltaTimeSeconds);

    // Sprite frame update
    current_scene->update_sprites(frame_clock, window);
}



