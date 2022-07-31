#pragma once

#include "Person/Person.hpp"

namespace university::employee {

class Employee : public person::Person
{
  public:
    Employee(const std::string& id,
             const std::string& firstName,
             const std::string& lastName,
             const std::string& pesel,
             const std::string& address,
             person::Gender gender,
             double salary);
    std::ostream& sendToStream(std::ostream& os) const override;
    // getters
    std::string id() const;
    double salary() const;
    // setters
    void setSalary(double newSalary);

    bool operator==(const Employee&) const = default;

  private:
    std::string id_;
    double salary_;
};
// TODO: remove
//  std::ostream& operator<<(std::ostream& os, const Employee& student);
}   // namespace university::employee
