#include "npc_events.h"

void Dialogue_manager::process_dialogues(sf::Event& event, Sprite_loader& sprite_loader)
{
    for(Dialogue &current_dialogue : this->dialogues)
    {
        if(current_dialogue.in_dialogue && current_dialogue.print_next_message)
        {
            current_dialogue.render_dialogue_next_message(sprite_loader, current_dialogue);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            e_was_pressed = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && e_was_pressed)
        {
            current_dialogue.print_next_message = true;
            e_was_pressed = false;
        }
    }
}

void Dialogue_manager::render_dialogue_frame(sf::RenderWindow& window, Sprite_loader& sprite_loader)
{
    for(Dialogue &current_dialogue : this->dialogues)
    {
        if(current_dialogue.in_dialogue)
        {
            window.draw(sprite_loader.dialogue_sprite);
            window.draw(*current_dialogue.message);
        }
    }
}

void Dialogue_manager::initialize_dialogues()
{
    std::cout << "dialogues initialized \n";
    // SPORK's messages.
    this->spork_npc_dialogue.messages.push_back(Message("BOOO!!!!"));
    this->spork_npc_dialogue.messages.push_back(Message("Hehehe, just kidding..."));
    this->spork_npc_dialogue.messages.push_back(Message("Anyway... Welcome!"));
    this->spork_npc_dialogue.messages.push_back(Message("..."));
    this->spork_npc_dialogue.ID = "SPORK_1";
    this->spork_npc_dialogue.message = &message;
    this->dialogues.push_back(this->spork_npc_dialogue);

    // Second conversation with Spork
    this->spork_npc_dialogue2.messages.push_back(Message("What do you mean\nwhere are we?"));
    this->spork_npc_dialogue2.messages.push_back(Message("Hehehe, got you again."));
    this->spork_npc_dialogue2.messages.push_back(Message("Don't worry, it's \n completely normal for \n newcomers to be confused."));
    this->spork_npc_dialogue2.messages.push_back(Message("Anyway... My name is Spork."));
    this->spork_npc_dialogue2.ID = "SPORK_2";
    this->spork_npc_dialogue2.message = &message;
    this->spork_npc_dialogue2.previous = &spork_npc_dialogue;
    this->dialogues.push_back(this->spork_npc_dialogue2);

    // std::cout << this->dialogues.size() << '\n';
    // std::cout << this->spork_npc_dialogue2.previous << '\n';
}

void Dialogue::render_dialogue_next_message(Sprite_loader& sprite_loader, Dialogue& dialogue)
{
    if(current_message < this->messages.size())
    {
        std::cout << this->messages[current_message].message << std::endl;
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
        std::cout << "finished dialogue 1" << ": " << this << '\n';
    }
}