#include "UserService.h"
#include "../repositories/UserRepository.h"
#include "../entities/Goal.h"

UserService::UserService(std::shared_ptr<IUserRepository> repo) : repository(std::move(repo)) {}

int UserService::registerUser(const std::string &name, int age, const std::string &email, int goalCalories) {
    RegularUser tmp(name, age, email);
    // set the user's daily goal before persisting
    tmp.setGoal(Goal(goalCalories, GoalPeriod::Daily));
    return repository->createUser(tmp);
}

std::unique_ptr<RegularUser> UserService::findByEmail(const std::string &email) {
    return repository->getUserByEmail(email);
}

std::unique_ptr<RegularUser> UserService::getById(int id) {
    return repository->getUserById(id);
}
