#include "MealEntry.h"
#include <sstream>

MealEntry::MealEntry() : mealId(0), mealType("Unknown") {}

MealEntry::MealEntry(int id, std::string type) : mealId(id), mealType(type) {}

void MealEntry::addFood(const FoodItem &food) {
    foodItems.push_back(food);
}

double MealEntry::calculateTotalCalories() const {
    double total = 0;
    for (auto &f : foodItems)
        total += f.calculateCalories();
    return total;
}

std::string MealEntry::getSummary() const {
    std::ostringstream oss;
    oss << mealType << " | Items: " << foodItems.size()
        << " | Total Calories: " << calculateTotalCalories();
    return oss.str();
}
