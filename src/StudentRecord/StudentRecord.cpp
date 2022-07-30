#include "StudentRecord.hpp"

#include <ostream>
namespace university::student {

StudentRecord::StudentRecord(IndexNo indexNumber,
                             const std::string& firstName,
                             const std::string& lastName,
                             const std::string& pesel,
                             const std::string& address,
                             Gender gender)
    : index_(indexNumber)
    , first_name_(firstName)
    , last_name_(lastName)
    , pesel_(pesel)
    , address_(address)
    , gender_(gender)
{
}

std::string StudentRecord::firstName() const
{
    return first_name_;
}

std::string StudentRecord::lastName() const
{
    return last_name_;
}

std::string StudentRecord::pesel() const
{
    return pesel_;
}

std::string StudentRecord::address() const
{
    return address_;
}

IndexNo StudentRecord::index() const
{
    return index_;
}

Gender StudentRecord::gender() const
{
    return gender_;
}

std::ostream& operator<<(std::ostream& os, const StudentRecord& student)
{
    os << "First name: " + student.firstName() + "\n"
       << "Last name: " + student.lastName() + "\n"
       << "PESEL: " + student.pesel() + "\n"
       << "Index number: " + std::to_string(student.index()) + "\n"
       << "Address: " + student.address() + "\n"
       << "Gender: ";
    std::string gender = (student.gender() == Gender::male) ? "male"
                                                            : "female";
    os << gender << std::endl;

    return os;
}
}   // namespace university::student
