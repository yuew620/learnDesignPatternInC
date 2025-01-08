
+-------------------+
|      Person       |
+-------------------+
| - name: char*     |
| - age: int        |
+-------------------+
| + getName()       |
| + setName()       |
| + getAge()        |
| + setAge()        |
| + sayHello()      |
| + Person_new()    |
| + Person_delete() |
+-------------------+
          ▲
          |
          |
+-------------------+
|      Student      |
+-------------------+
| - studentId: int  |
+-------------------+
| + readBook()      |
| + getStudentId()  |
| + setStudentId()  |
| + sayHello()      |
| + Student_new()   |
| + Student_delete()|
+-------------------+



┌───────────────┐          ┌───────────────┐
│   Director    │─────────>│    Builder    │
└───────────────┘          └───────────────┘
                                  △
                                  │
                          ┌───────────────┐
                          │ConcreteBuilder│
                          └───────────────┘
                                  ¦
                                  v
                          ┌───────────────┐
                          │   Product     │
                          └───────────────┘


