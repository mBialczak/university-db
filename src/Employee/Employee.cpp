#include "Employee.hpp"

#include <ostream>

namespace university::employee {

Employee::Employee(const std::string& id,
                   const std::string& firstName,
                   const std::string& lastName,
                   const std::string& pesel,
                   const std::string& address,
                   person::Gender gender,
                   double salary)
    : Person(firstName, lastName, pesel, address, gender)
    , id_(id)
    , salary_(salary)

{ }

std::string Employee::id() const
{
    return id_;
}

double Employee::salary() const
{
    return salary_;
}

void Employee::setSalary(double newSalary)
{
    salary_ = newSalary;
}

std::ostream& Employee::sendToStream(std::ostream& os) const
{
    os << "Employee: " + id_ + "\n"
       << "First name: " + first_name_ + "\n"
       << "Last name: " + last_name_ + "\n"
       << "PESEL: " + pesel_ + "\n"
       << "Address: " + address_ + "\n"
       << "Gender: ";
    std::string gender = (gender_ == person::Gender::male) ? "male"
                                                           : "female";
    os << gender + "\n"
       << "Salary: " + std::to_string(salary_)
       << std::endl;

    return os;
}
}   // namespace university::employee
