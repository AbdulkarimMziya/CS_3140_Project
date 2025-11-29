/***
 * Calorie:
 *  -> Brief: delegate to shared date helper (formatDateIso)
***/

#include "CalorieTracker.h"
#include "Notification.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>

CalorieTracker::CalorieTracker(RegularUser &u) : user(u) {}


std::string CalorieTracker::formatDate(std::chrono::system_clock::time_point tp) const {
    return formatDateIso(tp);
}

void CalorieTracker::logMeal(const MealEntry &meal) {
    std::string dateKey = formatDate(meal.getDate());
    logs[dateKey].addMeal(meal);
    checkProgress(dateKey);
}

double CalorieTracker::calculateDailyCalories(const std::string &date) const {
    auto it = logs.find(date);
    if (it != logs.end()) return it->second.getTotalCalories();
    return 0.0;
}

const DailyLog* CalorieTracker::getDailyLog(const std::string &date) const {
    auto it = logs.find(date);
    if (it != logs.end()) return &it->second;
    return nullptr;
}

void CalorieTracker::checkProgress(const std::string &date) {
    double total = calculateDailyCalories(date);
    if (user.getGoal().isExceeded(total)) {
        Notification note("Calorie goal exceeded!", "Alert");
        user.addNotification(note);
    }
}

void CalorieTracker::viewDailyReport(const std::string &date) const {
    const DailyLog* log = getDailyLog(date);
    if (!log) {
        std::cout << "No meals logged for " << date << "\n";
        return;
    }

    std::cout << "\n--- Daily Report for " << user.getName() << " (" << date << ") ---\n";
    for (const auto &meal : log->getMeals())
        std::cout << meal.getSummary() << "\n";

    std::cout << "Total Calories: " << log->getTotalCalories()
              << "/" << user.getGoal().getTarget() << "\n";
}
