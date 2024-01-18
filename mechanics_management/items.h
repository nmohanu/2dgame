#include <iostream>
#include "../sprite_management/sprite_animation_manager.h"

struct Item
{
    std::string name;
    sf::Sprite sprite;
    int amount = 0;
    std::string ID;
    float ms_to_pick_up = 0.f;
};

struct Inventory
{
    // Declare item types.
    Item* leafs = new Item; 
    Item* tree1 = new Item; 
    Item* tree2 = new Item; 

    // Text for displaying item amount.
    sf::Text amount;
    sf::Font font;
    
    std::vector<Item*> items;
    std::string hotbar[9] = {"00000000","00000000","00000000","00000000","00000000","00000000","00000000","00000000"};

    sf::Clock progress_bar_clock;
    sf::Clock progress_x_clock;
    int progress_counter = 0;
    bool draw_progress = false;

    int current_selection = 0;

    Inventory(Sprite_loader& sprite_loader)
    {
        leafs->ID = "0000LEAF";
        leafs->sprite = sprite_loader.weed_sprite;
        leafs->ms_to_pick_up = 1024.f;
        items.push_back(leafs);

        tree1->ID = "000TREE1";
        tree1->sprite = sprite_loader.tree1_sprite;
        tree1->ms_to_pick_up = 5120.f;
        items.push_back(tree1);

        tree2->ID = "000TREE2";
        tree2->sprite = sprite_loader.tree2_sprite;
        tree2->ms_to_pick_up = 2610.f;
        items.push_back(tree2);
        

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
        delete leafs;
    }
};


