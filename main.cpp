// main.cpp

#include <iostream>
#include <string>
#include <conio.h>
#include "file.h"
#include "token.h"

void Welcome()
{
	std::cout << "学生成绩管理系统 v1.60.0\n\n";
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
	welcome();
    
	return 0;
}