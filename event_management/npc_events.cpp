#include "npc_events.h"

void Dialogue_manager::process_dialogues(sf::Event& event, Sprite_loader& sprite_loader)
{   
    if(current != nullptr)
    {
        if(current->in_dialogue && current->print_next_message)
        {
            current->render_dialogue_next_message(sprite_loader, *current);
            std::cout << "VECTOR MEM: " << &spork_dialogues << std::endl;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            e_was_pressed = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && e_was_pressed)
        {
            current->print_next_message = true;
            e_was_pressed = false;
        }
    }
    
    
}

void Dialogue_manager::render_dialogue_frame(sf::RenderWindow& window, Sprite_loader& sprite_loader)
{
    for(Dialogue* current_dialogue : *this->spork_dialogues)
    {
        if(current_dialogue->in_dialogue)
        {
            window.draw(sprite_loader.dialogue_sprite);
            window.draw(*current_dialogue->message);
        }
    }
}

void Dialogue_manager::initialize_dialogues()
{
    std::cout << "dialogues initialized \n";
    // SPORK's messages.
    this->spork_npc_dialogue->messages.push_back(Message("BOOO!!!!"));
    this->spork_npc_dialogue->messages.push_back(Message("Hehehe, just kidding..."));
    this->spork_npc_dialogue->messages.push_back(Message("Anyway... Welcome!"));
    this->spork_npc_dialogue->messages.push_back(Message("..."));
    this->spork_npc_dialogue->ID = "SPORK_1";
    this->spork_npc_dialogue->message = &message;
    

    // Second conversation with Spork
    this->spork_npc_dialogue2->messages.push_back(Message("What do you mean\nwhere are we?"));
    this->spork_npc_dialogue2->messages.push_back(Message("Hehehe, got you\nagain."));
    this->spork_npc_dialogue2->messages.push_back(Message("Don't worry, it's\ncompletely normal\nfor newcomers\nto be confused."));
    this->spork_npc_dialogue2->messages.push_back(Message("Anyway... \nMy name is Spork."));
    
    this->spork_npc_dialogue2->ID = "SPORK_2";
    this->spork_npc_dialogue2->message = &message;


    this->spork_npc_dialogue->next = spork_npc_dialogue2;

    this->spork_dialogues->push_back(spork_npc_dialogue);
    this->spork_dialogues->push_back(spork_npc_dialogue2);

    std::cout << "INIT MEMORY 1 " << &spork_npc_dialogue << '\n';
    std::cout << "INIT MEMORY 2 " << &spork_npc_dialogue2 << '\n';

    // std::cout << this->dialogues.size() << '\n';
    // std::cout << this->spork_npc_dialogue2.previous << '\n';
    std::cout << "VECTOR MEM: " << &spork_dialogues << std::endl;
    for(Dialogue* dialogue : *spork_dialogues)
    {
        std::cout << "DIALOGUE MEM: " << &dialogue << std::endl;
    }
}

void Dialogue::render_dialogue_next_message(Sprite_loader& sprite_loader, Dialogue& dialogue)
{
    if(current_message < this->messages.size())
    {
        std::cout << '\n' << this->messages[current_message].message << std::endl;
        this->message_to_display = this->messages[current_message].message;
        this->message->setString(message_to_display);
        this->current_message++;
        this->print_next_message = false;
    }
    else
    {
        this->in_dialogue = false;
        this->finished = true;
        this->current_message = 0;
        std::cout << "finished dialogue 1" << ": " << this->finished << '\n';
    }
}