#include "person.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Person方法的实现
static void person_sayHello(Person* this) {
    printf("Hello, I am %s, %d years old.\n", this->name, this->age);
}

static const char* person_getName(Person* this) {
    return this->name;
}

static void person_setName(Person* this, const char* name) {
    if (this->name != NULL) {
        free(this->name);
    }
    this->name = strdup(name);
}

static int person_getAge(Person* this) {
    return this->age;
}

static void person_setAge(Person* this, int age) {
    this->age = age;
}

// 构造函数
Person* Person_new(const char* name, int age) {
    Person* person = (Person*)malloc(sizeof(Person));
    if (person != NULL) {
        person->name = strdup(name);
        person->age = age;
        
        // 绑定方法
        person->sayHello = person_sayHello;
        person->getName = person_getName;
        person->setName = person_setName;
        person->getAge = person_getAge;
        person->setAge = person_setAge;
    }
    return person;
}

// 析构函数
void Person_delete(Person* person) {
    if (person != NULL) {
        if (person->name != NULL) {
            free(person->name);
        }
        free(person);
    }
}
