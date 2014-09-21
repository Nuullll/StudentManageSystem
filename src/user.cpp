// user.cpp

#include "user.h"
#include "course.h"
#include "global.h"
#include <algorithm>
#include "file.h"

bool ValidPassword(std::string password)
{
    for (int i = 0; i < password.size(); i++)
    {
        char ch = password[i];
        if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')))
            return false;
    }
    return ((password.size() >= 6) && (password.size() <= 15));
}

void User::set_password()
{
    ClearScreen();
    std::cout << "ԭ����: ";
    std::string origin = GetPass();
    if (origin != password_)
    {
        HighlightPrint("�������! \n");
		MyGetCh();
        return;
    }
    std::cout << "������: ";
    std::string new_pwd = GetPass();
    if (!ValidPassword(new_pwd))
    {
        HighlightPrint("������6~15λ������ĸ����!\n");
		MyGetCh();
        return;
    }
    std::cout << "�ظ�������: ";
    std::string confirm = GetPass();
    if (new_pwd != confirm)
    {
        HighlightPrint("�������벻һ��!\n");
		MyGetCh();
        return;
    }
    password_ = new_pwd;
    update();
    HighlightPrint("���óɹ�!\n");
	MyGetCh();
    return;
}

void Administrator::add_user()
{
    std::vector<std::string> identities;
    int k = 1;      // identity = k
    identities.push_back("��ʦ");
    identities.push_back("ѧ��");
    identities.push_back("����");
    while (true)        // ��ݲ˵�ѡ��.
    {
        ClearScreen();
        std::cout << "��ѡ�����û������:\n";
        for (int i = 0; i < 3; ++i)
        {
            if (i == k - 1)
            {
                HighlightPrint(identities[i] + '\n');
                continue;
            }
            std::cout << identities[i] + '\n';
        }
        Key ch = MyGetCh();
        if (ch == UP)
        {
            if (--k < 1)
                k = 3;
            continue;
        }
        if (ch == DOWN)
        {
            if (++k > 3)
                k = 1;
            continue;
        }
        if (ch == LEFT || ch == ESCAPE)
            return;
        if (ch == RIGHT || ch == ENTER)
        {
            ClearScreen();
            HighlightPrint(identities[k - 1] + '\n');
            continue;
        }
    }
    int new_id = 0;
    for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
    {
        if (new_id <= (*it)->id())
            new_id = (*it)->id() + 1;
    }
    std::cout << "ѧ��(����): " << new_id << std::endl;
    std::cout << "����������: ";
    std::string new_name;
    std::cin >> new_name;
    std::cin.get();
    std::cout << "���뵥��ӡ���!\n";      // Ĭ��������ѧ��(����)��ͬ
    HighlightPrint("�뾡���޸�����!\n");
    switch (k)
    {
        case TEACHER:
        {
            std::ofstream fp("./data/teachers.txt", std::ios::app|std::ios::out);
            fp << k << '\n';
            fp << new_id << '\n';
            fp << new_id << '\n';   // ����
            fp << new_name << '\n';
			fp << "*\n";
			fp << "#\n";
            std::cout << "�����û�Ϊ������, ��������: [������ֱ�ӻس�] ";
            if (MyGetCh() != ENTER)      // ������
            {
                fp << 1 << '\n';
                std::string class_id;
                std::cin >> class_id;
                std::cin.get();
                fp << class_id << "\n\n";
				fp.close();
                break;
            }
            else    // �ǰ�����
            {
                fp << 0 << '\n';
                fp << 0 << "\n\n";
				fp.close();
                break;
            }
        }
        case STUDENT:
        {
            std::ofstream fp("./data/students.txt", std::ios::app|std::ios::out);
            fp << k << '\n';
            fp << new_id << '\n';
            fp << new_id << '\n';   // ����
            fp << new_name << '\n';
            std::cout << "���: ";
            std::string class_id;
            std::cin >> class_id;
            std::cin.get();
            fp << class_id << '\n';
			fp << "*\n";
			fp << "#\n";
			fp << "*\n";
			fp << "#\n";
			fp.close();
            break;
        }
        case TEACHING_ASSISTANT:
        {
            std::ofstream fp("./data/tas.txt", std::ios::app|std::ios::out);
            fp << k << '\n';
            fp << new_id << '\n';
            fp << new_id << '\n';   // ����
            fp << new_name << '\n';
            std::cout << "���: ";
            std::string class_id;
            std::cin >> class_id;
            std::cin.get();
            fp << class_id << '\n';
			fp << "*\n";
			fp << "#\n";
			fp << "*\n";
			fp << "#\n";
			fp.close();
            break;
        }
		default:
			break;
    }
    UpdateUsers();
	return;
}

