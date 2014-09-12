// main.h

#include <string>
#include "token.h"
#include "menu.h"

void Title();
void ClearScreen();
std::string GetPass();
Token Login();
std::vector<MenuNode> InitialMenu(int identity);