// global.h

#ifndef GLOBAL_H
#define GLOBAL_H

#include "user.h"
#include <string>
#include <utility>
#include "course.h"
#include "token.h"
#include "menu.h"

extern std::vector<User*> users;   // 所有用户基类指针.
extern std::vector<Administrator> admins;  
extern std::vector<Teacher> teachers;
extern std::vector<Student> students;
extern std::vector<TeachingAssistant> tas; // ta: teachingassistant
extern std::vector<Course> courses;

typedef std::pair<int, char> Key;	// first = times, second = ch;

const Key ENTER = std::make_pair(1, char(13));
const Key ESCAPE = std::make_pair(1, char(27));
const Key UP = std::make_pair(2, char(72));
const Key DOWN = std::make_pair(2, char(80));
const Key LEFT = std::make_pair(2, char(75));
const Key RIGHT = std::make_pair(2, char(77));

Key MyGetCh();
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

#endif