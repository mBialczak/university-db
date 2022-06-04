#include "StudentRecord.hpp"

namespace university::student_record {

StudentRecord::StudentRecord(IndexNo indexNumber,
                             std::string firstName,
                             std::string lastName,
                             std::string address)
    : index_(indexNumber)
    , first_name_(firstName)
    , last_name_(lastName)
    , address_(address)
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

}   // namespace university::student_record
