#ifndef COURSE_H
#define COURSE_H 

#include <string>
#include <vector>

const int kCourseMaxSize = 400;         // 课容量最大值
const int kCourseMaxTeacher = 5;        // 课程老师最大值(包括主讲老师,助教等)

class Course
{
public:
    Course();
    ~Course();

    std::string id(){ return id_; }
    std::string name(){ return name_; }
    int credit(){ return credit_; }
    bool is_optional(){ return is_optional_; }
    bool is_scoring(){ return is_scoring_; }
    double avg_score(){ return avg_score_; }
    std::vector<int> teachers(){ return teachers_id_; }
    std::vector<int> students(){ return students_id_; }

private:
    std::string id_;                            // 课程ID
    std::string name_;                          // 课程名称
    int credit_;                                // 学分
    bool is_optional_;                          // 是否任选(非任选则为必修限选课程)
    bool is_scoring_;                           // 是否记分
    double avg_score_;                          // 该课程平均分(若记分)
    std::vector<int> teachers_id_;      // 老师团队
    std::vector<int> students_id_;      // 学生ID
};

#endif