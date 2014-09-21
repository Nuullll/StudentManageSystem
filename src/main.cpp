// main.cpp

#include "global.h"
#include "file.h"
#include "token.h"
#include "user.h"
#include <conio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <map>

int main(int argc, char const *argv[])
{
login:              // 登录标签.
	ClearScreen();
	HighlightPrint("载入数据中...请稍后...\n");
	UpdateUsers();
    ClearScreen();      // 保留软件标题的清屏函数.
    Token tmp;		// 获取登录信息的令牌.
    User* user;     // 当前登录的用户.
    while (true)
    {
        tmp = Login();  // 从键盘获取登录信息.
        if ((user = tmp.auth(users)) != NULL)
        {
            std::cout << "登录成功!\n";
            std::cout << "欢迎";
            user->print();  // 显示用户基本信息.
			MyGetCh();
            break;
        }
        else
        {
            ClearScreen();  // 清屏显示错误.
            std::cout << "学号(工号)或密码错误! 重新输入? \n";
            std::cout << "[回车继续, q退出系统] ";
            if (MyGetCh() == std::make_pair(1,'q'))     // 退出系统.
            {
                HighlightPrint("\n再见! \n");
                return 0;
            }
			ClearScreen();
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
                Key ch = MyGetCh();   // 获取键盘输入(非缓冲)
                if (ch == UP)
                {
                    if (--k < 0)
                        k = now.options_target.size() - 1; // 选中最后一项.
                    continue;
                }
                if (ch == DOWN)
                {
                    if (++k > now.options_target.size() - 1)
                        k = 0;  // 选中第一项.
                    continue;
                }
                if (ch == LEFT || ch == ESCAPE)
                {
                    now = *now.previous;    // 返回上级菜单.
                    k = 0;
                    continue;
                }
                if (ch == RIGHT || ch == ENTER)
                {
                    if (now.options_target[k] == NULL)
                    {
                        std::map<std::string, int> mp;
                        mp["退出系统"] = 0;
                        mp["新用户注册"] = 1;
                        mp["删除用户"] = 2;
                        mp["修改密码"] = 3;
                        mp["退出登录"] = 4;
                        switch (mp[now.options_text[k]])
                        {
                            case 0:
                            {
                                Exit();
                                break;
                            }
                            case 1:
                            {
                                admin.add_user();
                                break;
                            }
                            case 2:
                            {
                                admin.del_user();
                                break;
                            }
                            case 3:
                            {
                                admin.set_password();
                                break;
                            }
                            case 4:
                                goto login;
                        }
                        k = 0;
                        continue;
                    }
                    else
                    {
                        now = *now.options_target[k];
                        k = 0;
                        continue;
                    }
                }
			}
		}
        // 教师菜单.
        case TEACHER:
        {
            Teacher teacher;
            teacher = teachers[Find(teachers, tmp.id())];
            MenuNode top_menu, course_menu, user_menu;
            top_menu.previous = course_menu.previous = user_menu.previous = &top_menu;
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
                now.show(k);    // 展示菜单, 第k项高亮显示
                Key ch = MyGetCh();   // 获取键盘输入(非缓冲)
                if (ch == UP)
                {
                    if (--k < 0)
                        k = now.options_target.size() - 1; // 选中最后一项.
                    continue;
                }
                if (ch == DOWN)
                {
                    if (++k > now.options_target.size() - 1)
                        k = 0;  // 选中第一项.
                    continue;
                }
                if (ch == LEFT || ch == ESCAPE)
                {
                    now = *now.previous;    // 返回上级菜单.
                    k = 0;
                    continue;
                }
                if (ch == RIGHT || ch == ENTER)
                {
                    if (now.options_target[k] == NULL)
                    {
                        std::map<std::string, int> mp;
                        mp["退出系统"] = 0;
                        mp["查看班级"] = 1;
                        mp["增开课程"] = 2;
                        mp["修改密码"] = 3;
                        mp["退出登录"] = 4;
						for (int i = 0; i < teacher.course_id().size(); i++)
							mp[courses[Find(courses, teacher.course_id()[i])].name()] = 5;
                        switch (mp[now.options_text[k]])
                        {
                            case 0:
                            {
                                Exit();
                                break;
                            }
                            case 1:
                            {
                                teacher.display_class();
                                break;
                            }
                            case 2:
                            {
                                teacher.add_course();
                                break;
                            }
                            case 3:
                            {
                                teacher.set_password();
                                break;
                            }
                            case 4:
                                goto login;
                            case 5:
                            {
                                Course course = courses[Find(courses, now.options_text[k])];
                                if (course.is_scoring())
                                {
									ClearScreen();
                                    std::cout << "现在录入成绩? [y/n]";
                                    ch = MyGetCh();
                                    if (ch == std::make_pair(1, 'y') || ch == std::make_pair(1, 'Y'))
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
                        continue;
                    }
                    else
                    {
                        now = *now.options_target[k];
                        k = 0;
                        continue;
                    }
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
                now.show(k);    // 展示菜单, 第k项高亮显示
                Key ch = MyGetCh();   // 获取键盘输入(非缓冲)
                if (ch == UP)
                {
                    if (--k < 0)
                        k = now.options_target.size() - 1; // 选中最后一项.
                    continue;
                }
                if (ch == DOWN)
                {
                    if (++k > now.options_target.size() - 1)
                        k = 0;  // 选中第一项.
                    continue;
                }
                if (ch == LEFT || ch == ESCAPE)
                {
                    now = *now.previous;    // 返回上级菜单.
                    k = 0;
                    continue;
                }
                if (ch == RIGHT || ch == ENTER)
                {
                    if (now.options_target[k] == NULL)
                    {
                        std::map<std::string, int> mp;
                        mp["所有课程"] = 0;
                        mp["增加课程"] = 1;
                        mp["退出系统"] = 2;
                        mp["修改密码"] = 3;
                        mp["退出登录"] = 4;
                        switch (mp[now.options_text[k]])
                        {
                            case 0:
                            {
                                student.course_info();
                                break;
                            }
                            case 1:
                            {
                                student.add_course();
                                break;
                            }
                            case 2:
                            {
                                Exit();
                                break;
                            }
                            case 3:
                            {
                                student.set_password();
                                break;
                            }
                            case 4:
                                goto login;
                        }
                        k = 0;
                        continue;
                    }
                    else
                    {
                        now = *now.options_target[k];
                        k = 0;
                        continue;
                    }
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
                now.show(k);    // 展示菜单, 第k项高亮显示
                Key ch = MyGetCh();   // 获取键盘输入(非缓冲)
                if (ch == UP)
                {
                    if (--k < 0)
                        k = now.options_target.size() - 1; // 选中最后一项.
                    continue;
                }
                if (ch == DOWN)
                {
                    if (++k > now.options_target.size() - 1)
                        k = 0;  // 选中第一项.
                    continue;
                }
                if (ch == LEFT || ch == ESCAPE)
                {
                    now = *now.previous;    // 返回上级菜单.
                    k = 0;
                    continue;
                }
                if (ch == RIGHT || ch == ENTER)
                {
                    if (now.options_target[k] == NULL)
                    {
                        std::map<std::string, int> mp;
                        mp["退出系统"] = 0;
                        mp["增开课程"] = 1;
                        mp["所有课程"] = 2;
                        mp["增加课程"] = 3;
                        mp["修改密码"] = 4;
                        mp["退出登录"] = 5;
						for (int i = 0; i < ta.Teacher::course_id().size(); i++)
							mp[courses[Find(courses, ta.Teacher::course_id()[i])].name()] = 6;
                        switch (mp[now.options_text[k]])
                        {
                            case 0:
                            {
                                Exit();
                                break;
                            }
                            case 1:
                            {
                                ta.Teacher::add_course();
                                break;
                            }
                            case 2:
                            {
                                ta.Student::course_info();
                                break;
                            }
                            case 3:
                            {
                                ta.Student::add_course();
                                break;
                            }
                            case 4:
                            {
                                ta.set_password();
                                break;
                            }
                            case 5:
                                goto login;
                            case 6:
                            {
                                Course course = courses[Find(courses, now.options_text[k])];
                                if (course.is_scoring())
                                {
									ClearScreen();
                                    std::cout << "现在录入成绩? [y/n]";
                                    ch = MyGetCh();
                        
                                    if (ch == std::make_pair(1, 'y') || ch == std::make_pair(1, 'Y'))
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
						continue;
                    }
                    else
                    {
                        now = *now.options_target[k];
                        k = 0;
                        continue;
                    }
                }
            }
        }
    }
    return 0;
}
