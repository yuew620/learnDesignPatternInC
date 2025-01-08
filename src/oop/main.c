#include <stdio.h>
#include "person.h"
#include "student.h"

// 通用函数，接收Person指针，展示多态
void displayInfo(Person* person) {
    printf("\n--- Displaying Person Info ---\n");
    printf("Name: %s\n", person->getName(person));
    printf("Age: %d\n", person->getAge(person));
}

void displaySayHello(Person* person) {
    printf("\n---  Person displaySayHello ---\n");
    person->sayHello(person);  // 这里会根据实际对象类型调用相应的sayHello
}

int main() {
    printf("\n=== 继承和多态演示 ===\n");

    // 1. 创建一个Person对象
    printf("\n1. 创建并测试Person对象：\n");
    Person* person = Person_new("Alice", 30);
    displayInfo(person);

    // 2. 创建一个Student对象
    printf("\n2. 创建并测试Student对象：\n");
    Student* student = Student_new("Bob", 20, 12345);
    displayInfo((Person*)student);
    
    // 3. 展示继承：Student可以访问Person的方法
    printf("\n3. 展示继承 - 直接通过Student访问Person的方法：\n");
    printf("Student name: %s\n", student->base.getName(&student->base));
    printf("Student age: %d\n", student->base.getAge(&student->base));
    
    // 4. 展示Student特有的方法
    printf("\n4. 展示Student特有的方法：\n");
    student->readBook(student);
    printf("Student ID: %d\n", student->getStudentId(student));

    // 5. 展示多态：将Student转换为Person并调用方法
    printf("\n5. 展示多态 - 通过Person指针调用方法：\n");
    displaySayHello(person);
    Person* studentAsPerson = (Person*)student;
    displaySayHello((Person*)studentAsPerson);  // 会调用Student重写的sayHello

    // 6. 修改属性后再次展示
    printf("\n6. 修改属性后的效果：\n");
    studentAsPerson->setName(studentAsPerson, "Bob Smith");
    studentAsPerson->setAge(studentAsPerson, 21);
    displayInfo(studentAsPerson);

    // 7. 验证是同一个对象
    printf("\n7. 验证对象一致性：\n");
    printf("通过Student指针访问：\n");
    student->base.sayHello(&student->base);
    printf("通过Person指针访问：\n");
    studentAsPerson->sayHello(studentAsPerson);

    // 清理内存
    printf("\n8. 清理内存...\n");
    Person_delete(person);
    Student_delete(student);

    return 0;
}
