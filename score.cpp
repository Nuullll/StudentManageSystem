//score.cpp

#include "score.h"

std::ofstream &operator <<(std::ofstream &of, const Score &s)
{
    of << s.course_id_ << '\n';
    of << s.student_id_ << '\n';
    of << s.num_ << '\n';
    return of;
}