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

    std::ostream& sendToStream(std::ostream& os) const override;
    std::string index() const;

    bool operator==(const Student&) const = default;

  private:
    std::string index_;
};
}   // namespace university::student
