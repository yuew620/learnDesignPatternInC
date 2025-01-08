#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 前向声明
typedef struct Person2 Person2;

// 定义方法表结构体
typedef struct Person2_operation {
    void (*sayHello)(Person2*);
    const char* (*getName)(Person2*);
    void (*setName)(Person2*, const char*);
    int (*getAge)(Person2*);
    void (*setAge)(Person2*, int);
} Person2_operation;

// 定义Person2结构体
struct Person2 {
    char* name;
    int age;
    Person2_operation* optr;
};

// Person2方法的实现 - 移除static
void person2_sayHello(Person2* this) {
    printf("Hello, I am %s, %d years old.\n", this->name, this->age);
}

const char* person2_getName(Person2* this) {
    return this->name;
}

void person2_setName(Person2* this, const char* name) {
    if (this->name != NULL) {
        free(this->name);
    }
    this->name = strdup(name);
}

int person2_getAge(Person2* this) {
    return this->age;
}

void person2_setAge(Person2* this, int age) {
    this->age = age;
}

// 方法表 - 可以选择是否保留static
Person2_operation person2_op = {
    .sayHello = person2_sayHello,
    .getName = person2_getName,
    .setName = person2_setName,
    .getAge = person2_getAge,
    .setAge = person2_setAge
};

// 构造函数
Person2* Person2_new(const char* name, int age) {
    Person2* person2 = (Person2*)malloc(sizeof(Person2));
    if (person2 != NULL) {
        person2->name = strdup(name);
        person2->age = age;
        person2->optr = &person2_op;
    }
    return person2;
}

// 析构函数
void Person2_delete(Person2* person2) {
    if (person2 != NULL) {
        if (person2->name != NULL) {
            free(person2->name);
        }
        free(person2);
    }
}

int main() {
    Person2* p = Person2_new("John", 25);
    p->optr->sayHello(p);
    p->optr->setAge(p, 26);
    p->optr->setName(p, "John Doe");
    p->optr->sayHello(p);
    Person2_delete(p);
    return 0;
}
