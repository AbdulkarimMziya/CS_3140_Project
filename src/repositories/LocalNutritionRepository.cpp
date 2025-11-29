/***
 * Assisted by GitHub Copilot, adapted by A.K. Mziya, 2025-11-20 
 *  -> Brief: reuse header-provided string helpers, reading CSV file.
 *  -> Code display: For purpose of readability write code segments in single line
***/

#include "LocalNutritionRepository.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../entities/Exceptions.h"

#include "UserRepository.h" // reuse trim/toLower helpers declared in header

LocalNutritionRepository::LocalNutritionRepository(const std::string &csvPath)
    : path(csvPath) {
    load();
}

void LocalNutritionRepository::load() {
    store.clear();
    std::ifstream in(path);
    if (!in) return; // ok if missing
    std::string line;
    // header
    if (!std::getline(in, line)) return;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string name, calS, protS, carbS, fatS;
        if (!std::getline(ss, name, ',')) continue;
        if (!std::getline(ss, calS, ',')) continue;
        if (!std::getline(ss, protS, ',')) protS = "0";
        if (!std::getline(ss, carbS, ',')) carbS = "0";
        if (!std::getline(ss, fatS, ',')) fatS = "0";
        NutritionInfo info;
        info.name = trim(name);
        try {
            info.calories = std::stod(trim(calS));
            info.protein = std::stod(trim(protS));
            info.carbs = std::stod(trim(carbS));
            info.fat = std::stod(trim(fatS));
        } catch (...) { continue; }
        store[toLower(info.name)] = info;
    }
}

bool LocalNutritionRepository::getNutrition(const std::string &foodName, NutritionInfo &out) {
    auto key = toLower(trim(foodName));
    auto it = store.find(key);
    if (it == store.end()) return false;
    out = it->second;
    return true;
}
