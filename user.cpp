// user.cpp

#include "user.h"
#include "file.h"
#include "main.h"

void ValidPassword(std::string password)
{
    return ((password.size() >= 6) && (password.size() <= 15));
}

void User::set_password()
{
    ClearScreen();
    std::cout << "原密码: ";
    std::string origin = GetPass();
    if (origin != password_)
    {
        HighlightPrint("密码错误! \n");
        return;
    }
    std::cout << "新密码: ";
    std::string new_pwd = GetPass();
    if (!ValidPassword(new_pwd))
    {
        HighlightPrint("请设置6~15位密码!\n");
        return;
    }
    std::cout << "重复新密码: ";
    std::string confirm = GetPass();
    if (new_pwd != confirm)
    {
        HighlightPrint("两次密码不一致!\n");
        return;
    }
    password_ = new_pwd;
    update();
    std::cout << "设置成功!\n";
    return;
}

void Administrator::update()
{
    Remove(admins, id_);
    admins.push_back(*this);
    UpadateFiles();
    return;
}

void Teacher::update()
{
    Remove(teachers, id_);
    teachers.push_back(*this);
    UpdateFiles();
    return;
}

void Student::update()
{
    Remove(students, id_);
    students.push_back(*this);
    UpdateFiles();
    return;
}

void TeachingAssistant::update()
{
    Remove(tas, id_);
    tas.push_back(*this);
    UpdateFiles();
    return;
}

std::ofstream &operator <<(std::ofstream &of, const User &user)
{
    of << user.identity_ << '\n';
    of << user.id_ << '\n';
    of << user.password_ << '\n';
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
    of << "*\n";
    std::vector<std::string>::iterator it;
    for(it = t.course_id_.begin(); it != t.course_id_.end(); it++)
    {
        of << *it << '\n';
    }
    of << "#\n";
    of << t.is_head_teacher_ << '\n';
    of << t.class_id_ << '\n\n';
    return of;
}

std::ofstream &operator <<(std::ofstream &of, const Student &stu)
{
    of << User(stu);
    of << stu.name_ << '\n';
    of << stu.class_id_ << '\n';
    of << "*\n";
    std::vector<std::string>::iterator it1;
    for(it1 = stu.course_id_.begin(); it1 != stu.course_id_.end(); it1++)
    {
        of << *it1 << '\n';
    }
    of << "#\n";
    of << "*\n";
    std::vector<Score>::iterator it2;
    for(it2 = stu.score_.begin(); it2 != stu.score_.end(); it2++)
    {
        of << *it2;
    }
    of << "#\n";
    of << '\n';
    return of;
}

std::ofstream &operator <<(std::ofstream &of, const TeachingAssistant &ta)
{
    of << User(ta);
    of << ta.name_ << '\n';
    of << ta.class_id_ << '\n';
    of << "*\n";
    std::vector<std::string>::iterator it1;
    for(it1 = ta.Teacher::course_id().begin(); it1 != ta.Teacher::course_id().end(); it1++)
    {
        of << *it1 << '\n';
    }
    of << "#\n";
    of << "*\n";
    std::vector<std::string>::iterator it2;
    for(it2 = ta.Student::course_id().begin(); it2 != ta.Student::course_id().end(); it2++)
    {
        of << *it2 << '\n';
    }
    of << "#\n";
    of << "\n";
    return of;
}

void Administrator::add_user()
{
    std::vector<std::string> identities;
    int k = 1;      // identity = k
    identities.push_back("教师");
    identities.push_back("学生");
    identities.push_back("助教");
    while (true)        // 身份菜单选择.
    {
        ClearScreen();
        std::cout << "请选择新用户的身份:\n";
        for (int i = 0; i < 3; ++i)
        {
            if (i == k - 1)
            {
                HighlightPrint(identities[i] + '\n');
                continue;
            }
            std::cout << identities[i] + '\n';
        }
        int ch = getch();
        if (ch == 13)   // 回车选定.
        {
            ClearScreen();
            HighlightPrint(identities[k - 1] + '\n');
            break;
        }
        while (ch != 224)
            ;
        switch (getch())
        {
            case UP:
            {
                if (--k < 1)
                    k = 3;
                break;
            }
            case DOWN:
            {
                if (++k > 3)
                    k = 1;
                break;
            }
            default:
                break;
        }
    }
    int new_id = 0;
    for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
    {
        if (new_id <= it->id())
            new_id = it->id() + 1;
    }
    std::cout << "学号(工号): " << new_id << std::endl;
    std::cout << "请输入姓名: ";
    std::string new_name;
    std::cin >> new_name;
    std::cout << "密码单打印完毕!\n";      // 默认密码与学号(工号)相同
    HighlightPrint("请尽快修改密码!\n");
    switch (k)
    {
        case TEACHER:
        {

            std::ofstream fp("./data/teachers.txt", std::ios::app|std::ios::out);
            fp << k << '\n';
            fp << new_id << '\n';
            fp << new_id << '\n';   // 密码
            fp << new_name << '\n';
            std::cout << "若新用户为班主任, 请输入班号: [否则请直接回车]";
            if (getch() != 13)      // 班主任
            {
                fp << 1 << '\n';
                std::string class_id;
                std::cin >> class_id;
                fp << class_id << '\n\n';
                break;
            }
            else    // 非班主任
            {
                fp << 0 << '\n';
                fp << 0 << '\n\n';
                break;
            }
        }
        case STUDENT:
        {
            std::ofstream fp("./data/students.txt", std::ios::app|std::ios::out);
            fp << k << '\n';
            fp << new_id << '\n';
            fp << new_id << '\n';   // 密码
            fp << new_name << '\n';
            std::cout << "班号: ";
            std::string class_id;
            std::cin >> class_id;
            fp << class_id << '\n\n';
            break;
        }
        case TEACHING_ASSISTANT:
        {
            std::ofstream fp("./data/tas.txt", std::ios::app|std::ios::out);
            fp << k << '\n';
            fp << new_id << '\n';
            fp << new_id << '\n';   // 密码
            fp << new_name << '\n';
            std::cout << "班号: ";
            std::string class_id;
            std::cin >> class_id;
            fp << class_id << '\n\n';
            break;
        }
    }
    UpdateUsers();
}

void Administrator::del_user()
{
    std::cout << "学号(工号): ";
    int del_id;
    std::cin >> del_id;
    if (Find(del_id).identity() == -1)  // 用户不存在
    {
        std::cout << "用户不存在!\n";
        getch();
        ClearScreen();
        return;
    }
    switch (Find(del_id).identity())
    {
        case ADMINISTRATOR:
        {
            ClearScreen();
            HighlightPrint("无权限进行此操作! \n");
            break;
        }
        case TEACHER:
        {
            ClearScreen();
            teachers = Remove(teachers, del_id);
            HighlightPrint("用户已被删除!\n");
            break;
        }
        case STUDENT:
        {
            ClearScreen();
            students = Remove(students, del_id);
            HighlightPrint("用户已被删除!\n");
            break;
        }
        case TEACHING_ASSISTANT:
        {
            ClearScreen();
            tas = Remove(tas, del_id);
            HighlightPrint("用户已被删除!\n");
            break;
        }
        default:
            break;
    }
    UpdateFiles();
}