/***
 * Assisted by GitHub Copilot, adapted by A.K. Mziya, 2025-11-220 
 *  -> Brief: CSV-backed nutrition repository (reads src/data/nutrition.csv)
***/

#ifndef LOCALNUTRITIONREPOSITORY_H
#define LOCALNUTRITIONREPOSITORY_H


#include "INutritionRepository.h"
#include <string>
#include <unordered_map>

class LocalNutritionRepository : public INutritionRepository {
public:
    explicit LocalNutritionRepository(const std::string &csvPath = "src/data/nutrition.csv");
    bool getNutrition(const std::string &foodName, NutritionInfo &out) override;

private:
private:
    void load();
    std::string path;
    std::unordered_map<std::string, NutritionInfo> store; // lowercase name -> info
};

#endif // LOCALNUTRITIONREPOSITORY_H
