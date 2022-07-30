#pragma once

#include <string>

namespace university::person {

enum class Gender
{
    male,
    female
};

class Person
{
  public:
    Person(const std::string& firstName,
           const std::string& lastName,
           const std::string& pesel,
           const std::string& address,
           Gender gender);

    virtual ~Person() = default;

    std::string firstName() const;
    std::string lastName() const;
    std::string pesel() const;
    std::string address() const;
    Gender gender() const;

    bool operator==(const Person&) const = default;

  protected:
    std::string first_name_;
    std::string last_name_;
    std::string pesel_;
    std::string address_;
    Gender gender_;
};

}   // namespace university::person
