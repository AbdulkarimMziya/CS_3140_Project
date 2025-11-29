/***
 *  MealService:
 *  -> Brief: Business operations for logging meals and with nutrition data
***/
#ifndef MEALSERVICE_H
#define MEALSERVICE_H

#include <memory>
#include "../repositories/IMealRepository.h"
#include "../repositories/INutritionRepository.h"

// forward declarations
class INutritionRepository;

class MealService {
public:
    explicit MealService(std::shared_ptr<IMealRepository> repo,
                         std::shared_ptr<INutritionRepository> nutritionRepo = nullptr);

    // persist a meal for a user and return meal id
    int logMeal(int userId, const MealEntry &meal);

    // retrieve meals for user (delegates to repository)
    std::vector<MealEntry> getMealsForUser(int userId);

private:
    std::shared_ptr<IMealRepository> repository;
    std::shared_ptr<INutritionRepository> nutritionRepository;
};

#endif // MEALSERVICE_H
