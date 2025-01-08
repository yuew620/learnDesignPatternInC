#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Product
typedef struct {
    char* cpu;
    char* memory;
    char* storage;
} Computer;

// 创建 Computer
Computer* createComputer() {
    Computer* computer = (Computer*)malloc(sizeof(Computer));
    computer->cpu = NULL;
    computer->memory = NULL;
    computer->storage = NULL;
    return computer;
}

// 释放 Computer
void freeComputer(Computer* computer) {
    if (computer) {
        free(computer->cpu);
        free(computer->memory);
        free(computer->storage);
        free(computer);
    }
}

// Abstract Builder
typedef struct {
    Computer* computer;
    void (*setCPU)(Computer*, const char*);
    void (*setMemory)(Computer*, const char*);
    void (*setStorage)(Computer*, const char*);
    Computer* (*getResult)(Computer*);
} ComputerBuilder;

// 通用设置方法
void setCPU(Computer* computer, const char* cpu) {
    if (computer->cpu) free(computer->cpu);
    computer->cpu = strdup(cpu);
}

void setMemory(Computer* computer, const char* memory) {
    if (computer->memory) free(computer->memory);
    computer->memory = strdup(memory);
}

void setStorage(Computer* computer, const char* storage) {
    if (computer->storage) free(computer->storage);
    computer->storage = strdup(storage);
}

Computer* getResult(Computer* computer) {
    return computer;
}

// Concrete Builders
typedef struct {
    ComputerBuilder base;
} GamingComputerBuilder;

typedef struct {
    ComputerBuilder base;
} OfficeComputerBuilder;

// Gaming Computer 构建方法
void gamingSetCPU(Computer* computer, const char* cpu) {
    setCPU(computer, "Intel i9-12900K");
}

void gamingSetMemory(Computer* computer, const char* memory) {
    setMemory(computer, "32GB DDR5");
}

void gamingSetStorage(Computer* computer, const char* storage) {
    setStorage(computer, "2TB NVMe SSD");
}

// Office Computer 构建方法
void officeSetCPU(Computer* computer, const char* cpu) {
    setCPU(computer, "Intel i5-12400");
}

void officeSetMemory(Computer* computer, const char* memory) {
    setMemory(computer, "16GB DDR4");
}

void officeSetStorage(Computer* computer, const char* storage) {
    setStorage(computer, "512GB SSD");
}

// 创建具体的 Builder
GamingComputerBuilder* createGamingComputerBuilder() {
    GamingComputerBuilder* builder = (GamingComputerBuilder*)malloc(sizeof(GamingComputerBuilder));
    builder->base.computer = createComputer();
    builder->base.setCPU = gamingSetCPU;
    builder->base.setMemory = gamingSetMemory;
    builder->base.setStorage = gamingSetStorage;
    builder->base.getResult = getResult;
    return builder;
}

OfficeComputerBuilder* createOfficeComputerBuilder() {
    OfficeComputerBuilder* builder = (OfficeComputerBuilder*)malloc(sizeof(OfficeComputerBuilder));
    builder->base.computer = createComputer();
    builder->base.setCPU = officeSetCPU;
    builder->base.setMemory = officeSetMemory;
    builder->base.setStorage = officeSetStorage;
    builder->base.getResult = getResult;
    return builder;
}

// 释放 Builder
void freeBuilder(ComputerBuilder* builder) {
    if (builder) {
        freeComputer(builder->computer);
        free(builder);
    }
}

// Director
typedef struct Director {
    ComputerBuilder* builder;
    void (*setBuilder)(struct Director*, ComputerBuilder*);
    void (*constructComputer)(struct Director*);
} Director;

// Director 的方法实现
void setBuilder(Director* director, ComputerBuilder* builder) {
    director->builder = builder;
}

void constructComputer(Director* director) {
    if (director->builder == NULL) return;
    
    director->builder->setCPU(director->builder->computer, NULL);
    director->builder->setMemory(director->builder->computer, NULL);
    director->builder->setStorage(director->builder->computer, NULL);
}

// 创建 Director
Director* createDirector() {
    Director* director = (Director*)malloc(sizeof(Director));
    director->builder = NULL;
    director->setBuilder = setBuilder;
    director->constructComputer = constructComputer;
    return director;
}

// 释放 Director
void freeDirector(Director* director) {
    if (director) {
        free(director);
    }
}

// 打印电脑配置
void printComputerSpecs(Computer* computer) {
    printf("Computer Specifications:\n");
    printf("CPU: %s\n", computer->cpu);
    printf("Memory: %s\n", computer->memory);
    printf("Storage: %s\n", computer->storage);
}

// Main 函数
int main() {
    // 创建 director
    Director* director = createDirector();
    
    // 创建不同的 builder
    GamingComputerBuilder* gamingBuilder = createGamingComputerBuilder();
    OfficeComputerBuilder* officeBuilder = createOfficeComputerBuilder();
    
    // 构建游戏电脑
    printf("Building a Gaming Computer...\n");
    director->setBuilder(director, (ComputerBuilder*)gamingBuilder);
    director->constructComputer(director);
    Computer* gamingComputer = gamingBuilder->base.getResult(gamingBuilder->base.computer);
    printComputerSpecs(gamingComputer);
    
    // 构建办公电脑
    printf("\nBuilding an Office Computer...\n");
    director->setBuilder(director, (ComputerBuilder*)officeBuilder);
    director->constructComputer(director);
    Computer* officeComputer = officeBuilder->base.getResult(officeBuilder->base.computer);
    printComputerSpecs(officeComputer);
    
    // 清理内存
    freeBuilder((ComputerBuilder*)gamingBuilder);
    freeBuilder((ComputerBuilder*)officeBuilder);
    freeDirector(director);
    
    return 0;
}
