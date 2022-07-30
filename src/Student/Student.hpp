#pragma once

#include "Person/Person.hpp"

namespace university::student {

using IndexNo = unsigned long;

class Student : public person::Person
{
  public:
    Student(const std::string& indexNumber,
            const std::string& firstName,
            const std::string& lastName,
            const std::string& pesel,
            const std::string& address,
            person::Gender gender);

    std::string index() const;

    bool operator==(const Student&) const = default;

  private:
    std::string index_;
};

std::ostream& operator<<(std::ostream& os, const Student& student);
}   // namespace university::student
