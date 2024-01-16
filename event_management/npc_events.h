#include <vector>
#include <iostream>

#include "../level_management/level.h"


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
    sf::Text* message;
    bool finished = false;
    
    std::string ID;
    std::vector<Message> messages;
    int current_message = 0;
    void render_dialogue_next_message(Sprite_loader& sprite_loader, Dialogue& dialogue);
    bool in_dialogue = false;
    std::string message_to_display;
    Dialogue* next = nullptr;
};

struct Dialogue_manager
{
    sf::Text message;
    
    bool e_was_pressed = false;
    std::vector<Dialogue*>* spork_dialogues = new std::vector<Dialogue*>;
    void process_dialogues(sf::Event& event, Sprite_loader& sprite_loader);
    void initialize_dialogues();
    void render_dialogue_frame(sf::RenderWindow& window, Sprite_loader& sprite_loader);
    

    Dialogue_manager()
    {
        initialize_dialogues();
    }

    // Dialogues
    Dialogue* spork_npc_dialogue = new Dialogue;
    Dialogue* spork_npc_dialogue2 = new Dialogue;
    Dialogue* current = spork_npc_dialogue;

};

