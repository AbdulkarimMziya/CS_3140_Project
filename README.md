# CS_3140_Project - Calorie Tracker App

## Overview
The Calorie Tracker App is a C++ object-oriented project designed to help users monitor their daily calorie intake and achieve fitness goals. It models a real-world calorie tracking system using key OOP concepts such as encapsulation, inheritance, and polymorphism.</br>
The system includes classes for users (regular users and trainers), goals, meals, and food items. Regular users can log meals and track progress toward their calorie goals, while trainers can create and assign diet plans.
</br>
The project is organized into modular components under an `entities/` folder and demonstrates practical class relationships through composition and association.

## Project Structure
```text
src/
 ├── entities/
 │    ├── User.h / User.cpp
 │    ├── RegularUser.h / RegularUser.cpp
 │    ├── Goal.h / Goal.cpp
 │    ├── MealEntry.h / MealEntry.cpp
 │    ├── FoodItem.h / FoodItem.cpp
 │    ├── Notification.h
 ├── main.cpp
```

## Installation
1. Clone the repository:

```bash
git clone 'https://github.com/<YOUR-REPO>/CS_3140_Project.git' &&
cd CS_3140_Project
```

2. Open the project in Visual Studio Code and [set up the C/C++ extension](https://code.visualstudio.com/docs/cpp/config-clang-mac) if needed.

---

## UML-to-Code Mapping

Below are two tables following the example you provided: a detailed class table and a relationship table.

### Class mapping (detailed)

| UML Class | Responsibility | Header File (.h) | Source File (.cpp) | Member functions (representative) | Notes |
|---|---|---|---|---|---|
| User | Base class representing any user in the system | `src/entities/User.h` | `src/entities/User.cpp` | getId(), getName(), setName(), virtual getRole() | Common base for concrete user types. May be abstract.
| RegularUser | Stores user-specific data and manages meal logs/goals | `src/entities/RegularUser.h` | `src/entities/RegularUser.cpp` | logMeal(const MealEntry&), getMeals(), setGoal(const Goal&), getGoal() | Inherits from `User`; aggregates `MealEntry` instances and references `Goal`.
| Goal | Represents a calorie/fitness goal and progress logic | `src/entities/Goal.h` | `src/entities/Goal.cpp` | setTargetCalories(int), getTargetCalories(), isMet(), progress() | Tracks target calories and time window; often owned by a user.
| MealEntry | A logged meal for a user; groups food items and timestamp | `src/entities/MealEntry.h` | `src/entities/MealEntry.cpp` | addFoodItem(const FoodItem&), getTotalCalories(), getTimestamp() | Aggregates one or more `FoodItem` objects; linked to a `User`.
| FoodItem | Nutritional information for a food/ingredient | `src/entities/FoodItem.h` | `src/entities/FoodItem.cpp` | getCalories(), getServingSize(), getName() | Lightweight data object used by `MealEntry` to compute calories.
| Notification | Alert or message object for the system | `src/entities/Notification.h` | (header-only) | create(message), getMessage(), sendTo(const User&) | Small header-only type; used for alerts/messages.
| Application entrypoint | Program bootstrap and example usage | `src/main.cpp` | `src/main.cpp` | main(int, char**) | Shows how components are wired together and can include sample flows.



### Relationship mapping (UML -> Code)

| Relationship | UML element (example) | Code representation | Notes |
|---|---|---|---|
| Inheritance | `RegularUser` → `User` | `class RegularUser : public User { ... };` | "is-a" relationship — concrete user extends base `User`.
| Association / Aggregation | `MealEntry` — `FoodItem` | `MealEntry` stores a collection (e.g., `std::vector<FoodItem>` or pointers/references) | `MealEntry` references `FoodItem` instances to compute totals.
| Aggregation | `User` — `MealEntry` | `User` maintains a list/vector of `MealEntry` objects | `User` aggregates meal logs; entries may be stored externally in some designs.
| Composition | `User` owns `Goal` | `User`/`RegularUser` contains a `Goal` member (by-value or `unique_ptr`) | Strong ownership — goal lifecycle tied to the user.
| Dependency | `main` or service functions → `Goal` / `MealEntry` | Example: `user.setGoal(Goal(...));` inside a function | Temporary usage of other objects; no ownership implied.

