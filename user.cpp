// user.cpp

#include "user.h"
#include "file.h"

void User::set_password(std::string new_password)
{
    password_ = new_password;
    UpdatePassword(id_num_, new_password);
}

std::ofstream &operator <<(std::ofstream &of, const User &user)
{
    of << user.identity_ << '\n'; 
    of << user.id_num_ << '\n';
    return of;
}

std::ofstream &operator <<(std::ofstream &of, const Administrator &admin)
{
    of << User(admin) << '\n';
    return of;
}

std::ofstream &operator <<(std::ofstream &of, const Teacher &t)
{
    of << User(t);
    of << t.name_ << '\n';
    std::vector<std::string>::iterator it;
    for(it = t.course_id_.begin(); it != t.course_id_.end(); it++)
    {
        of << *it << '\n';
    }
    of << t.is_head_teacher_ << '\n';
    of << t.class_id_ << '\n\n';
    return of;
}

std::ofstream &operator <<(std::ofstream &of, const Student &stu)
{
    of << User(stu);
    of << stu.name_ << '\n';
    of << stu.class_id_ << '\n';
    std::vector<std::string>::iterator it1;
    for(it1 = stu.course_id_.begin(); it1 != stu.course_id_.end(); it1++)
    {
        of << *it1 << '\n';
    }
    std::vector<Score>::iterator it2;
    for(it2 = stu.score_.begin(); it2 != stu.score_.end(); it2++)
    {
        of << *it2;
    }
    of << '\n';
    return of;
}

