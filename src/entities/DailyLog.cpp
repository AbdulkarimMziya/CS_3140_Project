#include "DailyLog.h"

void DailyLog::addMeal(const MealEntry &meal) {
    meals.push_back(meal);
}

double DailyLog::getTotalCalories() const {
    double total = 0.0;
    for (const auto &meal : meals) total += meal.calculateTotalCalories();
    return total;
}

const std::vector<MealEntry>& DailyLog::getMeals() const {
    return meals;
}
