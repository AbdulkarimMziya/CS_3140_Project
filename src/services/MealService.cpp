
#include "MealService.h"
#include "../repositories/InMemoryMealRepository.h"
#include "../entities/NutritionInfo.h"

MealService::MealService(std::shared_ptr<IMealRepository> repo,
                         std::shared_ptr<INutritionRepository> nutritionRepo)
    : repository(std::move(repo)), nutritionRepository(std::move(nutritionRepo)) {}

int MealService::logMeal(int userId, const MealEntry &meal) {
    if (!repository) return -1;

    // Create an enriched copy of the meal: fill missing calories from the nutrition repo
    MealEntry enrichedMeal(meal.getMealId(), meal.getMealType(), meal.getDate());
    auto items = meal.getFoodItems();
    for (auto item : items) {
        if ((item.getCaloriesPerUnit() <= 0.0) && nutritionRepository) {
            NutritionInfo info;
            if (nutritionRepository->getNutrition(item.getName(), info)) {
                item.setCaloriesPerUnit(info.calories);
            }
        }
        enrichedMeal.addFood(item);
    }

    return repository->createMeal(userId, enrichedMeal);
}

std::vector<MealEntry> MealService::getMealsForUser(int userId) {
    if (!repository) return {};
    return repository->listMealsForUser(userId);
}

