/***
 * INutritionRepository:  
 *  -> Brief: Interface for looking up NutritionInfo by food name
***/

#ifndef INUTRITIONREPOSITORY_H
#define INUTRITIONREPOSITORY_H

#include <string>
#include "../entities/NutritionInfo.h"

class INutritionRepository {
public:
    virtual ~INutritionRepository() = default;
    
    // returns true and fills out if found
    virtual bool getNutrition(const std::string &foodName, NutritionInfo &out) = 0;
};

#endif // INUTRITIONREPOSITORY_H
