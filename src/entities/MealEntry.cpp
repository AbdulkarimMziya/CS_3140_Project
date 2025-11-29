#include "MealEntry.h"
#include <sstream>

// Default constructor: start with an 'Unknown' meal type and current time
MealEntry::MealEntry() : mealId(0), mealType("Unknown"), date(std::chrono::system_clock::now()) {}

// Constructor with a specific id and type (used by repositories)
MealEntry::MealEntry(int id, const std::string &type, std::chrono::system_clock::time_point d)
    : mealId(id), mealType(type), date(d) {}

void MealEntry::addFood(const FoodItem &food) {
    foodItems.push_back(food);
}

double MealEntry::calculateTotalCalories() const {
    double total = 0;
    for (const auto &f : foodItems) total += f.calculateCalories();
    return total;
}

std::string MealEntry::getSummary() const {
    // Readable summary used in the CLI
    std::ostringstream oss;
    oss << mealType << " | Items: " << foodItems.size();
    if (!foodItems.empty()) {
        oss << " [";
        for (size_t i = 0; i < foodItems.size(); ++i) {
            oss << foodItems[i].getName();
            if (i + 1 < foodItems.size()) oss << ", ";
        }
        oss << "]";
    }
    oss << " | Total Calories: " << calculateTotalCalories();
    return oss.str();
}

int MealEntry::getMealId() const { return mealId; }
std::string MealEntry::getMealType() const { return mealType; }
std::vector<FoodItem> MealEntry::getFoodItems() const { return foodItems; }
std::chrono::system_clock::time_point MealEntry::getDate() const { return date; }

void MealEntry::setMealType(const std::string &type) { mealType = type; }
