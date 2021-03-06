#ifndef SCORE_H
#define SCORE_H 

#include <string>

class Score
{
public:
    Score() {}
    Score(std::string course_id, int num): course_id_(course_id), num_(num) {};
    ~Score() {}

    std::string course_id() { return course_id_; }
    int num() { return num_; }
    void update_num(int num) { num_ = num; }
    int rank();
	bool operator ==(const Score &s) { return course_id_ == s.course_id_; }
    bool operator ==(const std::string &course_id) { return course_id_ == course_id; }
    friend std::ifstream &operator >>(std::ifstream &in, Score &s);
    friend std::ofstream &operator <<(std::ofstream &of, const Score &s);

private:
    std::string course_id_;     // 课程ID
    int num_;                   // 分数
};

bool CompareScore(Score s1, Score s2);

#endif