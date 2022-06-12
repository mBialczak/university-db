#pragma once

#include "PeselValidator/PeselValidator.hpp"
#include "StudentRecord/StudentRecord.hpp"

#include <cstddef>
#include <string>
#include <vector>
namespace university {

class UniversityDB
{
  public:
    bool addStudent(student_record::IndexNo index,
                    const std::string& firstName,
                    const std::string& lastName,
                    const std::string& pesel,
                    const std::string& address,
                    const student_record::Gender gender);
    // TODO:: add this
    //  void addStudent(const StudentRecord&);
    std::size_t size() const;

  private:
    pesel_validator::PeselValidator pesel_validator_;
    std::vector<student_record::StudentRecord> students_;
};   // namespace UniversityDB

}   // namespace university

// TODO: valid index number implementation