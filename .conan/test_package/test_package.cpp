#include <propagate_const.h>
#include <memory>
#include <iostream>
#include <stdexcept>

class test {
public:
    test() : m_message(std::make_unique<std::string>("The const version of message has been called")){}

    [[noreturn]] std::string message() { throw std::runtime_error("Do not call the non-const version of this function"); }
    const std::string& message() const { return *m_message; }
private:
    std::experimental::propagate_const<std::unique_ptr<std::string>> m_message;
};

int main()
{
    const test pointer_owner;
    std::cout << pointer_owner.message();
    return EXIT_SUCCESS;
}
