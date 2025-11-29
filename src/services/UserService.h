/***
 * UserService:
 *  -> Brief: Business layer for registering and retrieving users
 ***/
#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <memory>
#include <string>
#include "../repositories/IUserRepository.h"

class UserService {
public:
    explicit UserService(std::shared_ptr<IUserRepository> repo);

    // register a user and return id. `goalCalories` is the daily calorie target.
    int registerUser(const std::string &name, int age, const std::string &email, int goalCalories = 2000);

    // Lookup helpers
    std::unique_ptr<RegularUser> findByEmail(const std::string &email);
    std::unique_ptr<RegularUser> getById(int id);

private:
    std::shared_ptr<IUserRepository> repository;
};

#endif // USERSERVICE_H
