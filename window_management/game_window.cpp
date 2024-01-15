#include "game_window.h"
#include <cmath>

// Background color
const sf::Color BG_color(124, 116, 97);

// This is where the window is created.
void game_window::open_game_window()
{
    
    current_scene = &level_1;
    current_scene->current_level = current_scene->level_1;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Bruh", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    game_window_loop(window);
    ladybug.play();
    
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
    // SFML stuffs -------------------------------------------------

    // Clear window
    window.clear(BG_color);

    // Render world ------------------------------------------------

    // Call renderer and render the world.
    current_scene->render_everything(window, mouse_position, sprite_loader, *player_inventory);

    // Render UI elements ------------------------------------------

    // Draw player money
    window.draw(player_money_text);

    // Draw dialogue frame
    dialogue_manager->render_dialogue_frame(window, sprite_loader);

    // Final SFML stuffs -------------------------------------------
    // Display window.
    window.display();
}

// Update objects and events.
void game_window::game_window_update(sf::RenderWindow& window)
{
    // Get mouse location
    mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

    // Update player money.
    std::string player_money_string = std::to_string(player_money);
    player_money_text.setString(player_money_string);

    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window.close();
        // Handle clicks
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            handle_clicks(window, event, mouse_position, sprite_loader, *dialogue_manager, *current_scene->level_1, *player_inventory);
        }
        
    }
    // Calculate delta time
    sf::Time deltaTime = delta_clock.restart();

    // Update game logic based on delta time
    float deltaTimeSeconds = deltaTime.asSeconds();

    update_world(window, sprite_loader, *current_scene->level_1, *game_clock);

    // Sprite frame update
    current_scene->animation_manager.update_sprites(frame_clock, window, deltaTimeSeconds, sprite_loader);

    // Move player.
    current_scene->player_movement(deltaTimeSeconds, sprite_loader);

    dialogue_manager->process_dialogues(event, sprite_loader);
    
}



