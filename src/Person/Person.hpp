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
    virtual std::ostream& sendToStream(std::ostream& os) const = 0;

    bool operator==(const Person&) const = default;
    virtual bool operator<(const Person&) const;

  protected:
    std::string first_name_;
    std::string last_name_;
    std::string pesel_;
    std::string address_;
    Gender gender_;
};

std::ostream& operator<<(std::ostream& os, const Person& person);
}   // namespace university::person
