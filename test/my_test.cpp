
// Assisted by GitHub Copilot, adapted by adapted by A.K. Mziya, 2025-11-28
// Reason: added focused unit tests for `MealEntry` and notification behavior

#include "gtest/gtest.h"
#include "entities/FoodItem.h"
#include "entities/MealEntry.h"

#include "entities/RegularUser.h"
#include "entities/CalorieTracker.h"
#include "entities/Goal.h"


TEST(MealEntryTest, CalculatesTotalAndSummary) {
	// Create two food items: Apple (52 cal per unit, 1 unit)
	// and Banana (89 cal per unit, 0.5 unit -> 44.5)
	FoodItem apple(1, "Apple", 52.0, 1.0);
	FoodItem banana(2, "Banana", 89.0, 0.5);

	MealEntry meal;
	meal.setMealType("Breakfast");
	meal.addFood(apple);
	meal.addFood(banana);

	double total = meal.calculateTotalCalories();
	EXPECT_DOUBLE_EQ(total, 52.0 + 44.5);

	std::string summary = meal.getSummary();
	EXPECT_NE(summary.find("Breakfast"), std::string::npos);
	EXPECT_NE(summary.find("Apple"), std::string::npos);
	EXPECT_NE(summary.find("Banana"), std::string::npos);
}

TEST(NotificationTest, AddsNotificationWhenCaloriesExceeded) {
	RegularUser user("TestUser", 30, "test@example.com");
	Goal lowGoal(50, GoalPeriod::Daily);
	user.setGoal(lowGoal);

	CalorieTracker tracker(user);

	FoodItem item(1, "HighCal", 100.0, 1.0);
	MealEntry meal;
	meal.addFood(item);

	tracker.logMeal(meal);

	auto &notes = user.getNotifications();
	EXPECT_EQ(notes.size(), 1u);
}

