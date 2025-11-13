#include "Goal.h"
#include <sstream>

Goal::Goal(int target, std::string per)
    : targetCalories(target), period(per) {}

void Goal::updateGoal(int newTarget) { targetCalories = newTarget; }

bool Goal::isExceeded(double currentCalories) const {
    return currentCalories > targetCalories;
}

int Goal::getTarget() const { return targetCalories; }
