// main.cpp

#include <iostream>
#include <string>
#include <conio.h>
#include "file.h"
#include "token.h"
#include <stdlib.h>

void Title()
{
	std::cout << "学生成绩管理系统 v1.60.0\n\n";
}

void ClearScreen()
{
    system("cls");
    Title();
}

Token Login()
{
    std::cout << "请登录\n";
    std::string id, pwd;
    std::cout << "请输入您的学号(工号): ";
    std::cin >> id;
    std::cout << "请输入您的密码: ";
    char tmp;
    while ((tmp = getch()) != 13)
    {
        pwd.append(1, tmp);
        std::cout << '*';
    }
    std::cout << '\n';
    return Token(id, pwd);
}


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
            std::cout << "学号(工号)或密码错误! 请重新输入!\n";
        }
    }

	return 0;
}