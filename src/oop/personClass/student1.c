#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 前向声明
typedef struct Person1 Person1;
typedef struct Student1 Student1;

// Person1方法声明
void person1_sayHello(Person1* this);
const char* person1_getName(Person1* this);
void person1_setName(Person1* this, const char* name);
int person1_getAge(Person1* this);
void person1_setAge(Person1* this, int age);

// Student1方法声明
void student1_sayHello(Person1* this);
void student1_study(Student1* this);
const char* student1_getStudentID(Student1* this);
void student1_setStudentID(Student1* this, const char* id);

// Person1结构体定义
struct Person1 {
    char* name;
    int age;
    
    void (*sayHello)(Person1*);
    const char* (*getName)(Person1*);
    void (*setName)(Person1*, const char*);
    int (*getAge)(Person1*);
    void (*setAge)(Person1*, int);
};

// Student1结构体定义
struct Student1 {
    Person1 base;  // 继承Person1
    char* studentID;
    
    void (*study)(Student1*);
    const char* (*getStudentID)(Student1*);
    void (*setStudentID)(Student1*, const char*);
};


// 定义转换宏
#define AS_PERSON1_PTR(ptr) (&((ptr)->base))

// Person1方法的实现
void person1_sayHello(Person1* this) {
    printf("Hello, I am %s, %d years old.\n", this->name, this->age);
}

const char* person1_getName(Person1* this) {
    return this->name;
}

void person1_setName(Person1* this, const char* name) {
    if (this->name != NULL) {
        free(this->name);
    }
    this->name = strdup(name);
}

int person1_getAge(Person1* this) {
    return this->age;
}

void person1_setAge(Person1* this, int age) {
    this->age = age;
}

// Student1方法的实现
void student1_sayHello(Person1* this) {
    Student1* student = (Student1*)this;
    printf("Hello, I am student %s, %d years old, Student ID: %s\n", 
           this->name, this->age, student->studentID);
}

void student1_study(Student1* this) {
    printf("Student %s is studying...\n", this->base.name);
}

const char* student1_getStudentID(Student1* this) {
    return this->studentID;
}

void student1_setStudentID(Student1* this, const char* id) {
    if (this->studentID != NULL) {
        free(this->studentID);
    }
    this->studentID = strdup(id);
}

// Person1构造函数
Person1* Person1_new(const char* name, int age) {
    Person1* person1 = (Person1*)malloc(sizeof(Person1));
    if (person1 != NULL) {
        person1->name = strdup(name);
        person1->age = age;
        
        // 绑定方法
        person1->sayHello = person1_sayHello;
        person1->getName = person1_getName;
        person1->setName = person1_setName;
        person1->getAge = person1_getAge;
        person1->setAge = person1_setAge;
    }
    return person1;
}

// Student1构造函数
Student1* Student1_new(const char* name, int age, const char* studentID) {
    Student1* student1 = (Student1*)malloc(sizeof(Student1));
    if (student1 != NULL) {
        // 初始化基类部分
        student1->base.name = strdup(name);
        student1->base.age = age;
        
        // 初始化子类特有成员
        student1->studentID = strdup(studentID);
        
        // 绑定基类方法（注意sayHello被覆盖）
        student1->base.sayHello = student1_sayHello;
        student1->base.getName = person1_getName;
        student1->base.setName = person1_setName;
        student1->base.getAge = person1_getAge;
        student1->base.setAge = person1_setAge;
        
        // 绑定子类特有方法
        student1->study = student1_study;
        student1->getStudentID = student1_getStudentID;
        student1->setStudentID = student1_setStudentID;
    }
    return student1;
}

// Person1析构函数
void Person1_delete(Person1* person1) {
    if (person1 != NULL) {
        if (person1->name != NULL) {
            free(person1->name);
        }
        free(person1);
    }
}

// Student1析构函数
void Student1_delete(Student1* student1) {
    if (student1 != NULL) {
        if (student1->base.name != NULL) {
            free(student1->base.name);
        }
        if (student1->studentID != NULL) {
            free(student1->studentID);
        }
        free(student1);
    }
}

int main() {
    // 测试Person1
    Person1* p = Person1_new("John", 25);
    p->sayHello(p);
    Person1_delete(p);

    // 测试Student1
    Student1* s = Student1_new("Tom", 20, "S123");
    s->base.sayHello((Person1*)s);

    // 或者这样写：
    Person1* p2 = (Person1*)s;  // 向上转型
    p2->sayHello(p2);         // 通过基类指针调用

    //  或者这样写： 使用宏进行转换
    Person1* p3 = AS_PERSON1_PTR(s);
    // 调用方法
    p3->sayHello(p3);  // 输出: Student Hello

    Student1_delete(s);

    return 0;
}
