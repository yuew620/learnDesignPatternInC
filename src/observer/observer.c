
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大观察者数量
#define MAX_OBSERVERS 10

// 天气数据结构
typedef struct {
    float temperature;
    float humidity;
    float pressure;
} WeatherData;

// 观察者接口（函数指针）
typedef void (*ObserverCallback)(WeatherData data);

// 主题（被观察者）结构
typedef struct {
    WeatherData data;
    ObserverCallback observers[MAX_OBSERVERS];
    int observerCount;
} WeatherStation;

// 初始化气象站
void initWeatherStation(WeatherStation* station) {
    station->observerCount = 0;
    station->data.temperature = 0.0f;
    station->data.humidity = 0.0f;
    station->data.pressure = 0.0f;
}

// 注册观察者
void registerObserver(WeatherStation* station, ObserverCallback observer) {
    if (station->observerCount < MAX_OBSERVERS) {
        station->observers[station->observerCount++] = observer;
    }
}

// 通知所有观察者
void notifyObservers(WeatherStation* station) {
    for (int i = 0; i < station->observerCount; i++) {
        station->observers[i](station->data);
    }
}

// 设置气象数据
void setMeasurements(WeatherStation* station, float temperature, 
                     float humidity, float pressure) {
    station->data.temperature = temperature;
    station->data.humidity = humidity;
    station->data.pressure = pressure;
    notifyObservers(station);
}

// 观察者1：显示当前状况
void currentConditionsDisplay(WeatherData data) {
    printf("Current conditions: %.1fF degrees and %.1f%% humidity\n",
           data.temperature, data.humidity);
}

// 观察者2：显示气象统计
void statisticsDisplay(WeatherData data) {
    printf("Avg/Max/Min temperature = %.1f/%.1f/%.1f\n",
           data.temperature, data.temperature + 2, data.temperature - 2);
}

// 观察者3：显示天气预报
void forecastDisplay(WeatherData data) {
    if (data.pressure < 1000)
        printf("Forecast: Watch out for cooler, rainy weather\n");
    else
        printf("Forecast: Improving weather on the way!\n");
}

int main() {
    // 创建气象站
    WeatherStation station;
    initWeatherStation(&station);

    // 注册观察者
    registerObserver(&station, currentConditionsDisplay);
    registerObserver(&station, statisticsDisplay);
    registerObserver(&station, forecastDisplay);

    // 模拟气象测量
    printf("First weather update:\n");
    setMeasurements(&station, 80, 65, 1012.2f);
    
    printf("\nSecond weather update:\n");
    setMeasurements(&station, 82, 70, 995.5f);

    return 0;
}
