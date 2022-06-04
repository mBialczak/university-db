#pragma once

#include <string>

namespace university::student_record {

using IndexNo = unsigned long;

class StudentRecord
{

  public:
    StudentRecord(IndexNo indexNumber,
                  std::string firstName,
                  std::string lastName,
                  std::string address);
    // getters
    std::string firstName() const;
    std::string lastName() const;
    std::string address() const;
    IndexNo index() const;

  private:
    IndexNo index_;
    std::string first_name_;
    std::string last_name_;
    std::string address_;
};

}   // namespace university::student_record