/***
 * NutritionInfo:
 *  -> Brief: A struct holding nutritional values for a food item
***/
#ifndef NUTRITIONINFO_H
#define NUTRITIONINFO_H


#include <string>

struct NutritionInfo {
    std::string name;
    double calories = 0.0; // kcal
    double protein = 0.0;  // grams
    double carbs = 0.0;    // grams
    double fat = 0.0;      // grams
    std::string raw;       // optional raw metadata
};

#endif //CS_3140_PROJECT_NUTRITIONINFO_H