#include <exception>
#include <iostream>

using namespace std;

class value_not_in_tree : public exception {
private:
    const char* message;
public:
    // Constructor
    value_not_in_tree(const char* msg) {
        message = msg;
    }

    // Override the what() method
    const char* what() const noexcept {
        return message;
    }
};


class empty_tree_exception : public exception {
private:
    const char* message;
public:
    // Constructor
    empty_tree_exception(const char* msg) {
        message = msg;
    }

    // Override the what() method
    const char* what() const noexcept {
        return message;
    }
};