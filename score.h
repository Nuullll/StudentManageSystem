#ifndef SCORE_H
#define SCORE_H 

#include <string>

class Score
{
public:
    Score(std::string course_id, std::string student_id, int num):
          course_id_(course_id), student_id_(student_id), num_(num) {};

    friend std::ofstream &operator <<(std::ofstream &of, const Score &s);

private:
    std::string course_id_;     // 课程ID
    std::string student_id_;    // 学生ID
    int num_;                   // 分数
};

#endif