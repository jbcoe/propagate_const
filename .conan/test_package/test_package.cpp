#include <propagate_const.h>
#include <memory>
#include <iostream>
#include <stdexcept>

class component {
public:
    [[noreturn]] std::string message() { throw std::runtime_error("Do not call the non-const version of this function"); }
    std::string message() const { return "The const version of message has been called"; }
};

class owner {
public:
    owner() : m_component(std::make_unique<component>()){}

    std::string message() const { return m_component->message(); }
private:
    std::experimental::propagate_const<std::unique_ptr<component>> m_component;
};

int main()
{
    const owner pointer_owner;
    std::cout << pointer_owner.message() << std::endl;
    return EXIT_SUCCESS;
}
