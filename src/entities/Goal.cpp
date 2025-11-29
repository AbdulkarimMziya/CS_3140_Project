#include "Goal.h"

Goal::Goal(int target, GoalPeriod p) : targetCalories(target), period(p) {}

void Goal::updateGoal(int newTarget) {
    targetCalories = newTarget;
}

bool Goal::isExceeded(double currentCalories) const {
    return currentCalories > targetCalories;
}
