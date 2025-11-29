/***
 * InMemoryMealRepository: 
 *  -> Brief: In-memory implementation of IMealRepository for tests/demo
***/

#ifndef INMEMORYMEALREPOSITORY_H
#define INMEMORYMEALREPOSITORY_H

#include "IMealRepository.h"
#include <unordered_map>

class InMemoryMealRepository : public IMealRepository {
public:
    InMemoryMealRepository() = default;
    // Persist the meal and return assigned id
    int createMeal(int userId, const MealEntry &meal) override;
    // List meals for a given user
    std::vector<MealEntry> listMealsForUser(int userId) override;

private:
    std::unordered_map<int, MealEntry> store; // mealId -> meal
    std::unordered_map<int, std::vector<int>> index; // userId -> mealIds
};

#endif // INMEMORYMEALREPOSITORY_H
