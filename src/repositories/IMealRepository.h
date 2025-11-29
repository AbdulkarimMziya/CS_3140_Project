/***
 * IMealRepository:
 *  -> Brief: Interface for storing and retrieving MealEntry records
***/

#ifndef IMEALREPOSITORY_H
#define IMEALREPOSITORY_H


#include <vector>
#include <memory>
#include "../entities/MealEntry.h"

class IMealRepository {
public:
    virtual ~IMealRepository() = default;
    // Persist a meal and return an assigned meal id
    virtual int createMeal(int userId, const MealEntry &meal) = 0;
    // List meals for a user
    virtual std::vector<MealEntry> listMealsForUser(int userId) = 0;
};

#endif // IMEALREPOSITORY_H
