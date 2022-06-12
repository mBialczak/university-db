#include "UniversityDB.hpp"

#include "StudentRecord/StudentRecord.hpp"

namespace university {

bool UniversityDB::addStudent(const std::string& firstName,
                              const std::string& lastName,
                              const std::string& pesel,
                              const std::string& address,
                              const student_record::Gender gender)
{
    student_record::StudentRecord added { student_record::IndexNo(1),
                                          firstName,
                                          lastName,
                                          pesel,
                                          address,
                                          gender };
    students_.emplace_back(added);
}

std::size_t UniversityDB::size() const
{
    return students_.size();
}

}   // namespace university