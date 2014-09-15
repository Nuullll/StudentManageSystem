//score.cpp

#include "score.h"
#include "main.h"
#include <algorithm>

bool CompareScore(Score s1, Score s2)
{
    return s1.num() > s2.num();
}

int Score::rank()
{
    Course course = courses[Find(courses, course_id_)];
    std::vector<Score> scores;
    for (std::vector<int>::iterator it = course.students().begin(); it != course.students().end(); it++)
    {
        Student stu = students[Find(students, *it)];
        scores.push_back(stu.score()[Find(stu.score(), course_id_)]);
    }
    std::sort(scores.begin(), scores.end(), CompareScore);
    for (int i = 0; i < scores.size(); i++)
    {
        if (num_ == scores[i].num())
            return i + 1;
    }
    return 0;
}

std::ifstream &operator >>(std::ifstream &in, Score &s)
{
    in >> s.course_id_;
    in >> s.num_;
    return in;
}

std::ofstream &operator <<(std::ofstream &of, const Score &s)
{
    of << s.course_id_ << '\n';
    of << s.num_ << '\n';
    return of;
}