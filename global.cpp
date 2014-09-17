// global.cpp

#include "global.h"
#include "course.h"
#include "file.h"

std::vector<User*> users;   // 所有用户基类指针.
std::vector<Administrator> admins;  
std::vector<Teacher> teachers;
std::vector<Student> students;
std::vector<TeachingAssistant> tas; // ta: teachingassistant
std::vector<Course> courses;

int GetX()
{
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &pBuffer);
	return pBuffer.dwCursorPosition.X;
}

int GetY()
{
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &pBuffer);
	return pBuffer.dwCursorPosition.Y;
}

void GotoXY(int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;                            
    HANDLE    hConsoleOut;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
    csbiInfo.dwCursorPosition.X = x;                                    
    csbiInfo.dwCursorPosition.Y = y;                                    
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition); 
}

std::string GetPass()
{
    std::string pwd;
    char tmp;
    while ((tmp = getch()) != 13)
    {
		if (tmp == 8)	// backspace
		{
			if (pwd.size() == 0)
				continue;
			pwd.erase(pwd.end() - 1);	// 删除末位
			int x = GetX(), y = GetY();	// 清掉屏幕上的一个'*'
			GotoXY(x - 1, y);
			std::cout << ' ';
			GotoXY(x - 1, y);
			continue;
		}
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
	WriteCourses();
}

void UpdateUsers()
{
    // 从文件读取用户信息.
    ReadAdmins();
    ReadTeachers();
    ReadStudents();
    ReadTAs();
	ReadUsers();
	ReadCourses();
	HighlightPrint("加载完毕! \n");
	getch();
	return;
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
