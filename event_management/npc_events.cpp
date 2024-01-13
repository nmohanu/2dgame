#include "npc_events.h"

void Dialogue_manager::process_dialogues(sf::RenderWindow& window, sf::Event& event)
{
    for(Dialogue &current_dialogue : this->dialogues)
    {
        if(current_dialogue.in_dialogue && current_dialogue.print_next_message)
        {
            current_dialogue.render_dialogue_next_message(window);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            e_was_pressed = true;
        }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && e_was_pressed)
        {
            current_dialogue.print_next_message = true;
            e_was_pressed = false;
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
    this->dialogues.push_back(this->spork_npc_dialogue);
    std::cout << this->dialogues.size() << " dialogues in the dialogues vector at init." << '\n';
}

void Dialogue::render_dialogue_next_message(sf::RenderWindow& window)
{
    if(current_message < this->messages.size())
    {
        std::cout << this->messages[current_message].message << std::endl;

        //window.draw();


        current_message++;
        this->print_next_message = false;
    }
}