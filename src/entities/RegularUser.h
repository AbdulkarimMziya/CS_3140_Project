#ifndef REGULARUSER_H
#define REGULARUSER_H

#include "User.h"
#include "MealEntry.h"
#include <vector>

class RegularUser : public User {
private:
    std::vector<MealEntry> meals;
    double currentCalories;

public:
    RegularUser(int id, const std::string &n, int a, const std::string &e);
    void logMeal(const MealEntry &meal);
    void checkProgress();
    void viewReport() const override;
};

#endif
