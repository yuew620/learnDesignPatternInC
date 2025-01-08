#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student特有方法的实现
static void student_readBook(Student* this) {
    printf("%s (Student ID: %d) is reading a book.\n", 
           this->base.getName(&this->base), 
           this->studentId);
}

static int student_getStudentId(Student* this) {
    return this->studentId;
}

static void student_setStudentId(Student* this, int id) {
    this->studentId = id;
}

// Student的sayHello实现（覆盖Person的sayHello）
static void student_sayHello(Person* this) {
    Student* student = (Student*)this;  // 向下转型
    printf("Hello, I am student %s, my student ID is %d\n", 
           this->getName(this), 
           student->studentId);
}

// 构造函数
Student* Student_new(const char* name, int age, int studentId) {
    Student* student = (Student*)malloc(sizeof(Student));
    if (student != NULL) {
        // 初始化基类（Person）部分
        Person* base = (Person*)student;
        *base = *(Person_new(name, age));
        
        // 初始化Student特有的属性
        student->studentId = studentId;
        
        // 绑定Student特有的方法
        student->readBook = student_readBook;
        student->getStudentId = student_getStudentId;
        student->setStudentId = student_setStudentId;

        // 覆盖Person的sayHello方法
        student->base.sayHello = student_sayHello;
    }
    return student;
}

// 析构函数
void Student_delete(Student* student) {
    if (student != NULL) {
        Person_delete((Person*)student);
    }
}
