#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 前向声明
typedef struct Person3 Person3;
typedef struct Student3 Student3;

// 定义Person3的虚函数表结构体
typedef struct Person3_vtable {
    void (*sayHello)(Person3*);
    const char* (*getName)(Person3*);
    void (*setName)(Person3*, const char*);
    int (*getAge)(Person3*);
    void (*setAge)(Person3*, int);
} Person3_vtable;

// 定义Student3的虚函数表结构体
typedef struct Student3_vtable {
    void (*sayHello)(Student3*);
    const char* (*getName)(Student3*);
    void (*setName)(Student3*, const char*);
    int (*getAge)(Student3*);
    void (*setAge)(Student3*, int);
    void (*study)(Student3*);
    const char* (*getStudentID)(Student3*);
    void (*setStudentID)(Student3*, const char*);
} Student3_vtable;

// 定义Person3结构体
struct Person3 {
    Person3_vtable* vptr;
    char* name;
    int age;
};

// 定义Student3结构体
struct Student3 {
    Person3 base;  // 继承Person3
    char* studentID;
};

// Person3方法的实现
void person3_sayHello(Person3* this) {
    printf("Hello, I am %s, %d years old.\n", this->name, this->age);
}

const char* person3_getName(Person3* this) {
    return this->name;
}

void person3_setName(Person3* this, const char* name) {
    if (this->name != NULL) {
        free(this->name);
    }
    this->name = strdup(name);
}

int person3_getAge(Person3* this) {
    return this->age;
}

void person3_setAge(Person3* this, int age) {
    this->age = age;
}

// Student3方法的实现
void student3_sayHello(Student3* this) {
    printf("Hello, I am student %s, %d years old, ID: %s\n", 
           this->base.name, this->base.age, this->studentID);
}

void student3_study(Student3* this) {
    printf("Student %s is studying\n", this->base.name);
}

const char* student3_getStudentID(Student3* this) {
    return this->studentID;
}

void student3_setStudentID(Student3* this, const char* id) {
    if (this->studentID != NULL) {
        free(this->studentID);
    }
    this->studentID = strdup(id);
}

// Person3的虚函数表
Person3_vtable person3_vtbl = {
    .sayHello = person3_sayHello,
    .getName = person3_getName,
    .setName = person3_setName,
    .getAge = person3_getAge,
    .setAge = person3_setAge
};

// Student3的虚函数表
Student3_vtable student3_vtbl = {
    .sayHello = student3_sayHello,
    .getName = (const char* (*)(Student3*))person3_getName,
    .setName = (void (*)(Student3*, const char*))person3_setName,
    .getAge = (int (*)(Student3*))person3_getAge,
    .setAge = (void (*)(Student3*, int))person3_setAge,
    .study = student3_study,
    .getStudentID = student3_getStudentID,
    .setStudentID = student3_setStudentID
};


// Person3构造函数
Person3* Person3_new(const char* name, int age) {
    Person3* person3 = (Person3*)malloc(sizeof(Person3));
    if (person3 != NULL) {
        person3->vptr = &person3_vtbl;
        person3->name = strdup(name);
        person3->age = age;
    }
    return person3;
}

// Student3构造函数
Student3* Student3_new(const char* name, int age, const char* studentID) {
    Student3* student3 = (Student3*)malloc(sizeof(Student3));
    if (student3 != NULL) {
        student3->base.vptr = (Person3_vtable*)&student3_vtbl;
        student3->base.name = strdup(name);
        student3->base.age = age;
        student3->studentID = strdup(studentID);
    }
    return student3;
}

// Person3析构函数
void Person3_delete(Person3* person3) {
    if (person3 != NULL) {
        if (person3->name != NULL) {
            free(person3->name);
        }
        free(person3);
    }
}

// Student3析构函数
void Student3_delete(Student3* student3) {
    if (student3 != NULL) {
        if (student3->base.name != NULL) {
            free(student3->base.name);
        }
        if (student3->studentID != NULL) {
            free(student3->studentID);
        }
        free(student3);
    }
}

int main() {
    // 测试Person3
    Person3* p = Person3_new("John", 25);
    p->vptr->sayHello(p);
    p->vptr->setAge(p, 26);
    p->vptr->setName(p, "John Doe");
    p->vptr->sayHello(p);
    Person3_delete(p);

    // 测试Student3
    Student3* s = Student3_new("Alice", 20, "S001");
    Student3_vtable* vtbl = (Student3_vtable*)s->base.vptr;
    vtbl->sayHello(s);
    vtbl->setAge(s, 21);
    vtbl->setName(s, "Alice Smith");
    vtbl->setStudentID(s, "S002");
    vtbl->study(s);
    vtbl->sayHello(s);
    Student3_delete(s);

    return 0;
}
