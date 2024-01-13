#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>


struct NPC
{
    std::string name;
};

struct Message
{
    Message(std::string message)
    {
        this->message = message;
    }
    std::string message;
    NPC* npc = new NPC;
};

struct Dialogue
{
    bool print_next_message = true;
    std::string ID;
    std::vector<Message> messages;
    int current_message = 0;
    void render_dialogue_next_message(sf::RenderWindow& window);
    bool in_dialogue = false;
};

struct Dialogue_manager
{
    Dialogue spork_npc_dialogue;
    std::vector<Dialogue> dialogues;
    void process_dialogues(sf::RenderWindow& window, sf::Event& event);
    void initialize_dialogues();
    bool e_was_pressed = false;
    Dialogue_manager()
    {
        initialize_dialogues();
    }
};

