#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person4 Person4;

// 定义函数指针类型
typedef void (*FuncSayHello)(Person4*);
typedef const char* (*FuncGetName)(Person4*);
typedef void (*FuncSetName)(Person4*, const char*);
typedef int (*FuncGetAge)(Person4*);
typedef void (*FuncSetAge)(Person4*, int);

// 将虚函数表改为函数指针数组
typedef void (*VTable[])(void);

struct Person4 {
    VTable* vptr;
    char* name;
    int age;
};

// Person4方法的实现
void person4_sayHello(Person4* this) {
    printf("Hello, I am %s, %d years old.\n", this->name, this->age);
}

const char* person4_getName(Person4* this) {
    return this->name;
}

void person4_setName(Person4* this, const char* name) {
    if (this->name != NULL) {
        free(this->name);
    }
    this->name = strdup(name);
}

int person4_getAge(Person4* this) {
    return this->age;
}

void person4_setAge(Person4* this, int age) {
    this->age = age;
}

// 虚函数表定义为函数指针数组
static VTable person4_vtbl = {
    (void(*)(void))person4_sayHello,
    (void(*)(void))person4_getName,
    (void(*)(void))person4_setName,
    (void(*)(void))person4_getAge,
    (void(*)(void))person4_setAge
};

// 构造函数
Person4* Person4_new(const char* name, int age) {
    Person4* person4 = (Person4*)malloc(sizeof(Person4));
    if (person4 != NULL) {
        person4->vptr = &person4_vtbl;
        person4->name = strdup(name);
        person4->age = age;
    }
    return person4;
}

// 析构函数
void Person4_delete(Person4* person4) {
    if (person4 != NULL) {
        if (person4->name != NULL) {
            free(person4->name);
        }
        free(person4);
    }
}

// 定义包装函数来调用虚函数表中的函数
void call_sayHello(Person4* obj) {
    ((FuncSayHello)(*obj->vptr)[0])(obj);
}

void call_setAge(Person4* obj, int age) {
    ((FuncSetAge)(*obj->vptr)[4])(obj, age);
}

void call_setName(Person4* obj, const char* name) {
    ((FuncSetName)(*obj->vptr)[2])(obj, name);
}

int main() {
    Person4* p = Person4_new("John", 25);
    
    // 使用包装函数调用方法
    call_sayHello(p);
    call_setAge(p, 26);
    call_setName(p, "John Doe");
    call_sayHello(p);

    Person4_delete(p);
    return 0;
}
