#ifndef PERSON_H
#define PERSON_H

// 前向声明
typedef struct Person Person;

// 定义Person结构体
struct Person {
    char* name;
    int age;
    
    // 方法
    void (*sayHello)(Person*);
    const char* (*getName)(Person*);
    void (*setName)(Person*, const char*);
    int (*getAge)(Person*);
    void (*setAge)(Person*, int);
};

// 构造和析构函数声明
Person* Person_new(const char* name, int age);
void Person_delete(Person* person);

#endif // PERSON_H
