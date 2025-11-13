#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <iostream>

class Notification {
private:
    std::string message;
    std::string title;

public:
    Notification() = default;
    Notification(const std::string &m, const std::string &t) : message(m), title(t) {}

    void send() const { std::cout << "[Notification] " << title << ": " << message << std::endl; }
};

#endif
