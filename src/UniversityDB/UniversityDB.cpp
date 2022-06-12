#include "UniversityDB.hpp"

namespace university {

bool UniversityDB::addStudent(student_record::IndexNo index,
                              const std::string& firstName,
                              const std::string& lastName,
                              const std::string& pesel,
                              const std::string& address,
                              const student_record::Gender gender)
{
    if (pesel_validator_(pesel)) {
        student_record::StudentRecord added { index,
                                              firstName,
                                              lastName,
                                              pesel,
                                              address,
                                              gender };
        students_.emplace_back(added);
        return true;
    }

    return false;
}

std::size_t UniversityDB::size() const
{
    return students_.size();
}

}   // namespace university