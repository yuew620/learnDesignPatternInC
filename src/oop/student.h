#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

// 前向声明
typedef struct Student Student;

// 定义Student结构体
struct Student {
    // 继承Person的所有成员
    Person base;
    
    // Student特有的成员
    int studentId;
    
    // Student特有的方法
    void (*readBook)(Student*);
    int (*getStudentId)(Student*);
    void (*setStudentId)(Student*, int);
};

// 构造和析构函数声明
Student* Student_new(const char* name, int age, int studentId);
void Student_delete(Student* student);

#endif // STUDENT_H
