#include "Person.hpp"

namespace university::person {

Person::Person(const std::string& firstName,
               const std::string& lastName,
               const std::string& pesel,
               const std::string& address,
               Gender gender)
    : first_name_(firstName)
    , last_name_(lastName)
    , pesel_(pesel)
    , address_(address)
    , gender_(gender)
{ }

std::string Person::firstName() const
{
    return first_name_;
}

std::string Person::lastName() const
{
    return last_name_;
}

std::string Person::pesel() const
{
    return pesel_;
}

std::string Person::address() const
{
    return address_;
}

Gender Person::gender() const
{
    return gender_;
}

}   // namespace university::person
