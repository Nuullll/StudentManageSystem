#ifndef COURSE_H
#define COURSE_H 

#include <string>
#include <vector>

const int kCourseMaxSize = 400;         // 课容量最大值
const int kCourseMaxTeacher = 5;        // 课程老师最大值(包括主讲老师,助教等)

class Course
{
public:
    Course() {}
    Course(std::string id, std::string name, int credit, bool is_optional, bool is_scoring):
           id_(id), name_(name), credit_(credit), is_optional_(is_optional), is_scoring_(is_scoring) {}
    ~Course() {}

    std::string id(){ return id_; }
    std::string name(){ return name_; }
    int credit(){ return credit_; }
    bool is_optional(){ return is_optional_; }
    bool is_scoring(){ return is_scoring_; }
    std::vector<int> teacher_id(){ return teacher_id_; }
    std::vector<int> student_id(){ return student_id_; }
    void add_teacher(int teacher_id);
    void add_student(int student_id);
    void update();
    void display();
    void update_score();

    friend bool operator ==(Course &c, std::string id){ return (c.id_ == id) || (c.name_ == id); }
    friend std::ifstream &operator >>(std::ifstream &in, Course &c);
    friend std::ofstream &operator <<(std::ofstream &of, const Course &c);

private:
    std::string id_;                            // 课程ID
    std::string name_;                          // 课程名称
    int credit_;                                // 学分
    bool is_optional_;                          // 是否任选(非任选则为必修限选课程)
    bool is_scoring_;                           // 是否记分
    std::vector<int> teacher_id_;      // 老师团队
    std::vector<int> student_id_;      // 学生ID
};

#endif