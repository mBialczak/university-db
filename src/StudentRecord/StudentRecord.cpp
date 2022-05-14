#include "StudentRecord.hpp"

namespace university::student_record {

StudentRecord::StudentRecord(std::string firstName, std::string lastName)
    : first_name_(firstName)
    , last_name_(lastName)
{
}

std::string StudentRecord::firstName() const
{
    return first_name_;
}

}   // namespace university::student_record