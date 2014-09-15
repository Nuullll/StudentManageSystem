// main.h

#include <string>
#include "user.h"
#include "course.h"
#include "token.h"
#include "menu.h"

extern std::vector<User*> users;   // 所有用户基类指针.
extern std::vector<Administrator> admins;  
extern std::vector<Teacher> teachers;
extern std::vector<Student> students;
extern std::vector<TeachingAssistant> tas; // ta: teachingassistant
extern std::vector<Course> courses;

std::string GetPass();
Token Login();
void ClearScreen();
void Exit();
void Title();
void UpdateFiles();
void UpdateUsers();

template <class A, class B>
int Find(std::vector<A> v, B id);

template <class T>
std::vector<T> Remove(std::vector<T> v, int id);