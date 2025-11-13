#ifndef GOAL_H
#define GOAL_H
#include <string>

class Goal {
private:
    int targetCalories;
    std::string period;

public:
    Goal(int target = 2000, std::string per = "daily");
    void updateGoal(int newTarget);
    bool isExceeded(double currentCalories) const;
    int getTarget() const;
};

#endif
