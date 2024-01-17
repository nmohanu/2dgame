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
    Item* weed = new Item; 
    

    std::vector<Item*> items;
    int hotbar[9] = {};

    Inventory()
    {
        weed->ID = 001;
        items.push_back(weed);
    }

    ~Inventory()
    {
        delete weed;
    }
};


