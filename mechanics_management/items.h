#include <iostream>
#include "../sprite_management/sprite_animation_manager.h"

struct Item
{
    std::string name;
    int amount = 0;
};

struct Inventory
{
    Item* weed = new Item;  // No need for dynamic allocation here
    std::vector<Item*> items;

    Inventory()
    {
        items.push_back(weed);
    }

    ~Inventory()
    {
        // Don't forget to free the allocated memory in the destructor
        delete weed;
    }
};


