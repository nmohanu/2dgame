#include <vector>
#include <iostream>

#include "../level_management/level.h"

struct Path_Node
{
    sf::Vector2f position;
    int x;
    int y;
    bool is_visited;
    Path_Node* parent;
    Path_Node(sf::Vector2f position) : position(position)
    {
        
    }
    Path_Node(int x, int y) : x(x), y(y)
    {
        
    }
};

struct Path
{
    std::vector<Path_Node*> path;
};

struct NPC
{
    std::string name;
    sf::Vector2f position;
    sf::Vector2f goal_position;
    Path* path = nullptr;
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
    Level* current_level = nullptr;

    sf::Text message;
    
    bool e_was_pressed = false;
    std::vector<Dialogue*>* spork_dialogues = new std::vector<Dialogue*>;
    void process_dialogues(sf::Event& event, Sprite_loader& sprite_loader);
    void initialize_dialogues();
    void render_dialogue_frame(sf::RenderWindow& window, Sprite_loader& sprite_loader);
    
    NPC* spork = new NPC;
    std::vector<NPC*>* npcs= new std::vector<NPC*>;

    Dialogue_manager()
    {
        initialize_dialogues();
        
        spork->position = sf::Vector2f(CENTER_X-(16 * SCALE_FACTOR_X)/2 + 24*SCALE_FACTOR_X, CENTER_Y-(16 * SCALE_FACTOR_X)/2);
        spork->goal_position = spork->position;
        npcs->push_back(spork);
    }

    // Dialogues
    Dialogue* spork_npc_dialogue = new Dialogue;
    Dialogue* spork_npc_dialogue2 = new Dialogue;
    Dialogue* current = spork_npc_dialogue;

};

