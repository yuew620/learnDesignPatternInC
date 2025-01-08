#include <stdio.h>
#include <stdlib.h>

// 定义策略接口（函数指针）
typedef void (*SortStrategy)(int*, int);

// 具体策略1：冒泡排序
void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("Using Bubble Sort\n");
}

// 具体策略2：选择排序
void selectionSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
    printf("Using Selection Sort\n");
}

// 上下文结构体
typedef struct {
    SortStrategy strategy;  // 策略函数指针
} Context;

// 初始化上下文
void initContext(Context* ctx, SortStrategy strategy) {
    ctx->strategy = strategy;
}

// 执行策略
void executeStrategy(Context* ctx, int* arr, int size) {
    ctx->strategy(arr, size);
}

// 打印数组
void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);
    Context ctx;

    // 使用冒泡排序策略
    printf("Original array: ");
    printArray(arr, size);
    
    initContext(&ctx, bubbleSort);
    executeStrategy(&ctx, arr, size);
    
    printf("Sorted array: ");
    printArray(arr, size);

    // 重置数组
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    
    // 使用选择排序策略
    printf("\nOriginal array: ");
    printArray(arr2, size);
    
    initContext(&ctx, selectionSort);
    executeStrategy(&ctx, arr2, size);
    
    printf("Sorted array: ");
    printArray(arr2, size);

    return 0;
}
