// file.h
// 声明文件操作所需的函数

#ifndef FILE_H
#define FILE_H 

#include <string>
#include <vector>
#include "user.h"

void UpdatePassword(std::string id_num, std::string new_password);

// user info
void WriteUsers(std::string path);
void WriteAdmins(std::string filename, std::vector<Administrator> admins);
void WriteTeachers(std::string filename, std::vector<Teacher> teachers);
void WriteStudents(std::string filename, std::vector<Student> students);
void WriteTAs(std::string filename, std::vector<TeachingAssistant> tas);
void ReadUsers(std::string path);
std::vector<Administrator> ReadAdmins(std::string filename);
std::vector<Teacher> ReadTeachers(std::string filename);
std::vector<Student> ReadStudents(std::string filename);
std::vector<TeachingAssistant> ReadTAs(std::string filename);

#endif