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

Key MyGetCh()
{
	int ch = getch();
	if (kbhit())
		return std::make_pair(2, getch());
	return std::make_pair(1, ch);
}

std::string GetPass()
{
    int c;
    std::string password;
    std::string::iterator it = password.end();
    while ((c = getch()) != '\r')
    {
        switch (c)
        {
        case 0: 
            {
                getch();
                std::cout << '\a';
                break;
            }
        case 224: 
            {
                switch (getch())
                {
                case 75: // left
                    {
                        if (it != password.begin())
                        {
                            --it;
                            std::cout << '\b';
                        }
                        else 
                            std::cout << '\a';
                        break;
                    }
                case 77: // right
                    {
                        if (it != password.end())
                        {
                            ++it;
                            std::cout << '*';
                        }
                        else
                            std::cout << '\a';
                        break;
                    }
                default: 
                    {
                        std::cout << '\a';
                        break;
                    }
                }
                break;
            }
        case 163: 
            {
                getch();
                std::cout << '\a';
                break;
            }
        case '\b':
            {
                if (password.size() != 0 && it != password.begin())
                {
                    std::cout << '\b';
                    for (int i = 0; i < password.end() - it; ++i)
                        std::cout << '*';
                    std::cout << ' ';
                    for (int i = 0; i < password.end() - it + 1; ++i)
                        std::cout << '\b';
                    password.erase(it - 1);
                    --it;
                }
                else
                    std::cout << '\a';
                break;
            }
        default:
            {
                if (isalnum(c) || ispunct(c))
                {
                    password.insert(it, c);
                    ++it;
                    for (int i = 0; i < password.end() - it + 1; ++i)
                        std::cout << '*';
                    for (int i = 0; i < password.end() - it; ++i)
                        std::cout << '\b';
                }
                else
                    std::cout << '\a';
                break;
            }
        }
    }
    std::cout << std::endl;
    return password;
}

Token Login()
{
	ClearScreen();
	std::cout << "���¼\n";
	int id;
	std::string pwd;
	std::cout << "����������ѧ��(����): ";
	if (!(std::cin >> id))
	{
		std::cin.clear();
		std::cin.sync();
		return Token(-1, "");
	}
	std::cin.get();
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
    Key ch = MyGetCh();
    if (ch == std::make_pair(1, 'y') || ch == std::make_pair(1, 'Y'))
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
	MyGetCh();
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
