// menu.h

#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <vector>

bool HighlightPrint(std::string text);

struct MenuNode
{
    std::vector<std::string> options_text;
    std::vector<std::string> options_target;
    MenuNode* previous;
    void append(std::string text, MenuNode* target);
    void show(int index = 0);
};

