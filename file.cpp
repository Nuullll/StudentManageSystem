// file.cpp

#include "file.h"
#include <fstream>

void WriteAdmins(std::string filename, std::vector<Administrator> admins)
{
    std::ofstream of(filename, std::ios::out|std::ios::trunc);
    for (std::vector<Administrator>::iterator it = admins.begin(); it != admins.end(); it++)
        of << *it;
}

void WriteTeachers(std::string filename, std::vector<Teacher> teachers)
{
    std::ofstream of(filename, std::ios::out|std::ios::trunc);
    for (std::vector<Teacher>::iterator it = teachers.begin(); it != teachers.end(); it++)
        of << *it;
}

void WriteStudents(std::string filename, std::vector<Student> students)
{
    std::ofstream of(filename, std::ios::out|std::ios::trunc);
    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); it++)
        of << *it;
}

void WriteTAs(std::string filename, std::vector<TeachingAssistant> tas)
{
    std::ofstream of(filename, std::ios::out|std::ios::trunc);
    for (std::vector<TeachingAssistant>::iterator it = tas.begin(); it != tas.end(); it++)
        of << *it;
}

