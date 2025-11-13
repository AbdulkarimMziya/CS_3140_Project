#ifndef MEALENTRY_H
#define MEALENTRY_H

#include <vector>
#include <string>
#include "FoodItem.h"

class MealEntry {
private:
    int mealId;
    std::string mealType;
    std::vector<FoodItem> foodItems;

public:
    MealEntry();
    MealEntry(int id, std::string type);
    void addFood(const FoodItem &food);
    double calculateTotalCalories() const;
    std::string getSummary() const;
};

#endif
