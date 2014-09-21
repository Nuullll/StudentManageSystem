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
login:              // ��¼��ǩ.
	ClearScreen();
	HighlightPrint("����������...���Ժ�...\n");
	UpdateUsers();
    ClearScreen();      // ��������������������.
    Token tmp;		// ��ȡ��¼��Ϣ������.
    User* user;     // ��ǰ��¼���û�.
    while (true)
    {
        tmp = Login();  // �Ӽ��̻�ȡ��¼��Ϣ.
        if ((user = tmp.auth(users)) != NULL)
        {
            std::cout << "��¼�ɹ�!\n";
            std::cout << "��ӭ";
            user->print();  // ��ʾ�û�������Ϣ.
			MyGetCh();
            break;
        }
        else
        {
            ClearScreen();  // ������ʾ����.
            std::cout << "ѧ��(����)���������! ��������? \n";
            std::cout << "[�س�����, q�˳�ϵͳ] ";
            if (MyGetCh() == std::make_pair(1,'q'))     // �˳�ϵͳ.
            {
                HighlightPrint("\n�ټ�! \n");
                return 0;
            }
			ClearScreen();
        }
    }       // ��¼�ɹ�.
    // �����û���ݳ�ʼ���˵�.
    switch (user->identity())
    {
        // ����Ա�˵�.
        case ADMINISTRATOR:
        {
            Administrator admin;
            admin = admins[Find(admins, tmp.id())];     // ��admins�ж�ȡ��ǰ��¼��admin��Ϣ.
            MenuNode top_menu, manager_menu, user_menu;     // ����Ա�˵�.
            top_menu.previous = manager_menu.previous = user_menu.previous = &top_menu;
            top_menu.append("�û�����", &manager_menu);
            top_menu.append("��������", &user_menu);
            top_menu.append("�˳�ϵͳ", NULL);
            manager_menu.append("���û�ע��", NULL);
            manager_menu.append("ɾ���û�", NULL);
            user_menu.append("�޸�����", NULL);
            user_menu.append("�˳���¼", NULL);
            MenuNode now = top_menu;    // ��ǰ��ʾ�˵�.
            int k = 0;                  // �˵���Ŀ����.
            while (true)
            {
                now.show(k);    // չʾ�˵�, ��k�������ʾ
                Key ch = MyGetCh();   // ��ȡ��������(�ǻ���)
                if (ch == UP)
                {
                    if (--k < 0)
                        k = now.options_target.size() - 1; // ѡ�����һ��.
                    continue;
                }
                if (ch == DOWN)
                {
                    if (++k > now.options_target.size() - 1)
                        k = 0;  // ѡ�е�һ��.
                    continue;
                }
                if (ch == LEFT || ch == ESCAPE)
                {
                    now = *now.previous;    // �����ϼ��˵�.
                    k = 0;
                    continue;
                }
                if (ch == RIGHT || ch == ENTER)
                {
                    if (now.options_target[k] == NULL)
                    {
                        std::map<std::string, int> mp;
                        mp["�˳�ϵͳ"] = 0;
                        mp["���û�ע��"] = 1;
                        mp["ɾ���û�"] = 2;
                        mp["�޸�����"] = 3;
                        mp["�˳���¼"] = 4;
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
        // ��ʦ�˵�.
        case TEACHER:
        {
            Teacher teacher;
            teacher = teachers[Find(teachers, tmp.id())];
            MenuNode top_menu, course_menu, user_menu;
            top_menu.previous = course_menu.previous = user_menu.previous = &top_menu;
            top_menu.append("�γ̹���", &course_menu);
            if (teacher.is_head_teacher())
                top_menu.append("�鿴�༶", NULL);
            top_menu.append("��������", &user_menu);
            top_menu.append("�˳�ϵͳ", NULL);
            for (int i = 0; i < teacher.course_id().size(); i++)
                course_menu.append(courses[Find(courses, teacher.course_id()[i])].name(), NULL);
            course_menu.append("�����γ�", NULL);
            user_menu.append("�޸�����", NULL);
            user_menu.append("�˳���¼", NULL);
            MenuNode now = top_menu;
            int k = 0;
            while (true)
            {
                now.show(k);    // չʾ�˵�, ��k�������ʾ
                Key ch = MyGetCh();   // ��ȡ��������(�ǻ���)
                if (ch == UP)
                {
                    if (--k < 0)
                        k = now.options_target.size() - 1; // ѡ�����һ��.
                    continue;
                }
                if (ch == DOWN)
                {
                    if (++k > now.options_target.size() - 1)
                        k = 0;  // ѡ�е�һ��.
                    continue;
                }
                if (ch == LEFT || ch == ESCAPE)
                {
                    now = *now.previous;    // �����ϼ��˵�.
                    k = 0;
                    continue;
                }
                if (ch == RIGHT || ch == ENTER)
                {
                    if (now.options_target[k] == NULL)
                    {
                        std::map<std::string, int> mp;
                        mp["�˳�ϵͳ"] = 0;
                        mp["�鿴�༶"] = 1;
                        mp["�����γ�"] = 2;
                        mp["�޸�����"] = 3;
                        mp["�˳���¼"] = 4;
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
                                    std::cout << "����¼��ɼ�? [y/n]";
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
        // ѧ���˵�.
        case STUDENT:
        {
            Student student;
            student = students[Find(students, tmp.id())];
            MenuNode top_menu, user_menu;
            top_menu.previous = user_menu.previous = &top_menu;
            top_menu.append("���пγ�", NULL);
            top_menu.append("���ӿγ�", NULL);
            top_menu.append("��������", &user_menu);
            top_menu.append("�˳�ϵͳ", NULL);
            user_menu.append("�޸�����", NULL);
            user_menu.append("�˳���¼", NULL);
            MenuNode now = top_menu;
            int k = 0;
            while (true)
            {
                now.show(k);    // չʾ�˵�, ��k�������ʾ
                Key ch = MyGetCh();   // ��ȡ��������(�ǻ���)
                if (ch == UP)
                {
                    if (--k < 0)
                        k = now.options_target.size() - 1; // ѡ�����һ��.
                    continue;
                }
                if (ch == DOWN)
                {
                    if (++k > now.options_target.size() - 1)
                        k = 0;  // ѡ�е�һ��.
                    continue;
                }
                if (ch == LEFT || ch == ESCAPE)
                {
                    now = *now.previous;    // �����ϼ��˵�.
                    k = 0;
                    continue;
                }
                if (ch == RIGHT || ch == ENTER)
                {
                    if (now.options_target[k] == NULL)
                    {
                        std::map<std::string, int> mp;
                        mp["���пγ�"] = 0;
                        mp["���ӿγ�"] = 1;
                        mp["�˳�ϵͳ"] = 2;
                        mp["�޸�����"] = 3;
                        mp["�˳���¼"] = 4;
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
        // ���̲˵�
        case TEACHING_ASSISTANT:
        {
            TeachingAssistant ta;
            ta = tas[Find(tas, tmp.id())];
            MenuNode top_menu, teacher_menu, student_menu, user_menu;
            top_menu.previous = teacher_menu.previous = student_menu.previous = user_menu.previous = &top_menu;
            top_menu.append("��ʦ����", &teacher_menu);
            top_menu.append("ѧ������", &student_menu);
            top_menu.append("��������", &user_menu);
            top_menu.append("�˳�ϵͳ", NULL);
            for (int i = 0; i < ta.Teacher::course_id().size(); i++)
                teacher_menu.append(courses[Find(courses, ta.Teacher::course_id()[i])].name(), NULL);
            teacher_menu.append("�����γ�", NULL);
            student_menu.append("���пγ�", NULL);
            student_menu.append("���ӿγ�", NULL);
            user_menu.append("�޸�����", NULL);
            user_menu.append("�˳���¼", NULL);
            MenuNode now = top_menu;
            int k = 0;
            while (true)
            {
                now.show(k);    // չʾ�˵�, ��k�������ʾ
                Key ch = MyGetCh();   // ��ȡ��������(�ǻ���)
                if (ch == UP)
                {
                    if (--k < 0)
                        k = now.options_target.size() - 1; // ѡ�����һ��.
                    continue;
                }
                if (ch == DOWN)
                {
                    if (++k > now.options_target.size() - 1)
                        k = 0;  // ѡ�е�һ��.
                    continue;
                }
                if (ch == LEFT || ch == ESCAPE)
                {
                    now = *now.previous;    // �����ϼ��˵�.
                    k = 0;
                    continue;
                }
                if (ch == RIGHT || ch == ENTER)
                {
                    if (now.options_target[k] == NULL)
                    {
                        std::map<std::string, int> mp;
                        mp["�˳�ϵͳ"] = 0;
                        mp["�����γ�"] = 1;
                        mp["���пγ�"] = 2;
                        mp["���ӿγ�"] = 3;
                        mp["�޸�����"] = 4;
                        mp["�˳���¼"] = 5;
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
                                    std::cout << "����¼��ɼ�? [y/n]";
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
