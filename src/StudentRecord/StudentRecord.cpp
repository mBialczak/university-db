#include "StudentRecord.hpp"

namespace university::student_record {

StudentRecord::StudentRecord(IndexNo indexNumber,
                             std::string firstName,
                             std::string lastName,
                             std::string address,
                             Gender gender)
    : index_(indexNumber)
    , first_name_(firstName)
    , last_name_(lastName)
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

}   // namespace university::student_record
