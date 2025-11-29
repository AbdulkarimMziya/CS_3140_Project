/***
 * UserRepository:
 *  -> Brief: File-backed repository that handles `RegularUser` records in a CSV file
 *            Provides create/read/list operations and handles basic parsing/serialization.
 ***/
#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "IUserRepository.h"
#include <string>
#include <algorithm>


/***
 * Assisted by GitHub Copilot, adapted by A.K. Mziya, 2025-11-28 
 *  -> Brief: common string helpers (trim, toLower) reused across repos
***/
static inline std::string trim(const std::string &s) {
    auto b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return std::string();
    auto e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

static inline std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

class UserRepository : public IUserRepository {
public:
    explicit UserRepository(const std::string &filePath = "users.txt");

    int createUser(const RegularUser &user) override;
    std::unique_ptr<RegularUser> getUserById(int id) override;
    std::unique_ptr<RegularUser> getUserByEmail(const std::string &email) override;
    std::vector<RegularUser> listAll() override;

private:
    std::string path;
    void load();
    void persist();

    std::vector<RegularUser> users;
};

#endif // USERREPOSITORY_H
