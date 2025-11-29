#include "FoodItem.h"

FoodItem::FoodItem(int id, const std::string &n, double calUnit, double portion)
    : foodId(id), name(n), caloriesPerUnit(calUnit), portionSize(portion) {}

double FoodItem::calculateCalories() const {
    // Multiply per-unit calories by chosen portion to get item calories
    return caloriesPerUnit * portionSize;
}

std::string FoodItem::getName() const {
    return name;
}

// Return the stored calories-per-unit and portion size
double FoodItem::getCaloriesPerUnit() const { return caloriesPerUnit; }

double FoodItem::getPortionSize() const { return portionSize; }

// Set per-unit calories (used when enriching from nutrition repository)
void FoodItem::setCaloriesPerUnit(double c) { caloriesPerUnit = c; }
