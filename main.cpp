// main.cpp

#include "main.h"
#include <iostream>
#include <conio.h>
#include "user.h"
#include "file.h"
#include "token.h"
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    Title();
    std::vector<User*> users;
    users = ReadUsers("./data");
    Token tmp;
    User* user;
    while (True)
    {
        tmp(Login());
        if ((user = tmp.auth(users)) != NULL)
        {
            std::cout << "登录成功!\n";
            std::cout << "欢迎";
            user->print();
            break;
        }
        else
        {
            ClearScreen();
            std::cout << "学号(工号)或密码错误! 重新输入? \n";
            std::cout << "[回车继续, q退出系统] ";
            if (getch() == 'q')
            {
                std::cout << "再见! \n";
                return 0;
            }
        }
    }

    return 0;
}


void Title()
{
	std::cout << "学生成绩管理系统 v1.60.0\n\n";
}

void ClearScreen()
{
    system("cls");
    Title();
}

std::string GetPass()
{
    std::string pwd;
    char tmp;
    while ((tmp = getch()) != 13)
    {
        pwd.append(1, tmp);
        std::cout << '*';
    }
    std::cout << '\n';
    return pwd;
}

Token Login()
{
    std::cout << "请登录\n";
    std::string id, pwd;
    std::cout << "请输入您的学号(工号): ";
    std::cin >> id;
    std::cout << "请输入您的密码: ";
    pwd = GetPass();
    return Token(id, pwd);
}

std::vector<MenuNode> InitialMenu(int identity)
{
    std::vector<MenuNode> menus;
    switch (identity)
    {
        case ADMINISTRATOR:
        {
            MenuNode top_menu, manager_menu, user_menu;
            top_menu.previous = &top_menu;
            top_menu.append("用户管理", &manager_menu);
            top_menu.append("个人中心", &user_menu);
            
        }
    }
}