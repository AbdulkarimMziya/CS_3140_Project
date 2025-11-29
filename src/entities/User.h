/***
 *  User: 
 *  -> Brief: Base class for users (regular and other roles), holds profile and notifications
***/
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
    // Construct a user with explicit id and profile fields
    User(int id, const std::string &n, int a, const std::string &e);

    // Subclasses implement a user-facing report view
    virtual void viewReport() const = 0;

    // Set the user's goal
    void setGoal(const Goal &g);

    // Add a notification to the user's queue (stores a copy)
    void addNotification(const Notification &n);

    // Accessors
    int getId() const { return userId; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getEmail() const { return email; }
};

#endif
