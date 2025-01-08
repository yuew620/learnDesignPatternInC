#include <stdio.h>

// 已存在的接口(计算华氏温度)
// 这是一个华氏温度传感器结构体，包含了温度值
typedef struct {
    float temperature_f;
} FahrenheitSensor;

// 初始化华氏温度传感器，将温度值设置为32°F
void fahrenheit_init(FahrenheitSensor* sensor) {
    sensor->temperature_f = 32.0;
}

// 读取华氏温度
float fahrenheit_get_temperature(FahrenheitSensor* sensor) {
    return sensor->temperature_f;
}

// 目标接口(摄氏温度)
// 这是一个适配器结构体，持有一个华氏温度传感器
typedef struct {
    FahrenheitSensor* f_sensor;
} CelsiusAdapter;

// 初始化适配器，传入一个华氏温度传感器
void celsius_adapter_init(CelsiusAdapter* adapter, FahrenheitSensor* sensor) {
    adapter->f_sensor = sensor;
}

// 转换并获取摄氏温度
// 这里实现了将华氏温度转换为摄氏温度的逻辑
float celsius_get_temperature(CelsiusAdapter* adapter) {
    float fahrenheit = fahrenheit_get_temperature(adapter->f_sensor);
    // 华氏温度转摄氏温度公式: (°F - 32) × 5/9 = °C
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

int main() {
    
    printf("***Run start***\n");
    // 创建华氏温度传感器
    FahrenheitSensor f_sensor;
    fahrenheit_init(&f_sensor);
    
    // 创建适配器
    CelsiusAdapter adapter;
    celsius_adapter_init(&adapter, &f_sensor);
    
    // 通过适配器获取摄氏温度
    float celsius = celsius_get_temperature(&adapter);
    printf("FahrenheitSensor temperature: %.1f F\n", fahrenheit_get_temperature(&f_sensor));
    printf("celsius_adapter temperature: %.1f C\n", celsius);
    
    return 0;
}
