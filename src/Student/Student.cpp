#include "Student.hpp"

#include <ostream>
namespace university::student {

Student::Student(IndexNo indexNumber,
                 const std::string& firstName,
                 const std::string& lastName,
                 const std::string& pesel,
                 const std::string& address,
                 person::Gender gender)
    : Person(firstName, lastName, pesel, address, gender)
    , index_(indexNumber)

{
}

IndexNo Student::index() const
{
    return index_;
}

std::ostream& operator<<(std::ostream& os, const Student& student)
{
    os << "First name: " + student.firstName() + "\n"
       << "Last name: " + student.lastName() + "\n"
       << "PESEL: " + student.pesel() + "\n"
       << "Index number: " + std::to_string(student.index()) + "\n"
       << "Address: " + student.address() + "\n"
       << "Gender: ";
    std::string gender = (student.gender() == person::Gender::male) ? "male"
                                                                    : "female";
    os << gender << std::endl;

    return os;
}
}   // namespace university::student
