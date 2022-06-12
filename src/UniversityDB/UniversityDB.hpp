#pragma once

#include <cstddef>
#include <string>
#include <vector>
namespace university {

namespace student_record {
    class StudentRecord;
    enum class Gender;
}   // namespace student_record

namespace pesel_validator {
    class PeselValidator;
}

class UniversityDB
{
  public:
    bool addStudent(const std::string& firstName,
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