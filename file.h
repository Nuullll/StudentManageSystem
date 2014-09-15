// file.h
// 声明文件操作所需的函数

#ifndef FILE_H
#define FILE_H 

#include <string>
#include <vector>
#include "course.h"
#include "user.h"

// user info
void WriteAdmins(char* filename, std::vector<Administrator> admins);
void WriteTeachers(char* filename, std::vector<Teacher> teachers);
void WriteStudents(char* filename, std::vector<Student> students);
void WriteTAs(char* filename, std::vector<TeachingAssistant> tas);
void ReadAdmins(char* filename);
void ReadTeachers(char* filename);
void ReadStudents(char* filename);
void ReadTAs(char* filename);
void ReadUsers();

void WriteCourses(char* filename, std::vector<Course> courses);
void ReadCourses(char* filename);

#endif