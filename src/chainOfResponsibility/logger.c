#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义日志级别
#define INFO 1
#define DEBUG 2
#define ERROR 3

// 前向声明
struct AbstractLogger;

// 定义函数指针类型
typedef void (*WriteFunc)(char* message);
typedef void (*SetNextLoggerFunc)(struct AbstractLogger* self, struct AbstractLogger* next);
typedef void (*LogMessageFunc)(struct AbstractLogger* self, int level, char* message);

// 抽象日志记录器结构体
typedef struct AbstractLogger {
    int level;
    struct AbstractLogger* nextLogger;
    WriteFunc write;
    SetNextLoggerFunc setNextLogger;
    LogMessageFunc logMessage;
} AbstractLogger;

// 具体日志记录器结构体
typedef struct ConsoleLogger {
    AbstractLogger base;
} ConsoleLogger;

typedef struct ErrorLogger {
    AbstractLogger base;
} ErrorLogger;

typedef struct FileLogger {
    AbstractLogger base;
} FileLogger;

// 通用的logMessage实现
void logMessage(AbstractLogger* self, int level, char* message) {
    if (level >= self->level) {
        self->write(message);
    }
    if (self->nextLogger != NULL) {
        self->nextLogger->logMessage(self->nextLogger, level, message);
    }
}

// 设置下一个记录器
void setNextLogger(AbstractLogger* self, AbstractLogger* nextLogger) {
    self->nextLogger = nextLogger;
}

// ConsoleLogger实现
void consoleWrite(char* message) {
    printf("Console::Logger: %s\n", message);
}

AbstractLogger* createConsoleLogger(int level) {
    ConsoleLogger* logger = (ConsoleLogger*)malloc(sizeof(ConsoleLogger));
    logger->base.level = level;
    logger->base.nextLogger = NULL;
    logger->base.write = consoleWrite;
    logger->base.setNextLogger = setNextLogger;
    logger->base.logMessage = logMessage;
    return (AbstractLogger*)logger;
}

// ErrorLogger实现
void errorWrite(char* message) {
    printf("Error::Logger: %s\n", message);
}

AbstractLogger* createErrorLogger(int level) {
    ErrorLogger* logger = (ErrorLogger*)malloc(sizeof(ErrorLogger));
    logger->base.level = level;
    logger->base.nextLogger = NULL;
    logger->base.write = errorWrite;
    logger->base.setNextLogger = setNextLogger;
    logger->base.logMessage = logMessage;
    return (AbstractLogger*)logger;
}

// FileLogger实现
void fileWrite(char* message) {
    printf("File::Logger: %s\n", message);
}

AbstractLogger* createFileLogger(int level) {
    FileLogger* logger = (FileLogger*)malloc(sizeof(FileLogger));
    logger->base.level = level;
    logger->base.nextLogger = NULL;
    logger->base.write = fileWrite;
    logger->base.setNextLogger = setNextLogger;
    logger->base.logMessage = logMessage;
    return (AbstractLogger*)logger;
}

// 创建日志链
AbstractLogger* getChainOfLoggers() {
    AbstractLogger* errorLogger = createErrorLogger(ERROR);
    AbstractLogger* fileLogger = createFileLogger(DEBUG);
    AbstractLogger* consoleLogger = createConsoleLogger(INFO);

    errorLogger->setNextLogger(errorLogger, fileLogger);
    fileLogger->setNextLogger(fileLogger, consoleLogger);

    return errorLogger;
}

// 主函数示例
int main() {
    AbstractLogger* loggerChain = getChainOfLoggers();

    loggerChain->logMessage(loggerChain, INFO, "This is an information.");
    printf("\n");
    loggerChain->logMessage(loggerChain, DEBUG, "This is a debug level information.");
    printf("\n");
    loggerChain->logMessage(loggerChain, ERROR, "This is an error information.");

    // 释放内存
    // 注意：实际应用中需要properly释放整个链上的所有logger
    //free(loggerChain);
    
    return 0;
}
