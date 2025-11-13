#include "RegularUser.h"
#include "Notification.h"
#include <iostream>

RegularUser::RegularUser(int id, const std::string &n, int a, const std::string &e)
    : User(id, n, a, e), currentCalories(0) {}

void RegularUser::logMeal(const MealEntry &meal) {
    meals.push_back(meal);
    currentCalories += meal.calculateTotalCalories();
    std::cout << "Logged: " << meal.getSummary() << std::endl;
}

void RegularUser::checkProgress() {
    if (goal.isExceeded(currentCalories)) {
        Notification note("Calorie goal exceeded!", "Alert");
        addNotification(note);
        note.send();
    }
}

void RegularUser::viewReport() const {
    std::cout << "\n--- Daily Report for " << name << " ---\n";
    for (const auto &m : meals)
        std::cout << m.getSummary() << "\n";
    std::cout << "Total Calories: " << currentCalories
              << "/" << goal.getTarget() << std::endl;
}
