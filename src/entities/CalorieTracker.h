
#ifndef CS_3140_PROJECT_CALORIETRACKER_H
#define CS_3140_PROJECT_CALORIETRACKER_H

#include <unordered_map>
#include <string>
#include "RegularUser.h"
#include "DailyLog.h"
#include "MealEntry.h"
#include <chrono>

/***
 * Assisted by GitHub Copilot, adapted by A.K. Mziya, 2025-11-25 
 *  -> Brief: date helpers (formatDateIso, todayIso) reused by tracker and main
 ***/

static inline std::string formatDateIso(const std::chrono::system_clock::time_point &tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::tm tm;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
    return std::string(buf);
}

static inline std::string todayIso() {
    return formatDateIso(std::chrono::system_clock::now());
}

class CalorieTracker {
private:
    RegularUser &user;
    std::unordered_map<std::string, DailyLog> logs;

    std::string formatDate(std::chrono::system_clock::time_point tp) const;

public:
    // Construct tracker bound to a specific RegularUser
    explicit CalorieTracker(RegularUser &u);

    // Add a meal to the tracker and record it under the appropriate date
    void logMeal(const MealEntry &meal);

    // Compute total calories for the given date (ISO YYYY-MM-DD)
    double calculateDailyCalories(const std::string &date) const;

    // Obtain a pointer to the DailyLog for the date, or nullptr if none
    const DailyLog* getDailyLog(const std::string &date) const;

    // Check user's goal progress for the given date and issue notifications as needed
    void checkProgress(const std::string &date);

    // Print a daily report to stdout for the given date
    void viewDailyReport(const std::string &date) const;
};

#endif //CS_3140_PROJECT_CALORIETRACKER_H