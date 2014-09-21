// user.h
// ������User������Administrator,Teacher,Student��,TeachingAssistant����ؼ̳���Teacher���Student��

#ifndef USER_H
#define USER_H 

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "score.h"

enum UserType { ADMINISTRATOR, TEACHER, STUDENT, TEACHING_ASSISTANT };
// �û����ͷ�Ϊ����Ա,��ʦ,ѧ��,�����������.

bool ValidPassword(std::string password);   // �ж������Ƿ���ϱ�׼.(����,��Сд��ĸ��6-15λ���)

class User
{
public:
    friend class Token;
    User() {}
    User(int identity, int id, std::string password): identity_(identity), id_(id), password_(password) {}
    virtual ~User() {}

    virtual void print() = 0;
    virtual void update() = 0;  // ����ȫ��vector
    bool operator ==(const int id){ return id_ == id; }
    int id() { return id_; }
    int identity() { return identity_; }
    void set_password();

protected:
    int identity_;         // �û����
    int id_;                    // �û�ID
    std::string password_;      // ��¼����ϵͳ��������
};



class Administrator: public User        // �̳���user������
{
public:
    Administrator() {}
    Administrator(int id, std::string password): User(ADMINISTRATOR, id, password){}
    ~Administrator() {}

    void add_user();    // �������û�
    void del_user();    // ɾ���û�
    void print() { std::cout << "����Ա: " << id_ << std::endl; }
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
    void print() { std::cout << name_ << "��ʦ" << std::endl; }
    void update();
    friend std::ifstream &operator >>(std::ifstream &in, Teacher &t);
    friend std::ofstream &operator <<(std::ofstream &of, const Teacher &t);

protected:
    std::string name_;                               // ��ʦ����
    std::vector<std::string> course_id_;             // �γ�ID
    bool is_head_teacher_;                           // �Ƿ������
    std::string class_id_;                           // ���ǰ�����,�༶ID
};


const int kStudentMaxCredit = 32;       // ��ѧ��ѧ������

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
    void print() { std::cout << name_ << "ͬѧ " << '(' << id_ << ')' << std::endl; }
    void update();
    friend std::ifstream &operator >>(std::ifstream &in, Student &stud);
    friend std::ofstream &operator <<(std::ofstream &of, const Student &stu);

protected:
    std::string name_;                              // ѧ������
    std::string class_id_;                          // ���
    std::vector<std::string> course_id_;            // �γ�ID
    std::vector<Score> score_;                      // ���γ̷���
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

    void print() { std::cout << Teacher::name() << "���� " << std::endl; }
    void update();
    friend std::ifstream &operator >>(std::ifstream &in, TeachingAssistant &ta);
    friend std::ofstream &operator <<(std::ofstream &of, const TeachingAssistant &ta);
};



#endif