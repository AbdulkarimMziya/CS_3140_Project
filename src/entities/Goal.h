/***
 * Goal: 
 *  -> Brief: Represents a user's calorie goal and period
***/
#ifndef GOAL_H
#define GOAL_H


enum class GoalPeriod { Daily, Weekly, Monthly };

class Goal {
private:
    int targetCalories;
    GoalPeriod period;

public:
    // Construct a Goal with a target calorie value and a period (default daily)
    Goal(int target = 2000, GoalPeriod p = GoalPeriod::Daily);

    // Update the target calorie value
    void updateGoal(int newTarget);

    // Return true if the provided currentCalories exceeds the goal target
    bool isExceeded(double currentCalories) const;

    // Accessors
    int getTarget() const { return targetCalories; }
    GoalPeriod getPeriod() const { return period; }
};

#endif
