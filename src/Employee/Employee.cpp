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

std::ostream& operator<<(std::ostream& os, const Employee& employee)
{
    os << "Employee: " + employee.id() + "\n"
       << "First name: " + employee.firstName() + "\n"
       << "Last name: " + employee.lastName() + "\n"
       << "PESEL: " + employee.pesel() + "\n"
       << "Address: " + employee.address() + "\n"
       << "Gender: ";
    std::string gender = (employee.gender() == person::Gender::male) ? "male"
                                                                     : "female";
    os << gender + "\n"
       << "Salary: " + std::to_string(employee.salary())
       << std::endl;

    return os;
}
}   // namespace university::employee