void Administrator::del_user()
{
	ClearScreen();
    std::cout << "ѧ��(����): ";
    int del_id;
    std::cin >> del_id;
    std::cin.get();
    if (Find(users, del_id) < 0)  // �û�������
    {
        std::cout << "�û�������!\n";
        MyGetCh();
        ClearScreen();
        return;
    }
    switch (users[Find(users, del_id)]->identity())
    {
        case ADMINISTRATOR:
        {
            HighlightPrint("��Ȩ�޽��д˲���! \n");
            break;
        }
        case TEACHER:
        {
            teachers = Remove(teachers, del_id);
            HighlightPrint("�û��ѱ�ɾ��!\n");
            break;
        }
        case STUDENT:
        {
            students = Remove(students, del_id);
            HighlightPrint("�û��ѱ�ɾ��!\n");
            break;
        }
        case TEACHING_ASSISTANT:
        {
            tas = Remove(tas, del_id);
            HighlightPrint("�û��ѱ�ɾ��!\n");
            break;
        }
        default:
            break;
    }
    UpdateFiles();
	UpdateUsers();
	return;
}

void Administrator::update()
{
    admins = Remove(admins, id_);
    admins.push_back(*this);
    UpdateFiles();
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
    of << admin.identity_ << '\n';
    of << admin.id_ << '\n';
    of << admin.password_ << '\n';
    return of;
}

void Teacher::add_course()
{
    ClearScreen();
    HighlightPrint("����һ�ſγ�!\n");
    std::cout << "�γ�ID: ";
    std::string new_id, new_name;
    int credit;
    bool is_optional, is_scoring;
    std::cin >> new_id;
    std::cin.get();
	int index = Find(courses, new_id);
    if (index >= 0)     // id����
    {
        course_id_.push_back(new_id);
		Course tmp = courses[index];
        tmp.add_teacher(id_);
		tmp.update();
        update();
		HighlightPrint("��ӳɹ�!\n");
		MyGetCh();
        return;
    }
    else
    {
        std::cout << "���ڴ���һ���¿γ�...\n";
        std::cout << "�γ�����: ";
        if (!(std::cin >> new_name))
		{
            HighlightPrint("�������! \n");
            MyGetCh();
            return;
        }
        std::cin.get();
        std::cout << "ѧ��: ";
        if (!(std::cin >> credit))
		{
            HighlightPrint("�������! \n");
            MyGetCh();
            return;
        }
        std::cin.get();
        std::cout << "ѡ�޿�? [0/1] ";
        if (!(std::cin >> is_optional))
		{
            HighlightPrint("�������! \n");
            MyGetCh();
            return;
        }
        std::cin.get();
        std::cout << "�Ƿ�Ƿ�? [0/1] ";
        if (!(std::cin >> is_scoring))
		{
            HighlightPrint("�������! \n");
            MyGetCh();
            return;
        }
        std::cin.get();
        Course new_course(new_id, new_name, credit, is_optional, is_scoring);
        new_course.add_teacher(id_);
        course_id_.push_back(new_id);
        update();
		HighlightPrint("��ӳɹ�!\n");
		MyGetCh();
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
    std::cout << "[��GPA����]\n";
    for (std::vector<Student>::iterator it = my_class.begin(); it != my_class.end(); it++)
        it->display_gpa_info();
    MyGetCh();
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
            while ((end_flag = in.get()) == '\n')
                ;
            if (end_flag == '#')
                break;
            else
			{
                in.seekg(-1, std::ios::cur);           
				std::string tmp_id;
				in >> tmp_id;
				t.course_id_.push_back(tmp_id);
			}
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
    of << t.identity_ << '\n';
    of << t.id_ << '\n';
    of << t.password_ << '\n';
    of << t.name_ << '\n';
    of << "*\n";
    for(std::vector<std::string>::const_iterator it = t.course_id_.begin(); it != t.course_id_.end(); it++)
    {
        of << *it << '\n';
    }
    of << "#\n";
    of << t.is_head_teacher_ << '\n';
    of << t.class_id_ << "\n\n";
    return of;
}

double Student::gpa()
{
    int total = 0;
    for (std::vector<Score>::iterator it = score_.begin(); it != score_.end(); it++)
        total += it->num() * courses[Find(courses, it->course_id())].credit();
    return (credit() ? (double(total) / double(credit())) : 0.0);
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
    HighlightPrint("�γ�ID: ");
    std::string add_id;
    std::cin >> add_id;
    std::cin.get();
    if (Find(courses, add_id) < 0)
    {
        HighlightPrint("û�иÿγ�! ��˶Կγ�ID.\n");
        MyGetCh();
        return;
    }
	if (Find(course_id_, add_id) >= 0)
	{
		HighlightPrint("�Ѿ���ӹ��ÿγ�!\n");
		MyGetCh();
		return;
	}
    course_id_.push_back(add_id);
    update();
	Course tmp = courses[Find(courses, add_id)];
	tmp.add_student(id_);
    WriteCourses();
    HighlightPrint("��ӳɹ�!\n");
    MyGetCh();
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
		printf("%6s", tmp.id().c_str());
		printf("%24s", tmp.name().c_str());
		printf("%3d%s", tmp.credit(), "ѧ��");
		printf("%10s", tmp.is_optional()?"ѡ�޿γ�":"���޿γ�");
        if (tmp.is_scoring())
        {
			if (Find(score_, tmp.id()) < 0)
			{
				printf("%12s\n","�ɼ�δ¼��");
				continue;
			}
            Score score = score_[Find(score_, tmp.id())];
			printf("%4d", score.num());
            std::cout << "  �γ�������: " << score.rank() << '/' << tmp.student_id().size() << std::endl;
        }
        else
            printf("%12s\n","���Ƿ�");
    }
    std::cout << "��GPA: " << gpa() << std::endl;
	MyGetCh();
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
    while ((start_flag = in.get()) == '\n')
        ;
    if (start_flag == '*')
    {
        while (true)
        {
            char end_flag;
            while ((end_flag = in.get()) == '\n')
                ;
            if (end_flag == '#')
                break;
            else
			{
                in.seekg(-1, std::ios::cur);
				std::string tmp_id;
				in >> tmp_id;
				stu.course_id_.push_back(tmp_id);
			}
        }
    }
    else
        in.seekg(-1, std::ios::cur);
    while ((start_flag = in.get()) == '\n')
        ;
    if (start_flag == '*')
    {
        while (true)
        {
            char end_flag;
            while ((end_flag = in.get()) == '\n')
                ;
            if (end_flag == '#')
                break;
            else
			{
                in.seekg(-1, std::ios::cur);
				Score tmp_score;
				in >> tmp_score;
				stu.score_.push_back(tmp_score);
			}
        }
    }
    else
        in.seekg(-1, std::ios::cur);
    return in;
}

