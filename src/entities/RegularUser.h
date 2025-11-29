#ifndef REGULARUSER_H
#define REGULARUSER_H

#include "User.h"

class RegularUser : public User {
public:
    RegularUser(const std::string &name, int age, const std::string &email);
    
    // Constructor with explicit id (for repositories)
    RegularUser(int id, const std::string &name, int age, const std::string &email);

    // Set or update the user's goal
    void setGoal(const Goal &g) { goal = g; }

    // Return a copy of the user's goal
    Goal getGoal() const { return goal; }

    // Append a notification for the user (stores a copy)
    void addNotification(const Notification &note);

    // Access the stored notifications
    const std::vector<Notification>& getNotifications() const { return notifications; }

    // View the user's report (UI hook)
    void viewReport() const override;

private:
    Goal goal;
    std::vector<Notification> notifications;
};

#endif
