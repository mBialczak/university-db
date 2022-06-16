#include "UniversityDB.hpp"

#include <algorithm>

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

bool UniversityDB::addStudent(const student_record::StudentRecord& record)
{
    if (pesel_validator_(record.pesel())) {
        students_.emplace_back(record);
        return true;
    }

    return false;
}

bool UniversityDB::addStudent(student_record::StudentRecord&& record)
{
    if (pesel_validator_(record.pesel())) {
        students_.emplace_back(std::move(record));
        return true;
    }

    return false;
}

std::size_t UniversityDB::size() const
{
    return students_.size();
}

std::optional<student_record::StudentRecord> UniversityDB::findByPesel(const std::string& pesel) const
{
    auto result_iter = std::find_if(students_.begin(),
                                    students_.end(),
                                    [&pesel](const auto& record) {
                                        return record.pesel() == pesel;
                                    });
    if (result_iter != students_.end()) {
        return *result_iter;
    }

    return std::nullopt;
}

std::vector<student_record::StudentRecord> UniversityDB::findByLastName(const std::string& lastName) const
{
    std::vector<student_record::StudentRecord> found_students;
    std::copy_if(students_.begin(),
                 students_.end(),
                 std::back_inserter(found_students),
                 [&lastName](const auto& record) {
                     return record.lastName() == lastName;
                 });

    return found_students;
}
}   // namespace university
