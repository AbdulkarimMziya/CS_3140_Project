#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>

class FoodItem {
private:
    int foodId;
    std::string name;
    double caloriesPerUnit;
    double portionSize;

public:
    FoodItem(int id, std::string n, double calUnit, double portion);
    double calculateCalories() const;
    std::string getName() const;
};

#endif
