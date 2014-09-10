#ifndef COURSE_H
#define COURSE_H 

#include <string>

const int kCourseMaxSize = 400;         // 课容量最大值
const int kCourseMaxTeacher = 5;        // 课程老师最大值(包括主讲老师,助教等)

class Course
{
public:
    Course();
    ~Course();

private:
    std::string course_id_;                     // 课程ID
    int course_credit_;                         // 学分
    bool is_optional_;                          // 是否任选(非任选则为必修限选课程)
    bool is_scoring_;                           // 是否记分
    double avg_score_;                          // 该课程平均分(若记分)
    std::string teacher_id_[kCourseMaxTeacher]; // 老师团队
    std::string student_id_[kCourseMaxSize];    // 学生ID
};

#endif