/***
 * Notification:
 *  -> Brief: Lightweight notification value object used to inform users
***/
#ifndef NOTIFICATION_H
#define NOTIFICATION_H


#include <string>
#include <iostream>

class Notification {
private:
    std::string message;
    std::string title;

public:
    // Default construct an empty notification
    Notification() = default;

    // Construct a notification with message and title
    Notification(const std::string &m, const std::string &t) : message(m), title(t) {}

    // Send/emit the notification (currently writes to stdout)
    void send() const { std::cout << "[Notification] " << title << ": " << message << std::endl; }
};
#endif
