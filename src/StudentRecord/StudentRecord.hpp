#pragma once

#include <string>

namespace university::student_record {
class StudentRecord
{
  public:
    StudentRecord(std::string firstName, std::string lastName);
    // getters
    std::string firstName() const;
    std::string lastName() const;

  private:
    std::string first_name_;
    std::string last_name_;
};

}   // namespace university::student_record