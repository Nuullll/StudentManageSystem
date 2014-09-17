// global.cpp

#include "global.h"
#include "course.h"
#include "file.h"

std::vector<User*> users;   // �����û�����ָ��.
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
			pwd.erase(pwd.end() - 1);	// ɾ��ĩλ
			int x = GetX(), y = GetY();	// �����Ļ�ϵ�һ��'*'
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
    std::cout << "���¼\n";
	int id;
    std::string pwd;
    std::cout << "����������ѧ��(����): ";
    std::cin >> id;
    std::cout << "��������������: ";
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
    ClearScreen();  // ����
    std::cout << "ȷ���˳�? [y/n]" << std::endl;
    char ch = getch();
    if (ch == 'y' || ch == 'Y')
    {
        std::cout << "�ټ�!" << std::endl;
        exit(1);
    }
}

void Title()
{
	HighlightPrint("ѧ���ɼ�����ϵͳ v1.60.0\n\n");
}

void UpdateFiles()
{
    // ����ȫ��vector�����ļ�.
    WriteAdmins();
    WriteTeachers();
    WriteStudents();
    WriteTAs();
	WriteCourses();
}

void UpdateUsers()
{
    // ���ļ���ȡ�û���Ϣ.
    ReadAdmins();
    ReadTeachers();
    ReadStudents();
    ReadTAs();
	ReadUsers();
	ReadCourses();
	HighlightPrint("�������! \n");
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
