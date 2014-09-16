// global.cpp

#include "global.h"
#include "file.h"

std::vector<User*> users;   // �����û�����ָ��.
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
}

void UpdateUsers()
{
    // ���ļ���ȡ�û���Ϣ.
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
