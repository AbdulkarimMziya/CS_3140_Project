/***
 *
 *  -> Brief: Domain-specific exception types used by repositories/services
***/


#ifndef CS_3140_PROJECT_EXCEPTIONS_H
#define CS_3140_PROJECT_EXCEPTIONS_H


#include <stdexcept>
#include <string>

class FileIOException : public std::runtime_error {
public:
    explicit FileIOException(const std::string &msg)
        : std::runtime_error("File I/O error: " + msg) {}
};

class RepositoryException : public std::runtime_error {
public:
    explicit RepositoryException(const std::string &msg)
        : std::runtime_error("Repository error: " + msg) {}
};

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string &msg)
        : std::runtime_error("Validation error: " + msg) {}
};

#endif // CS_3140_PROJECT_EXCEPTIONS_H
