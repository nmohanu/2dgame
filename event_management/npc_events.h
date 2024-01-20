#include <vector>
#include <iostream>

#include "../level_management/level.h"

struct Path_Node
{
    sf::Vector2f position;
    int x;
    int y;
    bool is_visited = false;
    Path_Node* parent = nullptr;
    Path_Node(sf::Vector2f position) : position(position)
    {
        
    }
    Path_Node(int x, int y) : x(x), y(y)
    {
        
    }
    Path_Node()
    {
        
    }
};

struct Path
{
    std::vector<Path_Node*> path = {};
};

struct Walk_Event
{
    sf::Vector2f walk_to_pos;
    Walk_Event(sf::Vector2f walk_to_pos) : walk_to_pos(walk_to_pos)
    {

    }
};

struct NPC
{
    std::string name;
    sf::Vector2f position;
    sf::Vector2i position_int;
    sf::Vector2f goal_position;
    Path* path = nullptr;
    Walk_Event* current_event = nullptr;
    sf::Vector2f next_destination_vec;
    int next_destination_x;
    int next_destination_y;
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
    sf::Text* message = nullptr;
    bool finished = false;
    
    std::string ID;
    std::vector<Message> messages;
    int current_message = 0;
    void render_dialogue_next_message(Sprite_loader& sprite_loader, Dialogue& dialogue);
    bool in_dialogue = false;
    std::string message_to_display;
    Dialogue* next = nullptr;
    Walk_Event* walk_to = nullptr;
    NPC* npc = nullptr;
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
        
    }

    // Dialogues
    Dialogue* spork_npc_dialogue = new Dialogue;
    Dialogue* spork_npc_dialogue2 = new Dialogue;
    Dialogue* current = spork_npc_dialogue;

};

                                                                        