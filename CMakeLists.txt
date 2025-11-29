#\***
#
#***\
cmake_minimum_required(VERSION 4.0)
project(CS_3140_Project)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Create a library with the project sources so main and tests can link to it
add_library(app_lib
  # entities
  src/entities/FoodItem.cpp
  src/entities/Goal.cpp
  src/entities/MealEntry.cpp
  src/entities/RegularUser.cpp
  src/entities/User.cpp
  src/entities/DailyLog.cpp
  src/entities/CalorieTracker.cpp

  # repositories
  src/repositories/UserRepository.cpp
  src/repositories/LocalNutritionRepository.cpp
  src/repositories/InMemoryMealRepository.cpp

  # services
  src/services/UserService.cpp
  src/services/MealService.cpp
)

target_include_directories(app_lib PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Main executable (application)
add_executable(CS_3140_Project src/main.cpp)
target_link_libraries(CS_3140_Project PRIVATE app_lib)

# Unit tests
add_executable(my_test test/my_test.cpp)
target_link_libraries(my_test PRIVATE app_lib gtest_main)
add_test(NAME unit_tests COMMAND my_test)
