#include "StudentRecord.hpp"

namespace university::student_record {

StudentRecord::StudentRecord(std::string firstName,
                             std::string lastName,
                             std::string address)
    : first_name_(firstName)
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

}   // namespace university::student_record