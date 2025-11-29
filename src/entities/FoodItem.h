/***
 * FoodItem:
 *  -> Brief: Represents a single food item including its name, calories per unit,
 *            and a portion size. Used by MealEntry to compute per-item calories.
***/

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
    // Create a food item. `calUnit` is calories per unit (e.g. per 100g or per item)
    FoodItem(int id, const std::string &n, double calUnit, double portion);

    // Compute calories = caloriesPerUnit * portionSize
    double calculateCalories() const;

    // Accessors
    std::string getName() const;
    double getCaloriesPerUnit() const;
    double getPortionSize() const;

    // Mutator used by services/repositories when enriching from nutrition data
    void setCaloriesPerUnit(double c);
};

#endif //CS_3140_PROJECT_FOODITEM_H