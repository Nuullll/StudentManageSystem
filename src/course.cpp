// course.cpp

#include "course.h"
#include "user.h"
#include "file.h"
#include "global.h"

void Course::add_teacher(int teacher_id)
{
    teacher_id_.push_back(teacher_id);
    update();
    return;
}

void Course::add_student(int student_id)
{
    student_id_.push_back(student_id);
    update();
    return;
}

void Course::update()
{
    courses = Remove(courses, id_);
    courses.push_back(*this);
    WriteCourses();
    return;
}

void Course::display()
{
    ClearScreen();
    std::cout << id_ << ' ';
    std::cout << name_ << ' ';
    std::cout << credit_ << "ѧ�� ";
    if (!is_scoring_)
        std::cout << "���Ƿ� ";
    if (is_optional_)
        std::cout << "ѡ�޿γ� \n";
    else
        std::cout << "���޿γ� \n";
    HighlightPrint("��ʦ: \n");
    for (std::vector<int>::iterator it = teacher_id_.begin(); it != teacher_id_.end(); it++)
	{
		if (Find(teachers, *it) < 0)
			tas[Find(tas, *it)].print();
		else
			teachers[Find(teachers, *it)].print();
	}
    HighlightPrint("ѧ��: \n");
    for (std::vector<int>::iterator it = student_id_.begin(); it != student_id_.end(); it++)
    {   
        Student stu = students[Find(students, *it)];
        if (!is_scoring_ || Find(stu.score(), id_) < 0)
            stu.print();
        else
        {
            std::cout << stu.id() << ' ';
            std::cout << stu.name() << ' ';
            std::cout << stu.score()[Find(stu.score(), id_)].num() << std::endl;
        }
    }
	MyGetCh();
    return;
}

void Course::update_score()
{
    ClearScreen();
    HighlightPrint("¼��ɼ���...\n");
    for (std::vector<int>::iterator it = student_id_.begin(); it != student_id_.end(); it++)
    {
        Student stu = students[Find(students, *it)];
        std::cout << stu.id() << ' ';
        std::cout << stu.name() << ' ';
        std::cout << "�ɼ�: ";
        int num = 0;
        if (!(std::cin >> num) || num < 0 || num >= 100)
        {
			std::cin.clear();
			std::cin.sync();
            HighlightPrint("�������!\n");
            return;
        }
        std::cin.get();
        stu.add_score(Score(id_, num));
        stu.update();
    }
    HighlightPrint("¼�����!\n");
    MyGetCh();
    return;
}

std::ifstream &operator >>(std::ifstream &in, Course &c)
{
    in >> c.id_;
	in >> c.name_;
	in >> c.credit_;
	in >> c.is_optional_;
	in >> c.is_scoring_;
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
				int tmp_id;
				in >> tmp_id;
				c.teacher_id_.push_back(tmp_id);
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
				int tmp_id;
				in >> tmp_id;
				c.student_id_.push_back(tmp_id);
			}
        }
    }
    else
        in.seekg(-1, std::ios::cur);
    return in;
}

std::ofstream &operator <<(std::ofstream &of, const Course &c)
{
    of << c.id_ << '\n';
    of << c.name_ << '\n';
    of << c.credit_ << '\n';
    of << c.is_optional_ << '\n';
    of << c.is_scoring_ << '\n';
    of << "*\n";
    for (std::vector<int>::const_iterator it = c.teacher_id_.begin(); it != c.teacher_id_.end(); it++)
        of << *it << '\n';
    of << "#\n";
    of << "*\n";
    for (std::vector<int>::const_iterator it = c.student_id_.begin(); it != c.student_id_.end(); it++)
        of << *it << '\n';
	of << "#\n\n";
    return of;
}