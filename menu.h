// menu.h

#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <vector>
#include "user.h"

bool HighlightPrint(std::string text);

struct MenuNode
{
    std::vector<std::string> options_text;
    std::vector<MenuNode*> options_target;
    MenuNode* previous;
    void append(std::string text, MenuNode* target);
    void show(int index);
};

