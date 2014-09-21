// user.h
// 抽象类User派生出Administrator,Teacher,Student类,TeachingAssistant类多重继承自Teacher类和Student类

#ifndef USER_H
#define USER_H 

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "score.h"

enum UserType { ADMINISTRATOR, TEACHER, STUDENT, TEACHING_ASSISTANT };
// 用户类型分为管理员,老师,学生,助教四种身份.

bool ValidPassword(std::string password);   // 判断密码是否符合标准.(数字,大小写字母的6-15位组合)

class User
{
public:
    friend class Token;
    User() {}
    User(int identity, int id, std::string password): identity_(identity), id_(id), password_(password) {}
    virtual ~User() {}

    virtual void print() = 0;
    virtual void update() = 0;  // 更新全局vector
    bool operator ==(const int id){ return id_ == id; }
    int id() { return id_; }
    int identity() { return identity_; }
    void set_password();

protected:
    int identity_;         // 用户身份
    int id_;                    // 用户ID
    std::string password_;      // 登录管理系统所用密码
};



class Administrator: public User        // 继承自user抽象类
{
public:
    Administrator() {}
    Administrator(int id, std::string password): User(ADMINISTRATOR, id, password){}
    ~Administrator() {}

    void add_user();    // 增加新用户
    void del_user();    // 删除用户
    void print() { std::cout << "管理员: " << id_ << std::endl; }
    void update();

    friend std::ifstream &operator >>(std::ifstream &in, Administrator &admin);
    friend std::ofstream &operator <<(std::ofstream &of, const Administrator &admin);
};


class Teacher: virtual public User
{
public:
	Teacher():User(), name_(), course_id_(), is_head_teacher_(0), class_id_() { course_id_.reserve(100); }
    Teacher(int id, std::string password, std::string name, std::vector<std::string> course_id, bool is_head_teacher = 0, std::string class_id = 0): 
            User(TEACHER, id, password), name_(name), course_id_(course_id), is_head_teacher_(is_head_teacher), class_id_(class_id) {}
    ~Teacher() {}

    bool is_head_teacher() { return is_head_teacher_; }
    std::string class_id() { return class_id_; }
    std::string name() { return name_; }
    std::vector<std::string> course_id() const { return course_id_; }
    void add_course();
    void display_class();
    void print() { std::cout << name_ << "老师" << std::endl; }
    void update();
    friend std::ifstream &operator >>(std::ifstream &in, Teacher &t);
    friend std::ofstream &operator <<(std::ofstream &of, const Teacher &t);

protected:
    std::string name_;                               // 老师姓名
    std::vector<std::string> course_id_;             // 课程ID
    bool is_head_teacher_;                           // 是否班主任
    std::string class_id_;                           // 若是班主任,班级ID
};


const int kStudentMaxCredit = 32;       // 单学期学分上限

class Student: virtual public User
{
public:
	Student():User(), name_(), class_id_(), course_id_(), score_() { course_id_.reserve(100), score_.reserve(100); }
    Student(int id, std::string password, std::string name, std::string class_id, 
            std::vector<std::string> course_id):
            User(STUDENT, id, password), name_(name), class_id_(class_id), course_id_(course_id) {}
    ~Student() {}

    double gpa();
    int credit();
    std::string class_id() { return class_id_; }
    std::string name() { return name_; }
    std::vector<Score> score() { return score_; }
    std::vector<std::string> course_id() const { return course_id_; }
    void add_course();
    void add_score(Score score);
    void course_info();
    void display_gpa_info();
    void print() { std::cout << name_ << "同学 " << '(' << id_ << ')' << std::endl; }
    void update();
    friend std::ifstream &operator >>(std::ifstream &in, Student &stud);
    friend std::ofstream &operator <<(std::ofstream &of, const Student &stu);

protected:
    std::string name_;                              // 学生姓名
    std::string class_id_;                          // 班号
    std::vector<std::string> course_id_;            // 课程ID
    std::vector<Score> score_;                      // 各课程分数
};

bool CompareStudent(Student stu1, Student stu2);

class TeachingAssistant: public Teacher, public Student
{
public:
    TeachingAssistant():User(), Teacher(), Student() {}
    TeachingAssistant(int id, std::string password, std::string name, std::vector<std::string> teach_course_id, 
                      std::vector<std::string> learn_course_id, std::string class_id):
                      User(TEACHING_ASSISTANT, id, password), Teacher(id, password, name, teach_course_id), 
                      Student(id, password, name, class_id, learn_course_id) {}
    ~TeachingAssistant() {}

    void print() { std::cout << Teacher::name() << "助教 " << std::endl; }
    void update();
    friend std::ifstream &operator >>(std::ifstream &in, TeachingAssistant &ta);
    friend std::ofstream &operator <<(std::ofstream &of, const TeachingAssistant &ta);
};



#endif