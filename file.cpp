// file.cpp

#include "main.h"
#include "file.h"
#include "user.h"
#include <fstream>

void WriteAdmins(char* filename, std::vector<Administrator> admins)
{
    std::ofstream of(filename, std::ios::out|std::ios::trunc);
    for (std::vector<Administrator>::iterator it = admins.begin(); it != admins.end(); it++)
        of << *it;
}

void WriteTeachers(char* filename, std::vector<Teacher> teachers)
{
    std::ofstream of(filename, std::ios::out|std::ios::trunc);
    for (std::vector<Teacher>::iterator it = teachers.begin(); it != teachers.end(); it++)
        of << *it;
}

void WriteStudents(char* filename, std::vector<Student> students)
{
    std::ofstream of(filename, std::ios::out|std::ios::trunc);
    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); it++)
        of << *it;
}

void WriteTAs(char* filename, std::vector<TeachingAssistant> tas)
{
    std::ofstream of(filename, std::ios::out|std::ios::trunc);
    for (std::vector<TeachingAssistant>::iterator it = tas.begin(); it != tas.end(); it++)
        of << *it;
}

void ReadAdmins(char* filename)
{
    std::ifstream in(filename, std::ios::in);
    admins.clear();
    Administrator admin;
    while (in >> admin)
        admins.push_back(admin);
}

void ReadTeachers(char* filename)
{
    std::ifstream in(filename, std::ios::in);
    teachers.clear();
    Teacher teacher;
    while (in >> teacher)
        teachers.push_back(teacher);
}

void ReadStudents(char* filename)
{
    std::ifstream in(filename, std::ios::in);
    students.clear();
    Student student;
    while (in >> student)
        students.push_back(student);
}

void ReadTAs(char* filename)
{
    std::ifstream in(filename, std::ios::in);
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