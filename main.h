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

void UpdateUsers();
void UpdateFiles();
void Title();
void ClearScreen();
void Exit();
std::string GetPass();
Token Login();

template <class T>
T Find(std::vector<T> vt, std::string id);

template <class T>
std::vector<T> Remove(std::vector<T> v, int id);

std::vector<MenuNode> InitialMenu(int identity);
