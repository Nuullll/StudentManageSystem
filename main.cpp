// main.cpp

#include "file.h"
#include "main.h"
#include "token.h"
#include "user.h"
#include <conio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

UpdateUsers();

int main(int argc, char const *argv[])
{
login:              // 登录标签.
    ClearScreen();      // 保留软件标题的清屏函数.
    Token tmp;      // 获取登录信息的令牌.
    User* user;     // 当前登录的用户.
    while (true)
    {
        tmp = Login();  // 从键盘获取登录信息.
        if ((user = tmp.auth(users)) != NULL)
        {
            std::cout << "登录成功!\n";
            std::cout << "欢迎";
            user->print();  // 显示用户基本信息.
            break;
        }
        else
        {
            ClearScreen();  // 清屏显示错误.
            std::cout << "学号(工号)或密码错误! 重新输入? \n";
            std::cout << "[回车继续, q退出系统] ";
            if (getch() == 'q')     // 退出系统.
            {
                std::cout << "再见! \n";
                return 0;
            }
        }
    }       // 登录成功.
    // 根据用户身份初始化菜单.
    switch (user->identity())
    {
        // 管理员菜单.
        case ADMINISTRATOR:
        {
            Administrator admin;
            admin = admins[Find(admins, tmp.id())];     // 从admins中读取当前登录的admin信息.
            MenuNode top_menu, manager_menu, user_menu;     // 管理员菜单.
            top_menu.previous = manager_menu.previous = user_menu.previous = &top_menu;
            top_menu.append("用户管理", &manager_menu);
            top_menu.append("个人中心", &user_menu);
            top_menu.append("退出系统", NULL);
            manager_menu.append("新用户注册", NULL);
            manager_menu.append("删除用户", NULL);
            user_menu.append("修改密码", NULL);
            user_menu.append("退出登录", NULL);
            MenuNode now = top_menu;    // 当前显示菜单.
            int k = 0;                  // 菜单项目索引.
            while (true)
            {
                now.show(k);    // 展示菜单, 第k项高亮显示
                int ch = getch();   // 获取键盘输入(非缓冲)
                if (ch == 13)   // 回车键, 等价与方向键右
                    goto admin_right;
                if (ch == 27)   // ESC键, 等价于方向键左
                    goto admin_left;
                while (ch != 224)   // 方向键需getch()两次.
                    ;
                switch (getch())
                {
                    case UP:
                    {
                        if (--k < 0)
                            k = now.options_target.size() - 1; // 选中最后一项.
                        break;
                    }
                    case DOWN:
                    {
                        if (++k > now.options_target.size() - 1)
                            k = 0;  // 选中第一项.
                        break;
                    }
                    case LEFT:
                    {
admin_left:
                        now = *now.previous;    // 返回上级菜单.
                        k = 0;
                        break;
                    }
                    case RIGHT:
                    {
admin_right:
                        if (now.options_target[k] == NULL)
                        {
                            switch (now.options_text[k])
                            {
                                case "退出系统":
                                {
                                    Exit();
                                    break;
                                }
                                case "新用户注册":
                                {
                                    admin.add_user();
                                    break;
                                }
                                case "删除用户":
                                {
                                    admin.del_user();
                                    break;
                                }
                                case "修改密码":
                                {
                                    admin.set_password();
                                    break;
                                }
                                case "退出登录":
                                    goto login;
                                default:
                                    break;
                            }
                            k = 0;
                            break;
                        }
                        else
                        {
                            now = *now.options_target[k];
                            k = 0;
                            break;
                        }
                    }
                    default:
                        break;
                }
            }
        }
        // 教师菜单.
        case TEACHER:
        {
            Teacher teacher;
            teacher = teachers[Find(teachers, tmp.id())];
            MenuNode top_menu, course_menu, user_menu;
            top_menu.previous = course_menu.previous = class_menu.previous = user_menu.previous = &top_menu;
            top_menu.append("课程管理", &course_menu);
            if (teacher.is_head_teacher())
                top_menu.append("查看班级", NULL);
            top_menu.append("个人中心", &user_menu);
            top_menu.append("退出系统", NULL);
            for (int i = 0; i < teacher.course_id().size(); i++)
                course_menu.append(courses[Find(courses, teacher.course_id()[i])].name(), NULL);
            course_menu.append("增开课程", NULL);
            user_menu.append("修改密码", NULL);
            user_menu.append("退出登录", NULL);
            MenuNode now = top_menu;
            int k = 0;
            while (true)
            {
                now.show(k);
                int ch = getch();
                if (ch == 13)
                    goto teacher_right;
                if (ch == 27)
                    goto teacher_left;
                while (ch != 224)
                    ;
                switch (getch())
                {
                    case UP:
                    {
                        if (--k < 0)
                            k = now.options_target.size() - 1;
                        break;
                    }
                    case DOWN:
                    {
                        if (++k > now.options_target.size() - 1)
                            k = 0;
                        break;
                    }
                    case LEFT:
                    {
teacher_left:
                        now = *now.previous;
                        k = 0;
                        break;
                    }
                    case RIGHT:
                    {
teacher_right:
                        if (now.options_target[k] == NULL)
                        {
                            switch (now.options_text[k])
                            {
                                case "退出系统":
                                {
                                    Exit();
                                    break;
                                }
                                case "查看班级":
                                {
                                    teacher.diplay_class();
                                    break;
                                }
                                case "增开课程":
                                {
                                    teacher.add_course();
                                    break;
                                }
                                case "修改密码":
                                {
                                    teacher.set_password();
                                    break;
                                }
                                case "退出登录":
                                    goto login;
                                default:
                                {
                                    Course course = courses[Find(courses, now.options_target[k])];
                                    if (course.is_scoring())
                                    {
                                        std::cout << "现在录入成绩? [y/n]";
                                        ch = getch();
                                        if (ch == 'y' || ch == 'Y')
                                        {
                                            course.update_score();
                                            break;
                                        }
                                    }
                                    course.display();
                                    break;
                                }
                            }
                            k = 0;
                            break;
                        }
                        else
                        {
                            now = *now.options_target[k];
                            k = 0;
                            break;
                        }
                    }
                    default:
                        break;
                }
            }
        }
        // 学生菜单.
        case STUDENT:
        {
            Student student;
            student = students[Find(students, tmp.id())];
            MenuNode top_menu, user_menu;
            top_menu.previous = user_menu.previous = &top_menu;
            top_menu.append("所有课程", NULL);
            top_menu.append("增加课程", NULL);
            top_menu.append("个人中心", &user_menu);
            top_menu.append("退出系统", NULL);
            user_menu.append("修改密码", NULL);
            user_menu.append("退出登录", NULL);
            MenuNode now = top_menu;
            int k = 0;
            while (true)
            {
                now.show(k);
                int ch = getch();
                if (ch == 13)
                    goto student_right;
                if (ch == 27)
                    goto student_left;
                while (ch != 224)
                    ;
                switch (getch())
                {
                    case UP:
                    {
                        if (--k < 0)
                            k = now.options_target.size() - 1;
                        break;
                    }
                    case DOWN:
                    {
                        if (++k > now.options_target.size() - 1)
                            k = 0;
                        break;
                    }
                    case LEFT:
                    {
student_left:
                        now = *now.previous;
                        k = 0;
                        break;
                    }
                    case RIGHT:
                    {
                        student_right:
                        if (now.options_target[k] == NULL)
                        {
                            switch (now.options_text[k])
                            {
                                case "所有课程":
                                {
                                    student.course_info();
                                    break;
                                }
                                case "增加课程":
                                {
                                    student.add_course();
                                    break;
                                }
                                case "退出系统":
                                {
                                    Exit();
                                    break;
                                }
                                case "修改密码":
                                {
                                    student.set_password();
                                    break;
                                }
                                case "退出登录":
                                    goto login;
                                default:
                                    break;
                            }
                            k = 0;
                            break;
                        }
                        else
                        {
                            now = *now.options_target[k];
                            k = 0;
                            break;
                        }
                    }
                    default:
                        break;
                }
            }
        }
        // 助教菜单
        case TEACHING_ASSISTANT:
        {
            TeachingAssistant ta;
            ta = tas[Find(tas, tmp.id())];
            MenuNode top_menu, teacher_menu, student_menu, user_menu;
            top_menu.previous = teacher_menu.previous = student_menu.previous = user_menu.previous = &top_menu;
            top_menu.append("教师界面", &teacher_menu);
            top_menu.append("学生界面", &student_menu);
            top_menu.append("个人中心", &user_menu);
            top_menu.append("退出系统", NULL);
            for (int i = 0; i < ta.Teacher::course_id().size(); i++)
                teacher_menu.append(courses[Find(courses, ta.Teacher::course_id()[i])].name(), NULL);
            teacher_menu.append("增开课程", NULL);
            student_menu.append("所有课程", NULL);
            student_menu.append("增加课程", NULL);
            user_menu.append("修改密码", NULL);
            user_menu.append("退出登录", NULL);
            MenuNode now = top_menu;
            int k = 0;
            while (true)
            {
                now.show(k);
                int ch = getch();
                if (ch == 13)
                    goto ta_right;
                if (ch == 27)
                    goto ta_left;
                while (ch != 224)
                    ;
                switch (getch())
                {
                    case UP:
                    {
                        if (--k < 0)
                            k = now.options_target.size() - 1;
                        break;
                    }
                    case DOWN:
                    {
                        if (++k > now.options_target.size() + 1)
                            k = 0;
                        break;
                    }
                    case LEFT:
                    {
ta_left:
                        now = *now.previous;
                        k = 0;
                        break;
                    }
                    case RIGHT:
                    {
ta_right:
                        if (now.options_target[k] == NULL)
                        {
                            switch (now.options_text[k])
                            {
                                case "退出系统":
                                {
                                    Exit();
                                    break;
                                }
                                case "增开课程":
                                {
                                    ta.Teacher::add_course();
                                    break;
                                }
                                case "所有课程":
                                {
                                    ta.Student::course_info();
                                    break;
                                }
                                case "增加课程":
                                {
                                    ta.Student::add_course();
                                    break;
                                }
                                case "修改密码":
                                {
                                    ta.set_password();
                                    break;
                                }
                                case "退出登录":
                                    goto login;
                                default:
                                {
                                    Course course = courses[Find(courses, now.options_target[k])];
                                    if (course.is_scoring())
                                    {
                                        std::cout << "现在录入成绩? [y/n]";
                                        ch = getch();
                                        if (ch == 'y' || ch == 'Y')
                                        {
                                            course.update_score();
                                            break;
                                        }
                                    }
                                    course.display();
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}


void Title()
{
	std::cout << "学生成绩管理系统 v1.60.0\n\n";
}

void ClearScreen()
{
    system("cls");
    Title();
}

std::string GetPass()
{
    std::string pwd;
    char tmp;
    while ((tmp = getch()) != 13)
    {
        pwd.append(1, tmp);
        std::cout << '*';
    }
    std::cout << '\n';
    return pwd;
}

Token Login()
{
    std::cout << "请登录\n";
    std::string id, pwd;
    std::cout << "请输入您的学号(工号): ";
    std::cin >> id;
    std::cout << "请输入您的密码: ";
    pwd = GetPass();
    return Token(id, pwd);
}

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

template <class T>
std::vector<T> Remove(std::vector<T> v, int id)
{
    for (std::vector<T>::iterator it = v.begin(); it != v.end(); it++)
    {
        if (it->id() == id)
        {
            v.erase(it);
            break;
        }
    }
    return v;
}

void UpdateUsers()
{
    // 从文件读取用户信息.
    users = ReadUsers("./data");
    admins = ReadAdmins("./data/admins.txt");
    teachers = ReadTeachers("./data/teachers.txt");
    students = ReadStudents("./data/students.txt");
    tas = ReadTAs("./data/tas.txt");
}

void UpdateFiles()
{
    // 根据全局vector更新文件.
    WriteAdmins("./data/admins.txt", admins);
    WriteTeachers("./data/teachers.txt", teachers);
    WriteStudents("./data/students.txt", students);
    WriteTAs("./data/tas.txt", tas);    
}

void Exit()
{
    ClearScreen();  // 清屏
    std::cout << "确认退出? [y/n]" << std::endl;
    ch = getch();
    if (ch == 'y' or ch == 'Y')
    {
        std::cout << "再见!" << std::endl;
        return 0;
    }
}