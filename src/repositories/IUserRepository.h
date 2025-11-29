/***
 *  IUserRepository:
 *  -> Brief: Interface for managing and retrieving RegularUser objects
***/

#ifndef IUSERREPOSITORY_H
#define IUSERREPOSITORY_H


#include <memory>
#include <vector>
#include <string>
#include "../entities/RegularUser.h"

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    // Create user and return assigned id
    virtual int createUser(const RegularUser &user) = 0;

    // Load user by id or email
    virtual std::unique_ptr<RegularUser> getUserById(int id) = 0;
    virtual std::unique_ptr<RegularUser> getUserByEmail(const std::string &email) = 0;

    // List all users (simple utility)
    virtual std::vector<RegularUser> listAll() = 0;
};

#endif // IUSERREPOSITORY_H
