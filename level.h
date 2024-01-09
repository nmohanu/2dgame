#include <vector>
#pragma once

struct Level
{

    Level(int, int, int);

    const int LEVEL_WIDTH;
    const int LEVEL_HEIGHT;
    int level;
    char level_1_terrain[8][8] =
    {{'0', '1', '1', '1', '1', '1', '1', '2'}, 
     {'7', 'F', 'L', 'F', 'L', 'F', 'L', '3'},
     {'7', 'L', 'F', 'L', 'F', 'L', 'F', '3'},
     {'7', 'F', 'L', 'F', 'L', 'F', 'L', '3'},
     {'7', 'L', 'F', 'L', 'F', 'L', 'F', '3'},
     {'7', 'F', 'L', 'F', 'L', 'F', 'L', '3'},
     {'7', 'L', 'F', 'L', 'F', 'L', 'F', '3'},
     {'6', '5', '5', '5', '5', '5', '5', '4'}};
};
