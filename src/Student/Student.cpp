#include "Student.hpp"

#include <ostream>
namespace university::student {

Student::Student(const std::string& indexNumber,
                 const std::string& firstName,
                 const std::string& lastName,
                 const std::string& pesel,
                 const std::string& address,
                 person::Gender gender)
    : Person(firstName, lastName, pesel, address, gender)
    , index_(indexNumber)

{
}

std::string Student::index() const
{
    return index_;
}

std::ostream& Student::sendToStream(std::ostream& os) const
{
    os << "STUDENT"
       << "\n"
       << "-------------"
       << "\n"
       << "Index number: " + index_ + "\n"
       << "First name: " + first_name_ + "\n"
       << "Last name: " + last_name_ + "\n"
       << "PESEL: " + pesel_ + "\n"
       << "Address: " + address_ + "\n"
       << "Gender: ";
    std::string gender = (gender_ == person::Gender::male) ? "male"
                                                           : "female";
    os << gender << std::endl;

    return os;
}
// TODO: remove
//  std::ostream& operator<<(std::ostream& os, const Student& student)
//  {
//      os << "STUDENT"
//         << "\n"
//         << "-------------"
//         << "\n"
//         << "Index number: " + student.index() + "\n"
//         << "First name: " + student.firstName() + "\n"
//         << "Last name: " + student.lastName() + "\n"
//         << "PESEL: " + student.pesel() + "\n"
//         << "Address: " + student.address() + "\n"
//         << "Gender: ";
//      std::string gender = (student.gender() == person::Gender::male) ? "male"
//                                                                      : "female";
//      os << gender << std::endl;

//     return os;
// }
}   // namespace university::student
