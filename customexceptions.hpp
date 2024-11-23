#include <exception>
#include <iostream>

using namespace std;

class value_not_in_tree : public exception
{
private:
    const char *message;

public:
    value_not_in_tree(const char *msg)
    {
        message = msg;
    }

    const char *what() const noexcept
    {
        return message;
    }
};

class empty_tree_exception : public exception
{
private:
    const char *message;

public:
    empty_tree_exception(const char *msg)
    {
        message = msg;
    }

    const char *what() const noexcept
    {
        return message;
    }
};

class key_exception : public exception
{
private:
    const char *message;

public:
    key_exception(const char *msg)
    {
        message = msg;
    }

    const char *what() const noexcept
    {
        return message;
    }
};

class size_exception : public exception
{
private:
    const char *message;

public:
    size_exception(const char *msg)
    {
        message = msg;
    }

    const char *what() const noexcept
    {
        return message;
    }
};