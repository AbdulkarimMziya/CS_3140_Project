// In-memory implementation of the meal repository used for demo and testing.
// This implementation stores meals in memory only (no disk persistence)
// and provides a simple mapping from userId -> list of meal ids plus
// a store of meal objects keyed by meal id.

#include "InMemoryMealRepository.h"
#include "../entities/IdGenerator.h"
#include <algorithm>

// Create a new meal for `userId` and return the assigned meal id.
// Note: this implementation is single-threaded (no locking) and returns
// copies of stored objects. This is sufficient for the small demo.
int InMemoryMealRepository::createMeal(int userId, const MealEntry &meal) {
    // assign a unique id for the stored meal
    int id = IdGenerator::generateId();
    // construct a stored copy with the assigned id (keep the original date/type)
    MealEntry stored(id, meal.getMealType(), meal.getDate());
    // copy food items into the stored entry
    for (const auto &f : meal.getFoodItems()) stored.addFood(f);
    // put the stored meal on the shelf and index it by user
    store.emplace(id, std::move(stored));
    index[userId].push_back(id);
    return id;
}

// Return a vector of meals for the given user. Meals are returned as copies
// of the internal stored objects so callers cannot mutate internal state.
std::vector<MealEntry> InMemoryMealRepository::listMealsForUser(int userId) {
    std::vector<MealEntry> out;
    auto it = index.find(userId);
    if (it == index.end()) return out;
    out.reserve(it->second.size());
    for (int id : it->second) {
        auto sit = store.find(id);
        if (sit != store.end()) out.push_back(sit->second);
    }
    return out;
}
