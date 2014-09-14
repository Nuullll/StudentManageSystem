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
    User():identity_(-1){}
    User(UserType identity, int id, std::string password):
        identity_(identity), id_(id), password_(password) {}
    virtual ~User();

    virtual void print() = 0;
    virtual void update() = 0;  // 更新全局vector
    friend bool operator ==(User &u, int id){ return u.id_ == id; }
    UserType identity() { return identity_; }
    int id() { return id_; }
    void set_password();


protected:
    UserType identity_;         // 用户身份
    int id_;                    // 用户ID
    std::string password_;      // 登录管理系统所用密码
};

bool ValidPassword(std::string password);   // 判断密码是否符合标准.(数字,大小写字母的6-15位组合)


class Administrator: public User        // 继承自user抽象类
{
public:
    Administrator(){}
    Administrator(int id, std::string password): User(ADMINISTRATOR, id, password){}
    ~Administrator();

    void print() { std::cout << "管理员: " << id_ << std::endl; }
    void update();
    void add_user();    // 增加新用户
    void del_user();    // 删除用户
  
    friend std::ofstream &operator <<(std::ofstream &of, const Administrator &admin);

private:

};


class Teacher: virtual public User
{
public:
    Teacher(){}
    Teacher(int id, std::string password, std::string name, std::vector<std::string> course_id, bool is_head_teacher = 0, std::string class_id = 0): 
            User(TEACHER, id, password), name_(name), course_id_(course_id), is_head_teacher_(is_head_teacher), class_id_(class_id)
    {}
    ~Teacher();

    void print() { std::cout << name_ << "老师" << std::endl; }
    void update();
    std::string name() { return name_; }
    std::vector<std::string> course_id() { return course_id_; }
    bool is_head_teacher() { return is_head_teacher_; }
    std::string class_id() { return class_id_; }
    void diplay_class();
    void add_course();

    friend std::ofstream &operator <<(std::ofstream &of, const Teacher &t);

private:
    std::string name_;                               // 老师姓名
    std::vector<std::string> course_id_;             // 课程ID
    bool is_head_teacher_;                           // 是否班主任
    std::string class_id_;                           // 若是班主任,班级ID
};


const int kStudentMaxCredit = 32;       // 单学期学分上限

class Student: virtual public User
{
public:
    Student(){}
    Student(int id, std::string password, std::string name, std::string class_id, 
            std::vector<std::string> course_id):
            User(STUDENT, id, password), name_(name), class_id_(class_id), course_id_(course_id) 
    {}
    ~Student();

    void print() { std::cout << name_ << "同学 " << '(' << id_ << ')' << std::endl; }
    void update();
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


class TeachingAssistant: public Teacher, public Student
{
public:
    TeachingAssistant(){};
    TeachingAssistant(int id, std::string password, std::string name, std::vector<std::string> teach_course_id, 
                    std::vector<std::string> learn_course_id, std::string class_id):
                    User(TEACHING_ASSISTANT, id, password), Teacher(id, password, name, teach_course_id), 
                    Student(id, password, name, class_id, learn_course_id) {};

    void print() { std::cout << Teacher::name() << "助教 " << std::endl; }
    void update();
    friend std::ofstream &operator <<(std::ofstream &of, const TeachingAssistant &ta);
private:

};



#endif