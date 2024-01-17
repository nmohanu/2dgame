#include <iostream>
#include "../sprite_management/sprite_animation_manager.h"

struct Item
{
    std::string name;
    int amount = 0;
    int ID;
};

struct Inventory
{
    // Declare item types.
    Item* weed = new Item; 

    // Text for displaying item amount.
    sf::Text amount;
    sf::Font font;
    
    std::vector<Item*> items;
    int hotbar[9] = {};

    Inventory()
    {
        weed->ID = 001;
        items.push_back(weed);

        // Text properties.
        amount.scale(0.1*INV_SCALE, 0.1*INV_SCALE);
        amount.setCharacterSize(100);

        if (!font.loadFromFile("../Assets/fonts/pixels.ttf")) 
        {
            // handle error if the font fails to load
            std::cout << "ERR\n";
        }
        amount.setFont(font);
    }

    ~Inventory()
    {
        delete weed;
    }
};


