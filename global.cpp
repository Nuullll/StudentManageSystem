// global.cpp

#include "global.h"
#include "file.h"

std::vector<User*> users;   // 所有用户基类指针.
std::vector<Administrator> admins;  
std::vector<Teacher> teachers;
std::vector<Student> students;
std::vector<TeachingAssistant> tas; // ta: teachingassistant
std::vector<Course> courses;

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
	int id;
    std::string pwd;
    std::cout << "请输入您的学号(工号): ";
    std::cin >> id;
    std::cout << "请输入您的密码: ";
    pwd = GetPass();
    return Token(id, pwd);
}

void ClearScreen()
{
    system("cls");
    Title();
}

void Exit()
{
    ClearScreen();  // 清屏
    std::cout << "确认退出? [y/n]" << std::endl;
    char ch = getch();
    if (ch == 'y' || ch == 'Y')
    {
        std::cout << "再见!" << std::endl;
        exit(1);
    }
}

void Title()
{
	HighlightPrint("学生成绩管理系统 v1.60.0\n\n");
}

void UpdateFiles()
{
    // 根据全局vector更新文件.
    WriteAdmins();
    WriteTeachers();
    WriteStudents();
    WriteTAs();    
}

void UpdateUsers()
{
    // 从文件读取用户信息.
    ReadAdmins();
    ReadTeachers();
    ReadStudents();
    ReadTAs();
	ReadUsers();

}

int Find(std::vector<User*> v, int id)
{
    for (int i = 0; i < v.size(); i++)
    {
		if (v[i]->id() == id)
            return i;
    }
    return -1;
}
