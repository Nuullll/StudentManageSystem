// menu.cpp

#include "menu.h"
#include "global.h"

bool HighlightPrint(std::string text)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle == 0)
        return false;
    BOOL ret = SetConsoleTextAttribute(handle, WORD(9));
    std::cout << text;
    ret = SetConsoleTextAttribute(handle, WORD(7));
    return (ret == true);
}

void MenuNode::append(std::string text, MenuNode* target)
{
    options_text.push_back(text);
    options_target.push_back(target);
}

void MenuNode::show(int index)
{
    ClearScreen();
    for (int i = 0; i < options_text.size(); i++)
    {
        if (i == index)
        {
            HighlightPrint(options_text[i] + '\n');
            continue;
        }
        std::cout << options_text[i] << std::endl;
    }
}