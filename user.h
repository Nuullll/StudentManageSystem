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

class User
{
public:
    friend class Token;
    User(){}
    User(UserType identity, std::string id, std::string password):
        identity_(identity), id_(id), password_(password) {}
    virtual ~User();

    virtual void print() = 0;
    UserType identity() { return identity_; }
    std::string id() { return id_; }
    void set_password(std::string new_password);


protected:
    UserType identity_;         // 用户身份
    std::string id_;            // 用户ID
    std::string password_;      // 登录管理系统所用密码
};

///////////////////////////////////////////////////////////////////

class Administrator: public User        // 继承自user抽象类
{
public:
    Administrator(){}
    Administrator(std::string id, std::string password): User(ADMINISTRATOR, id, password)
    {}
    ~Administrator();

    void print() { std::cout << "管理员: " << id_ << std::endl; }

  
    friend std::ofstream &operator <<(std::ofstream &of, const Administrator &admin);

private:

};

//////////////////////////////////////////////////////////////////

class Teacher: virtual public User
{
public:
    Teacher(){}
    Teacher(std::string id, std::string password, std::string name, std::vector<std::string> course_id, bool is_head_teacher = 0, std::string class_id = 0): 
            User(TEACHER, id, password), name_(name), course_id_(course_id), is_head_teacher_(is_head_teacher), class_id_(class_id)
    {}
    ~Teacher();

    void print() { std::cout << name_ << "老师" << std::endl; }
    std::string name() { return name_; }
    std::vector<std::string> courses() { return course_id_; }
    bool is_head_teacher() { return is_head_teacher_; }
    std::string class_id() { return class_id_; }

    friend std::ofstream &operator <<(std::ofstream &of, const Teacher &t);

private:
    std::string name_;                               // 老师姓名
    std::vector<std::string> course_id_;             // 课程ID
    bool is_head_teacher_;                           // 是否班主任
    std::string class_id_;                           // 若是班主任,班级ID
};

/////////////////////////////////////////////////////////////////////////

const int kStudentMaxCredit = 32;       // 单学期学分上限

class Student: virtual public User
{
public:
    Student(){}
    Student(std::string id, std::string password, std::string name, std::string class_id, 
            std::vector<std::string> course_id):
            User(STUDENT, id, password), name_(name), class_id_(class_id), course_id_(course_id) 
    {}
    ~Student();

    void print() { std::cout << name_ << "同学 " << '(' << id_ << ')' << std::endl; }
    std::string name() { return name_; }
    std::string class_id() { return class_id_; }
    std::vector<std::string> course_id() { return course_id_; }
    std::vector<Score> score() { return score_; }

    friend std::ofstream &operator <<(std::ofstream &of, const Student &stu);

private:
    std::string name_;                              // 学生姓名
    std::string class_id_;                          // 班号
    std::vector<std::string> course_id_;            // 课程ID
    std::vector<Score> score_;                      // 各课程分数
};

////////////////////////////////////////////////////////////////////////////////

class TeachingAssistant: public Teacher, public Student
{
public:
    TeachingAssistant(){};
    TeachingAssistant(std::string id, std::string password, std::string name, std::vector<std::string> teach_course_id, 
                    std::vector<std::string> learn_course_id, std::string class_id):
                    User(TEACHING_ASSISTANT, id, password), Teacher(id, password, name, teach_course_id), 
                    Student(id, password, name, class_id, learn_course_id) {};

    friend std::ofstream &operator <<(std::ofstream &of, const TeachingAssistant &ta);
private:

};



#endif