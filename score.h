#ifndef SCORE_H
#define SCORE_H 

#include "course.h"
#include <string>

class Score
{
public:
    Score();
    ~Score();

private:
    Course course_;             // 课程信息
    std::string student_id_;    // 学生ID
    int num_;                   // 分数
};

#endif