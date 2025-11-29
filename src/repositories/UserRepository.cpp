#include "UserRepository.h"
#include "../entities/IdGenerator.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "../entities/Exceptions.h"

/***
 * Assisted by GitHub Copilot, adapted by A.K. Mziya, 2025-11-28 
 *  -> Brief: reuse header-provided string helpers (trim)
 ***/

UserRepository::UserRepository(const std::string &filePath) : path(filePath) {
    load();
}

void UserRepository::load() {
    users.clear();
    std::ifstream in(path);
    if (!in) return; // no file yet

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string idStr, name, ageStr, email, goalStr;
        if (!std::getline(ss, idStr, ',')) continue;
        if (!std::getline(ss, name, ',')) continue;
        if (!std::getline(ss, ageStr, ',')) continue;
        if (!std::getline(ss, email, ',')) continue;
       
        std::getline(ss, goalStr, ',');
        try {
            int id = std::stoi(trim(idStr));
            int age = std::stoi(trim(ageStr));
            users.emplace_back(id, trim(name), age, trim(email));
            // if goal present and parseable, set it on the last inserted user
            if (!trim(goalStr).empty()) {
                try {
                    int g = std::stoi(trim(goalStr));
                    users.back().setGoal(Goal(g, GoalPeriod::Daily));
                } catch(...) { /* ignore malformed goal */ }
            }
        } catch (...) {
            continue;
        }
    }
}

void UserRepository::persist() {
    std::ofstream out(path, std::ios::trunc);
    if (!out) throw FileIOException(path);
    for (const auto &u : users) {
        // persist id,name,age,email,goal
        out << u.getId() << "," << u.getName() << "," << u.getAge() << "," << u.getEmail() << "," << u.getGoal().getTarget() << "\n";
    }
}

int UserRepository::createUser(const RegularUser &user) {
    int id = IdGenerator::generateId();
    users.emplace_back(id, user.getName(), user.getAge(), user.getEmail());
    // preserve the user's goal if provided (newer records include goal)
    users.back().setGoal(user.getGoal());
    try {
        persist();
    } catch (const FileIOException &e) {
        // rollback the in-memory insert so repository state remains consistent
        if (!users.empty() && users.back().getId() == id) users.pop_back();
        // rethrow so callers can handle/report the error
        throw;
    }
    return id;
}

std::unique_ptr<RegularUser> UserRepository::getUserById(int id) {
    auto it = std::find_if(users.begin(), users.end(), [&](const RegularUser &u){ return u.getId() == id; });
    if (it == users.end()) return nullptr;
    return std::make_unique<RegularUser>(*it);
}

std::unique_ptr<RegularUser> UserRepository::getUserByEmail(const std::string &email) {
    auto it = std::find_if(users.begin(), users.end(), [&](const RegularUser &u){ return u.getEmail() == email; });
    if (it == users.end()) return nullptr;
    return std::make_unique<RegularUser>(*it);
}

std::vector<RegularUser> UserRepository::listAll() {
    return users;
}
