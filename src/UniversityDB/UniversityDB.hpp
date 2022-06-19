#pragma once

#include "PeselValidator/PeselValidator.hpp"
#include "StudentRecord/StudentRecord.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
namespace university {

class UniversityDB
{
    using StudentIterator = std::vector<student_record::StudentRecord>::iterator;

  public:
    bool addStudent(const student_record::StudentRecord& record);
    bool addStudent(student_record::StudentRecord&& record);
    bool addStudent(student_record::IndexNo index,
                    const std::string& firstName,
                    const std::string& lastName,
                    const std::string& pesel,
                    const std::string& address,
                    const student_record::Gender gender);
    bool removeStudent(student_record::IndexNo indexNo);

    std::shared_ptr<const student_record::StudentRecord> findByPesel(const std::string& pesel) const;
    std::vector<student_record::StudentRecord> findByLastName(const std::string& lastName) const;

    std::size_t size() const;

  private:
    StudentIterator findByIndex(student_record::IndexNo index);
    pesel_validator::PeselValidator pesel_validator_;
    std::vector<student_record::StudentRecord> students_;
};   // namespace UniversityDB

}   // namespace university
