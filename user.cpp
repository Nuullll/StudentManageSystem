// user.cpp

#include "user.h"
#include "file.h"
#include "course.h"
#include "main.h"
#include <algorithm>

void ValidPassword(std::string password)
{
    for (int i = 0; i < password.size(); i++)
    {
        char ch = password[i];
        if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')))
            return false;
    }
    return ((password.size() >= 6) && (password.size() <= 15));
}

std::ofstream &operator <<(std::ofstream &of, const User &user)
{
    of << user.identity_ << '\n';
    of << user.id_ << '\n';
    of << user.password_ << '\n';
    return of;
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
        HighlightPrint("请设置6~15位数字字母密码!\n");
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

void Administrator::update()
{
    admins = Remove(admins, id_);
    admins.push_back(*this);
    UpadateFiles();
    return;
}

std::ifstream &operator >>(std::ifstream &in, Administrator &admin)
{
    in >> admin.identity_;
    in >> admin.id_;
    in >> admin.password_;
    return in;
}

std::ofstream &operator <<(std::ofstream &of, const Administrator &admin)
{
    of << User(admin) << '\n';
    return of;
}

void Teacher::add_course()
{
    ClearScreen();
    HighlightPrint("开设一门课程!\n");
    std::cout << "课程ID: ";
    std::string new_id, new_name;
    int credit;
    bool is_optional, is_scoring;
    std::cin >> new_id;
    if (Find(courses, new_id) >= 0)     // id符合
    {
        course_id_.push_back(courses[Find(courses, new_id)]);
        courses[Find(courses, new_id)].add_teacher(id_);
        update();
        return;
    }
    else
    {
        std::cout << "正在创建一门新课程...\n";
        std::cout << "课程名称: ";
        if (!(std::cin >> new_name))
            HighlightPrint("输入错误! \n"), return;
        std::cout << "学分: ";
        if (!(std::cin >> credit))
            HighlightPrint("输入错误! \n"), return;
        std::cout << "选修课? [0/1] ";
        if (!(std::cin >> is_optional))
            HighlightPrint("输入错误! \n"), return;
        std::cout << "是否记分? [0/1] ";
        if (!(std::cin >> is_scoring))
            HighlightPrint("输入错误! \n"), return;
        Course new_course(new_id, new_name, credit, is_optional, is_scoring);
        new_course.add_teacher(id_);
        courses.push_back(new_course);
        WriteCourses("./data/courses.txt", courses);
        course_id_.push_back(new_id);
        update();
        return;
    }
}

void Teacher::display_class()
{
    std::vector<Student> my_class;
    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); it++)
    {
        if (it->class_id() == class_id_)
            my_class.push_back(*it);
    }
    for (std::vector<TeachingAssistant>::iterator it = tas.begin(); it != tas.end(); it++)
    {
        if (it->Student::class_id() == class_id_)
            my_class.push_back(*it);
    }
    std::sort(my_class.begin(), my_class.end(), CompareStudent);
    ClearScreen();
    HighlightPrint(class_id_ + '\n');
    std::cout << "[按GPA排序]\n";
    for (std::vector<Student>::iterator it = my_class.begin(); it != my_class.end(); it++)
        it->display_gpa_info();
    getch();
    return;
}

void Teacher::update()
{
    teachers = Remove(teachers, id_);
    teachers.push_back(*this);
    UpdateFiles();
    return;
}

