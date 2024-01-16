#include <iostream>
#include "../sprite_management/sprite_animation_manager.h"

struct Item
{
    std::string name;
    int amount = 0;
};

struct Inventory
{
    Item* weed = new Item; 
    std::vector<Item*> items;

    Inventory()
    {
        items.push_back(weed);
    }

    ~Inventory()
    {
        delete weed;
    }
};


