#include "FoodItem.h"

FoodItem::FoodItem(int id, std::string n, double calUnit, double portion)
    : foodId(id), name(n), caloriesPerUnit(calUnit), portionSize(portion) {}

double FoodItem::calculateCalories() const {
    return caloriesPerUnit * portionSize;
}

std::string FoodItem::getName() const {
    return name;
}
