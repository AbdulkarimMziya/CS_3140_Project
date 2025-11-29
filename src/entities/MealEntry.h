#ifndef MEALENTRY_H
#define MEALENTRY_H


#include <vector>
#include <string>
#include <chrono>
#include "FoodItem.h"


class MealEntry {
private:
    int mealId;
    std::string mealType;
    std::vector<FoodItem> foodItems;
    std::chrono::system_clock::time_point date;

public:
    // Default constructor: creates an 'Unknown' meal with the current timestamp
    MealEntry();

    // Construct a MealEntry with an explicit id and type (used when storing)
    MealEntry(int id, const std::string &type, std::chrono::system_clock::time_point d = std::chrono::system_clock::now());

    // Add a food item to the meal (stores a copy of the FoodItem)
    void addFood(const FoodItem &food);

    // Calculate the total calories for all food items in the meal
    double calculateTotalCalories() const;

    // Produce a short textual summary used by the UI
    std::string getSummary() const;

    // Accessors
    int getMealId() const;
    std::string getMealType() const;
    std::vector<FoodItem> getFoodItems() const;
    std::chrono::system_clock::time_point getDate() const;

    // Mutator used by the UI to set meal type (Breakfast/Lunch/etc.)
    void setMealType(const std::string &type);
};

#endif
