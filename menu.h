// menu.h
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <vector>

bool HighlightPrint(std::string text);

struct MenuNode
{
    std::vector<std::string> options_text;
    std::vector<MenuNode*> options_target;
    MenuNode* previous;
    void append(std::string text, MenuNode* target);
    void show(int index);
};

#endif