/***
 * DailyLog:
 *  -> Brief: Daily aggregation of meals and calorie totals
***/

#ifndef CS_3140_PROJECT_DAILYLOG_H
#define CS_3140_PROJECT_DAILYLOG_H


#include <vector>
#include "MealEntry.h"

class DailyLog {
private:
    std::vector<MealEntry> meals;

public:
    // Append a meal to this day's log (stores a copy)
    void addMeal(const MealEntry &meal);

    // Compute the total calories across all meals in this log
    double getTotalCalories() const;

    // Return a const reference to the underlying meals vector
    const std::vector<MealEntry>& getMeals() const;
};

#endif //CS_3140_PROJECT_DAILYLOG_H
