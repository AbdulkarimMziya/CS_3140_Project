/***
 * Assisted by GitHub Copilot, adapted by A.K. Mziya, 2025-11-17 
 *  -> Brief: formatDate helper (thread-safe), comments, toLower lamba for string manipulation
 *  -> Code display: For purpose of readability write code segments in single line
***/

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <cctype>

#include "services/UserService.h"
#include "services/MealService.h"
#include "repositories/UserRepository.h"
#include "repositories/LocalNutritionRepository.h"
#include "repositories/InMemoryMealRepository.h"
#include "entities/FoodItem.h"
#include "entities/MealEntry.h"
#include "entities/CalorieTracker.h"

/***
 * Assisted by GitHub Copilot, adapted by A.K. Mziya, 2025-11-25 
 *  -> Brief: reuse shared date helpers (formatDateIso, todayIso)
 ***/

// Track which user/date combos have already been notified so we don't repeat
static std::unordered_set<std::string> g_notified;


int main() {
    auto userRepo = std::make_shared<UserRepository>("users.txt");
    auto nutritionRepo = std::make_shared<LocalNutritionRepository>("../src/data/nutrition.csv");
    auto mealRepo = std::make_shared<InMemoryMealRepository>();

    UserService userService(userRepo);
    MealService mealService(mealRepo, nutritionRepo);

    int currentUserId = -1;
    bool running = true;

    while (running) {
        std::cout << "\n--- Calorie Tracker ---\n";
        if (currentUserId >= 0) {
            auto u = userService.getById(currentUserId);
            if (u) std::cout << "Logged in as: " << u->getName() << " (id=" << u->getId() << ")\n";
            else currentUserId = -1;
        } else {
            std::cout << "[Not logged in]\n";
        }

        std::cout << "1) Register user\n";
        std::cout << "2) List users\n";
        std::cout << "3) Login (by id)\n";
        std::cout << "4) Lookup food nutrition\n";
        std::cout << "5) Log a meal\n";
        std::cout << "6) Show daily report (today)\n";
        std::cout << "0) Exit\n";
        std::cout << "Choose: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n');

        switch (choice) {
            case 1: {
                std::string name, email;
                int age = 18;
                int goal = 2000;
                std::cout << "Name: "; std::getline(std::cin, name);
                std::cout << "Age: "; std::cin >> age; std::cin.ignore(10000, '\n');
                std::cout << "Email: "; std::getline(std::cin, email);
                std::cout << "Daily calorie goal (default 2000): ";
                std::string gline; std::getline(std::cin, gline);
                if (!gline.empty()) {
                    try { goal = std::stoi(gline); } catch(...) { goal = 2000; }
                }
                int id = userService.registerUser(name, age, email, goal);
                if (id > 0) std::cout << "Registered user id=" << id << " (goal=" << goal << ")\n";
                else std::cout << "[Failed to register user]\n";
                break;
            }
            case 2: {
                auto list = userRepo->listAll();
                std::cout << "Users:\n";
                for (const auto &u : list) {
                    std::cout << "  id=" << u.getId() << " name=" << u.getName() << " age=" << u.getAge() << " email=" << u.getEmail() << "\n";
                }
                break;
            }
            case 3: {
                std::cout << "Enter user id: ";
                int uid; std::cin >> uid; std::cin.ignore(10000, '\n');
                auto u = userService.getById(uid);
                if (u) {
                    currentUserId = uid;
                    std::cout << "Logged in as " << u->getName() << "\n";
                } else {
                    std::cout << "User not found\n";
                }
                break;
            }
            case 4: {
                std::string fname;
                std::cout << "Food name: "; std::getline(std::cin, fname);
                NutritionInfo info;
                if (nutritionRepo->getNutrition(fname, info)) {
                    std::cout << info.name << " — " << info.calories << " kcal (P:" << info.protein
                              << " C:" << info.carbs << " F:" << info.fat << ")\n";
                } else {
                    std::cout << "[Not found]\n";
                }
                break;
            }
            case 5: {
                if (currentUserId < 0) { std::cout << "[Login first]\n"; break; }

                // Ask for meal type
                std::string mealType;
                std::cout << "Meal type (Breakfast/Lunch/Dinner/Snack) [default Breakfast]: ";
                std::getline(std::cin, mealType);
                if (mealType.empty()) mealType = "Breakfast";

                // reuse shared `toLower` helper from UserRepository.h
                const std::vector<std::string> allowed = {"breakfast", "lunch", "dinner", "snack"};
                std::string mtNorm = toLower(mealType);
                bool mealTypeOk = (std::find(allowed.begin(), allowed.end(), mtNorm) != allowed.end());
                if (!mealTypeOk) {
                    std::cout << "[Invalid meal type '" << mealType << "'. Returning to main menu.]\n";
                    break;
                }

                int n = 0;
                std::cout << "Number of items: ";
                if (!(std::cin >> n)) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Invalid number. Returning to main menu.\n"; break; }
                if (n <= 0) { std::cout << "[Must log at least one item. Returning to main menu.]\n"; std::cin.ignore(10000, '\n'); break; }
                std::cin.ignore(10000, '\n');

                MealEntry meal;
                meal.setMealType(mealType);

                bool valid = true;
                for (int i = 0; i < n; ++i) {
                    std::string fname;
                    double portion = 1.0;
                    std::cout << "Item " << (i+1) << " name: "; std::getline(std::cin, fname);
                    if (fname.empty()) { std::cout << "[Item name cannot be empty. Aborting meal entry.]\n"; valid = false; break; }
                    std::cout << "Portion size (default 1.0): ";
                    std::string pstr; std::getline(std::cin, pstr);
                    if (!pstr.empty()) {
                        try { portion = std::stod(pstr); } catch(...) { std::cout << "[Invalid portion input. Aborting meal entry.]\n"; valid = false; break; }
                        if (portion <= 0.0) { std::cout << "[Portion must be positive. Aborting meal entry.]\n"; valid = false; break; }
                    }
                    // calories left 0.0 so MealService will enrich from nutrition repo
                    meal.addFood(FoodItem(0, fname, 0.0, portion));
                }

                if (!valid) {
                    std::cout << "[Meal not logged due to invalid input. Returning to main menu.]\n";
                    break;
                }

                int mid = mealService.logMeal(currentUserId, meal);
                if (mid > 0) {
                    std::cout << "Logged meal id=" << mid << "\n";

                    // After logging, check today's total against user's goal and notify once
                    auto meals = mealService.getMealsForUser(currentUserId);
                    std::string today = todayIso();
                    double total = 0.0;
                    for (const auto &m : meals) {
                        if (formatDateIso(m.getDate()) != today) continue;
                        total += m.calculateTotalCalories();
                    }
                    auto u = userService.getById(currentUserId);
                    if (u) {
                        int goal = u->getGoal().getTarget();
                        std::string key = std::to_string(currentUserId) + "|" + today;
                        if (goal > 0 && total >= goal && g_notified.find(key) == g_notified.end()) {
                            // create a Notification object and attach/send via the user
                            std::string title = "[Daily Goal Reached]";
                            std::ostringstream msg;
                            msg << "You reached your daily goal (" << static_cast<int>(total) << "/" << goal << " kcal).";
                            Notification note(msg.str(), title);
                            u->addNotification(note); // this prints/sends the notification
                            g_notified.insert(key);
                        }
                    }
                } else std::cout << "[Failed to log meal]\n";
                break;
            }
            case 6: {
                if (currentUserId < 0) { std::cout << "Login first\n"; break; }
                auto meals = mealService.getMealsForUser(currentUserId);
                std::string today = todayIso();
                std::cout << "\n--- Daily Report (" << today << ") ---\n";
                double total = 0.0;
                for (const auto &m : meals) {
                    if (formatDateIso(m.getDate()) != today) continue;
                    std::cout << m.getSummary() << "\n";
                    total += m.calculateTotalCalories();
                }
                std::cout << "Total Calories today: " << total << "\n";
                break;
            }
            case 0:
                running = false; break;
            default:
                std::cout << "[Unknown option]\n"; break;
        }
    }

    std::cout << "Goodbye\n";
    return 0;
}