std::ifstream &operator >>(std::ifstream &in, Teacher &t)
{
    in >> t.identity_;
    in >> t.id_;
    in >> t.password_;
    in >> t.name_;
    char start_flag;
    while ((start_flag = in.get()) == '\n')
        ;
    if (start_flag == '*')
    {
        while (true)
        {
            char end_flag;
            std::string tmp_id;
            in >> tmp_id;
            t.course_id_.push_back(tmp_id);
            while ((end_flag = in.get()) == '\n')
                ;
            if (end_flag == '#')
                break;
            else
                in.seekg(-1, std::ios::cur);           
        }
    }
    else
        in.seekg(-1, std::ios::cur);
    in >> t.is_head_teacher_;
    in >> t.class_id_;
    return in;
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

double Student::gpa()
{
    int total = 0;
    for (std::vector<Score>::iterator it = score_.begin(); it != score_.end(); it++)
        total += it->num() * courses[Find(courses, it->course_id())].credit();
    return double(total) / double(credit());
}

int Student::credit()
{
    int total = 0;
    for (std::vector<std::string>::iterator it = course_id_.begin(); it != course_id_.end(); it++)
        total += courses[Find(courses, *it)].credit();
    return total;
}

void Student::add_course()
{
    ClearScreen();
    HighlightPrint("课程ID: ");
    std::string add_id;
    std::cin >> add_id;
    if (Find(courses, add_id) < 0)
    {
        HighlightPrint("没有该课程! 请核对课程ID.\n");
        getch();
        return;
    }
    course_id_.push_back(add_id);
    update();
    courses[Find(courses, add_id)].add_student(id_);
    WriteCourses("./data/courses.txt", courses);
    HighlightPrint("添加成功!\n");
    getch();
    return;
}

void Student::add_score(Score score)
{
    if (Find(score_, score) < 0)
        score_.push_back(score);
    else
        score_[Find(score_, score)].update_num(score.num());
    return;
}

void Student::course_info()
{
    ClearScreen();
    for (std::vector<std::string>::iterator it = course_id_.begin(); it != course_id_.end(); it++)
    {
        Course tmp = courses[Find(courses, *it)];
        std::cout << tmp.id() << "  ";
        std::cout << tmp.name() << "  ";
        std::cout << tmp.credit() << "学分  ";
        if (tmp.is_optional())
            std::cout << "选修课程 ";
        else
            std::cout << "必限课程 ";
        if (tmp.is_scoring())
        {
            Score score = score_[Find(score_, tmp.id())];
            std::cout << score.num() << ' ';
            std::cout << "课程内排名: " << score.rank() << '/' << tmp.students().size() << std::endl;
        }
        else
            std::cout << "不记分  \n";
    }
    std::cout << "总GPA: " << gpa() << std::endl;
    return;
}

void Student::display_gpa_info()
{
    std::cout << id_ << ' ';
    std::cout << name_ << ' ';
    std::cout << class_id_ << ' ';
    std::cout << "GPA: " << gpa() << std::endl;
    return;
}

void Student::update()
{
    students = Remove(students, id_);
    students.push_back(*this);
    UpdateFiles();
    return;
}

std::ifstream &operator >>(std::ifstream &in, Student &stu)
{
    in >> stu.identity_;
    in >> stu.id_;
    in >> stu.password_;
    in >> stu.name_;
    in >> stu.class_id_;
    char start_flag;
    while ((start_flag = getch()) == '\n')
        ;
    if (start_flag == '*')
    {
        while (true)
        {
            char end_flag;
            std::string tmp_id;
            in >> tmp_id;
            stu.course_id_.push_back(tmp_id);
            while ((end_flag = in.get()) == '\n')
                ;
            if (end_flag == '#')
                break;
            else
                in.seekg(-1, std::ios::cur);
        }
    }
    else
        in.seekg(-1, std::ios::cur);
    while ((start_flag = getch()) == '\n')
        ;
    if (start_flag == '*')
    {
        while (true)
        {
            char end_flag;
            Score tmp_score;
            in >> tmp_score;
            stu.score_.push_back(tmp_score);
            while ((end_flag = in.get()) == '\n')
                ;
            if (end_flag == '#')
                break;
            else
                in.seekg(-1, std::ios::cur);
        }
    }
    else
        in.seekg(-1, std::ios::cur);
    return in;
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

bool CompareStudent(Student stu1, Student stu2)
{
    return stu1.gpa() > stu2.gpa();
}

void TeachingAssistant::update()
{
    tas = Remove(tas, id_);
    tas.push_back(*this);
    UpdateFiles();
    return;
}

std::ifstream &operator >>(std::ifstream &in, TeachingAssistant &ta)
{
    in >> ta.identity_;
    in >> ta.id_;
    in >> ta.password_;
    in >> ta.name_;
    in >> ta.class_id_;
    char start_flag;
    while ((start_flag = getch()) == '\n')
        ;
    if (start_flag == '*')
    {
        while (true)
        {
            char end_flag;
            std::string tmp_id;
            in >> tmp_id;
            ta.Teacher::course_id_.push_back(tmp_id);
            while ((end_flag = in.get()) == '\n')
                ;
            if (end_flag == '#')
                break;
            else
                in.seekg(-1, std::ios::cur);
        }
    }
    else
        in.seekg(-1, std::ios::cur);
    while ((start_flag = getch()) == '\n')
        ;
    if (start_flag == '*')
    {
        while (true)
        {
            char end_flag;
            std::string tmp_id;
            in >> tmp_id;
            ta.Student::course_id_.push_back(tmp_id);
            while ((end_flag = in.get()) == '\n')
                ;
            if (end_flag == '#')
                break;
            else
                in.seekg(-1, std::ios::cur);
        }
    }
    else
        in.seekg(-1, std::ios::cur);
    return in;
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
