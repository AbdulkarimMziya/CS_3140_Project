#include "RegularUser.h"
#include <iostream>

RegularUser::RegularUser(const std::string &name, int age, const std::string &email)
    : User(-1, name, age, email), goal(2000, GoalPeriod::Daily) {}

RegularUser::RegularUser(int id, const std::string &name, int age, const std::string &email)
    : User(id, name, age, email), goal(2000, GoalPeriod::Daily) {}

void RegularUser::addNotification(const Notification &note) {
    notifications.push_back(note);
    note.send();
}

void RegularUser::viewReport() const {
    std::cout << "Report available via CalorieTracker for " << name << "\n";
}
