#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 前向声明
typedef struct Person3 Person3;

// 定义虚函数表结构体
typedef struct Person3_vtable {
    void (*sayHello)(Person3*);
    const char* (*getName)(Person3*);
    void (*setName)(Person3*, const char*);
    int (*getAge)(Person3*);
    void (*setAge)(Person3*, int);
} Person3_vtable;

// 定义Person3结构体
struct Person3 {
    Person3_vtable* vptr;  // 放在第一位
    char* name;
    int age;
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

// 虚函数表
Person3_vtable person3_vtbl = {
    .sayHello = person3_sayHello,
    .getName = person3_getName,
    .setName = person3_setName,
    .getAge = person3_getAge,
    .setAge = person3_setAge
};

// 构造函数
Person3* Person3_new(const char* name, int age) {
    Person3* person3 = (Person3*)malloc(sizeof(Person3));
    if (person3 != NULL) {
        person3->vptr = &person3_vtbl;  // 初始化 vptr
        person3->name = strdup(name);
        person3->age = age;
    }
    return person3;
}

// 析构函数
void Person3_delete(Person3* person3) {
    if (person3 != NULL) {
        if (person3->name != NULL) {
            free(person3->name);
        }
        free(person3);
    }
}

int main() {
    Person3* p = Person3_new("John", 25);
    p->vptr->sayHello(p);
    p->vptr->setAge(p, 26);
    p->vptr->setName(p, "John Doe");
    p->vptr->sayHello(p);
    Person3_delete(p);
    return 0;
}
