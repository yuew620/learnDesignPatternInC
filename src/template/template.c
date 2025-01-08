#include <stdio.h>
#include <stdlib.h>

// 前向声明
typedef struct Beverage Beverage;
typedef struct BeverageOps BeverageOps;

// 操作函数指针定义
typedef void (*BoilWaterFunc)(void);
typedef void (*BrewFunc)(void);
typedef void (*PourFunc)(void);
typedef void (*AddCondimentsFunc)(void);
typedef int (*CustomerWantsCondimentsFunc)(void);

// 饮料操作接口结构
struct BeverageOps {
    BoilWaterFunc boilWater;
    BrewFunc brew;
    PourFunc pourInCup;
    CustomerWantsCondimentsFunc customerWantsCondiments;
    AddCondimentsFunc addCondiments;
};

// 基础饮料结构
struct Beverage {
    const char* name;
    BeverageOps* ops;
};

// 模板方法：准备饮料的通用流程
void prepareBeverage(Beverage* beverage) {
    if (beverage && beverage->ops) {
        // 烧水
        if (beverage->ops->boilWater) {
            beverage->ops->boilWater();
        }
        
        // 冲泡
        if (beverage->ops->brew) {
            beverage->ops->brew();
        }
        
        // 倒入杯中
        if (beverage->ops->pourInCup) {
            beverage->ops->pourInCup();
        }
        
        // 询问是否需要调料
        if (beverage->ops->customerWantsCondiments && 
            beverage->ops->customerWantsCondiments()) {
            // 加入调料
            if (beverage->ops->addCondiments) {
                beverage->ops->addCondiments();
            }
        }
    }
}

// ============ 咖啡具体实现 ============

void coffeeBoilWater(void) {
    printf("将水煮到100度\n");
}

void coffeeBrewCoffeeGrinds(void) {
    printf("用沸水冲泡咖啡\n");
}

void coffeePourInCup(void) {
    printf("将咖啡倒入杯中\n");
}

void coffeeAddCondiments(void) {
    printf("添加糖和牛奶\n");
}

int coffeeCustomerWantsCondiments(void) {
    printf("您想要在咖啡中加入糖和牛奶吗？(1/0): ");
    int response;
    scanf("%d", &response);
    return response;
}

// ============ 茶具体实现 ============

void teaBoilWater(void) {
    printf("将水煮到80度\n");
}

void teaBrewTeaBag(void) {
    printf("浸泡茶包\n");
}

void teaPourInCup(void) {
    printf("将茶倒入杯中\n");
}

void teaAddCondiments(void) {
    printf("添加柠檬\n");
}

int teaCustomerWantsCondiments(void) {
    printf("您想要在茶中加入柠檬吗？(1/0): ");
    int response;
    scanf("%d", &response);
    return response;
}

// 创建咖啡实例
Beverage* createCoffee() {
    Beverage* coffee = (Beverage*)malloc(sizeof(Beverage));
    BeverageOps* coffeeOps = (BeverageOps*)malloc(sizeof(BeverageOps));
    
    coffeeOps->boilWater = coffeeBoilWater;
    coffeeOps->brew = coffeeBrewCoffeeGrinds;
    coffeeOps->pourInCup = coffeePourInCup;
    coffeeOps->addCondiments = coffeeAddCondiments;
    coffeeOps->customerWantsCondiments = coffeeCustomerWantsCondiments;
    
    coffee->name = "Coffee";
    coffee->ops = coffeeOps;
    
    return coffee;
}

// 创建茶实例
Beverage* createTea() {
    Beverage* tea = (Beverage*)malloc(sizeof(Beverage));
    BeverageOps* teaOps = (BeverageOps*)malloc(sizeof(BeverageOps));
    
    teaOps->boilWater = teaBoilWater;
    teaOps->brew = teaBrewTeaBag;
    teaOps->pourInCup = teaPourInCup;
    teaOps->addCondiments = teaAddCondiments;
    teaOps->customerWantsCondiments = teaCustomerWantsCondiments;
    
    tea->name = "Tea";
    tea->ops = teaOps;
    
    return tea;
}

// 释放内存
void freeBeverage(Beverage* beverage) {
    if (beverage) {
        free(beverage->ops);
        free(beverage);
    }
}

// 主函数
int main() {
    // 制作咖啡
    printf("=== 制作咖啡 ===\n");
    Beverage* coffee = createCoffee();
    prepareBeverage(coffee);
    
    printf("\n");
    
    // 制作茶
    printf("=== 制作茶 ===\n");
    Beverage* tea = createTea();
    prepareBeverage(tea);
    
    // 释放内存
    freeBeverage(coffee);
    freeBeverage(tea);
    
    return 0;
}
