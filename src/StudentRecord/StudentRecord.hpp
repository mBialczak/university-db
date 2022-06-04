#pragma once

#include <string>

namespace university::student_record {
class StudentRecord
{
  public:
    StudentRecord(std::string firstName,
                  std::string lastName,
                  std::string address);
    // getters
    std::string firstName() const;
    std::string lastName() const;
    std::string address() const;

  private:
    std::string first_name_;
    std::string last_name_;
    std::string address_;
};

}   // namespace university::student_record