# Calorie Tracker 

This small C++ project demonstrates a layered design (Entities → Repositories → Services → UI) suitable for a third-year university exercise in OOP and basic software architecture.

Goals:
- Show how domain entities (users, meals, food items, goals) are separated from persistence via repository interfaces.
- Provide services that encapsulate business logic and orchestrate repositories.
- Keep the implementation simple (CSV file and in-memory storage) so students can focus on design.

## Architecture

ASCII overview:
```md

            ┌───────────────────────┐
            │     UI / `main.cpp`   │
            └──────────┬────────────┘
                       │ calls
                       ▼
            ┌───────────────────────┐
            │ Services Layer        │
            │ `UserService`         │
            │ `MealService`         │
            └──────┬───────┬────────┘
                   │       │
                   ▼       ▼
     ┌─────────────────-┐  ┌──────────────────────┐
     │ `RegularUser`    │  │     `MealEntry`      │
     │ `FoodItem` (CSV) │  │     `Goal`           │
     └──────┬───────────┘  └─────────-┬───────────┘
            │                         │
            ▼                         ▼
   ┌────────────────┐       ┌────────────────────────┐
   │ UserRepository  │       │ LocalNutritionRepo     │
   │ (users.txt)     │       │ (src/data/nutrition.csv)
   └────────────────┘       └────────────────────────┘
```

The UI (a small `main.cpp` demo) calls the Services. Services call repository interfaces — concrete repository implementations (file-backed or in-memory) are provided and injected by the UI in this demo.

## Key Components

- `src/entities/` — domain objects:
  - `RegularUser`, `User`, `MealEntry`, `FoodItem`, `Goal`, `DailyLog`, `Notification`, `NutritionInfo`.

- `src/repositories/` — repository interfaces + implementations:
  - `IUserRepository` + `UserRepository` (file-backed `users.txt` CSV)
  - `INutritionRepository` + `LocalNutritionRepository` (reads `src/data/nutrition.csv`)
  - `IMealRepository` + `InMemoryMealRepository` (keeps meals in memory for the demo)

- `src/services/` — business logic / orchestration:
  - `UserService` — register users, fetch by id/email.
  - `MealService` — log meals, retrieve meals for a user.

- `src/main.cpp` — small console demo that wires repositories → services → runs a simple scenario:
  - Register a user
  - Lookup nutrition for "Apple"
  - Create a `MealEntry` and log it
  - Use `CalorieTracker` to print a daily report

## Build & Run

Requirements:
- macOS (or Linux) with CMake and a C++20 capable compiler (AppleClang/clang/gcc)

Build (from repository root):

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug --config Debug
```

Run the demo executable:

```bash
./cmake-build-debug/CS_3140_Project
```

Expected demo output (example):

```
Found nutrition for Apple, calories=52
Logged meal id=2

--- Daily Report for Bob (2025-11-27) ---
Unknown | Items: 1 | Total Calories: 52
Total Calories: 52/2000
```

Notes:
- `users.txt` (file-backed repository) will be created in the `CS_3140_Project/cmake-build-debug` when you register users via the demo.
- Nutrition data is read from `src/data/nutrition.csv`.

## Design Notes (for students)

- Separation of concerns: Entities only represent data and simple behavior. Repositories handle persistence details. Services expose higher-level operations and hide persistence details.
- Dependency inversion: Services depend on repository interfaces (e.g., `IUserRepository`) rather than concrete classes. The demo creates the concrete repositories and injects them into the services.
- Testability: Because services depend on interfaces, you can easily swap in test/dummy repositories (e.g., `InMemoryMealRepository`) when writing unit tests.

## Where to look in the code
- Entities: `src/entities/*.h` and `src/entities/*.cpp`
- Repositories: `src/repositories/*`
- Services: `src/services/*`
- Demo: `src/main.cpp`


## Contact / Credits
Project scaffold and entities provided by the assignment. This README and the repository/service layers were implemented as a learning example.

---

