#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 前向声明
typedef struct Person0 Person0;

// 定义Person0 结构体
struct Person0 {
    char* name;
    int age;
};

// Person0方法的实现
void Person0_sayHello(Person0* this) {
    printf("Hello, I am %s, %d years old.\n", this->name, this->age);
}

const char* Person0_getName(Person0* this) {
    return this->name;
}

void Person0_setName(Person0* this, const char* name) {
    if (this->name != NULL) {
        free(this->name);
    }
    this->name = strdup(name);
}

int Person0_getAge(Person0* this) {
    return this->age;
}

void Person0_setAge(Person0* this, int age) {
    this->age = age;
}

// 构造函数
Person0* Person0_new(const char* name, int age) {
    Person0* person0 = (Person0*)malloc(sizeof(Person0));
    if (person0 != NULL) {
        person0->name = strdup(name);
        person0->age = age;
    }
    return person0;
}

// 析构函数
void Person0_delete(Person0* person0) {
    if (person0 != NULL) {
        if (person0->name != NULL) {
            free(person0->name);
        }
        free(person0);
    }
}

int main() {
    Person0* p = Person0_new("John", 25);
    Person0_sayHello(p);
    Person0_setAge(p, 26);
    Person0_setName(p, "John Doe");
    Person0_sayHello(p);
    Person0_delete(p);
    return 0;
}
