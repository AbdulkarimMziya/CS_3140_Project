#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Goal.h"
#include "Notification.h"

class User {
protected:
    int userId;
    std::string name;
    int age;
    std::string email;
    Goal goal;
    std::vector<Notification> notifications;

public:
    User(int id, const std::string &n, int a, const std::string &e);
    // Subclasses must implement a report view.
    virtual void viewReport() const = 0;
    void setGoal(const Goal &g);
    void addNotification(const Notification &n);
};

#endif
