#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 前向声明
typedef struct Person1 Person1;

// 定义Person1结构体
struct Person1 {
    char* name;
    int age;
    
    // 方法
    void (*sayHello)(Person1*);
    const char* (*getName)(Person1*);
    void (*setName)(Person1*, const char*);
    int (*getAge)(Person1*);
    void (*setAge)(Person1*, int);
};

// Person1方法的实现
static void person1_sayHello(Person1* this) {
    printf("Hello, I am %s, %d years old.\n", this->name, this->age);
}

static const char* person1_getName(Person1* this) {
    return this->name;
}

static void person1_setName(Person1* this, const char* name) {
    if (this->name != NULL) {
        free(this->name);
    }
    this->name = strdup(name);
}

static int person1_getAge(Person1* this) {
    return this->age;
}

static void person1_setAge(Person1* this, int age) {
    this->age = age;
}

// 构造函数
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

// 析构函数
void Person1_delete(Person1* person1) {
    if (person1 != NULL) {
        if (person1->name != NULL) {
            free(person1->name);
        }
        free(person1);
    }
}

int main() {
    Person1* p = Person1_new("John", 25);
    p->sayHello(p);
    p->setAge(p, 26);
    p->setName(p, "John Doe");
    p->sayHello(p);
    Person1_delete(p);
    return 0;
}