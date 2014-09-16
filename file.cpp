// file.cpp

#include "file.h"
#include "global.h"
#include "user.h"
#include <fstream>

void WriteAdmins()
{
    std::ofstream of("./data/admins.txt", std::ios::out|std::ios::trunc);
    for (std::vector<Administrator>::iterator it = admins.begin(); it != admins.end(); it++)
        of << *it;
}

void WriteTeachers()
{
    std::ofstream of("./data/teachers.txt", std::ios::out|std::ios::trunc);
    for (std::vector<Teacher>::iterator it = teachers.begin(); it != teachers.end(); it++)
        of << *it;
}

void WriteStudents()
{
    std::ofstream of("./data/students.txt", std::ios::out|std::ios::trunc);
    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); it++)
        of << *it;
}

void WriteTAs()
{
    std::ofstream of("./data/tas.txt", std::ios::out|std::ios::trunc);
    for (std::vector<TeachingAssistant>::iterator it = tas.begin(); it != tas.end(); it++)
        of << *it;
}

void ReadAdmins()
{
    std::ifstream in("./data/admins.txt", std::ios::in);
    admins.clear();
    Administrator admin;
    while (in >> admin)
        admins.push_back(admin);
}

void ReadTeachers()
{
    std::ifstream in("./data/teachers.txt", std::ios::in);
    teachers.clear();
    Teacher teacher;
    while (in >> teacher)
        teachers.push_back(teacher);
}

void ReadStudents()
{
    std::ifstream in("./data/students.txt", std::ios::in);
    students.clear();
    Student student;
    while (in >> student)
        students.push_back(student);
}

void ReadTAs()
{
    std::ifstream in("./data/tas.txt", std::ios::in);
    tas.clear();
    TeachingAssistant ta;
    while (in >> ta)
        tas.push_back(ta);
}

void ReadUsers()
{
    users.clear();
    User* up;
    for (std::vector<Administrator>::iterator it = admins.begin(); it != admins.end(); it++)
    {
        up = &*it;
        users.push_back(up);
    }
    for (std::vector<Teacher>::iterator it = teachers.begin(); it != teachers.end(); it++)
    {
        up = &*it;
        users.push_back(up);
    }
    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); it++)
    {
        up = &*it;
        users.push_back(up);
    }
    for (std::vector<TeachingAssistant>::iterator it = tas.begin(); it != tas.end(); it++)
    {
        up = &*it;
        users.push_back(up);
    }
}

void WriteCourses()
{
	std::ofstream of("./data/courses.txt", std::ios::out|std::ios::trunc);
	for (std::vector<Course>::iterator it = courses.begin(); it != courses.end(); it++)
		of << *it;
}

void ReadCourses()
{
	std::ifstream in("./data/courses.txt", std::ios::in);
	courses.clear();
	Course tmp;
	while (in >> tmp)
		courses.push_back(tmp);
}