std::ofstream &operator <<(std::ofstream &of, const Student &stu)
{
    of << stu.identity_ << '\n';
    of << stu.id_ << '\n';
    of << stu.password_ << '\n';
    of << stu.name_ << '\n';
    of << stu.class_id_ << '\n';
    of << "*\n";
    std::vector<std::string>::const_iterator it1;
    for(it1 = stu.course_id_.begin(); it1 != stu.course_id_.end(); it1++)
    {
        of << *it1 << '\n';
    }
    of << "#\n";
    of << "*\n";
    std::vector<Score>::const_iterator it2;
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
    in >> ta.Teacher::name_;
    in >> ta.Student::class_id_;
    char start_flag;
    while ((start_flag = in.get()) == '\n')
        ;
    if (start_flag == '*')
    {
        while (true)
        {
            char end_flag;
            while ((end_flag = in.get()) == '\n')
                ;
            if (end_flag == '#')
                break;
            else
			{
                in.seekg(-1, std::ios::cur);
				std::string tmp_id;
				in >> tmp_id;
				ta.Teacher::course_id_.push_back(tmp_id);
			}
        }
    }
    else
        in.seekg(-1, std::ios::cur);
    while ((start_flag = in.get()) == '\n')
        ;
    if (start_flag == '*')
    {
        while (true)
        {
            char end_flag;
            while ((end_flag = in.get()) == '\n')
                ;
            if (end_flag == '#')
                break;
            else
			{
                in.seekg(-1, std::ios::cur);
				std::string tmp_id;
				in >> tmp_id;
				ta.Student::course_id_.push_back(tmp_id);
			}
        }
    }
    else
        in.seekg(-1, std::ios::cur);
    return in;
}

std::ofstream &operator <<(std::ofstream &of, const TeachingAssistant &ta)
{
    of << ta.identity_ << '\n';
    of << ta.id_ << '\n';
    of << ta.password_ << '\n';
    of << ta.Teacher::name_ << '\n';
    of << ta.Student::class_id_ << '\n';
    of << "*\n";
    std::vector<std::string>::const_iterator it1;
    for(it1 = (ta.Teacher::course_id_).begin(); it1 != (ta.Teacher::course_id_).end(); it1++)
    {
        of << *it1 << '\n';
    }
    of << "#\n";
    of << "*\n";
    std::vector<std::string>::const_iterator it2;
    for(it2 = (ta.Student::course_id_).begin(); it2 != (ta.Student::course_id_).end(); it2++)
    {
        of << *it2 << '\n';
    }
    of << "#\n";
    of << "\n";
    return of;
}
