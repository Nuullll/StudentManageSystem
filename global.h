// global.h

#include "user.h"
#include <string>
#include "course.h"
#include "token.h"
#include "menu.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

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

int Find(std::vector<User*> v, int id);

template <class A, class B>
int Find(std::vector<A> v, B id)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == id)
            return i;
    }
    return -1;
}

template <class A, class B>
std::vector<A> Remove(std::vector<A> v, B id)
{
    for (std::vector<A>::iterator it = v.begin(); it != v.end(); it++)
    {
        if (*it == id)
        {
            v.erase(it);
            break;
        }
    }
    return v;
}
