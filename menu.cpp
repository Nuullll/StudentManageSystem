// menu.cpp

#include "menu.h"

bool HighlightPrint(std::string text)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle == 0)
        return false;
    BOOL ret = SetConsoleTextAttribute(handle, WORD(9));
    cout << text;
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
    system("cls");
    for (int i = 0; i < options_text.size(); i++)
    {
        if (i == index)
        {
            HighlightPrint(options_text[i] + '\n');
            continue;
        }
        std::cout << options_txt[i] << std::endl;
    }
}