#include <iostream>
#include "entities/FoodItem.h"
#include "entities/MealEntry.h"
#include "entities/Goal.h"
#include "entities/RegularUser.h"

#include <iomanip>

int main()
{
    // Tests for FoodItem and MealEntry
    FoodItem apple(1, "Apple", 52.0, 1.0); // 52 kcal
    FoodItem banana(2, "Banana", 89.0, 0.5); // 44.5 kcal

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FoodItem tests:\n";
    std::cout << " - " << apple.getName() << ": " << apple.calculateCalories() << " kcal\n";
    std::cout << " - " << banana.getName() << ": " << banana.calculateCalories() << " kcal\n";

    MealEntry meal(100, "Lunch");
    meal.addFood(apple);
    meal.addFood(banana);

    double total = meal.calculateTotalCalories();
    std::cout << "\nMealEntry tests:\n";
    std::cout << " - Summary: " << meal.getSummary() << "\n";
    std::cout << " - Calculated total calories: " << total << " kcal\n";

    // Simple check: expected total = 52.0 + 44.5 = 96.5
    std::cout << "\nExpected total: 96.50 kcal\n";

    // Use Goal to demonstrate integration
    Goal dailyGoal(2000, "daily");
    std::cout << "\nGoal tests:\n";
    std::cout << " - Target calories (" << "daily" << "): " << dailyGoal.getTarget() << " kcal\n";

    if (dailyGoal.isExceeded(total)) {
        std::cout << " - Meal exceeds the goal!\n";
    } else {
        std::cout << " - Meal does not exceed the goal.\n";
    }

    // RegularUser integration test
    std::cout << "\nRegularUser tests:\n";
    RegularUser alice(1, "Alice", 30, "alice@example.com");
    Goal lowGoal(50, "daily");
    alice.setGoal(lowGoal);
    alice.logMeal(meal);
    alice.checkProgress();
    alice.viewReport();

    return 0;
}
