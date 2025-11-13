#include "User.h"
#include <iostream>


User::User(int id, const std::string &n, int a, const std::string &e)
    : userId(id), name(n), age(a), email(e) {}

void User::setGoal(const Goal &g) { goal = g; }

void User::addNotification(const Notification &n) { 
    notifications.push_back(n); 
}
