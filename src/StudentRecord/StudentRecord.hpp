#pragma once

#include <string>

namespace university::student_record {

using IndexNo = unsigned long;

enum class Gender
{
    male,
    female
};

class StudentRecord
{
  public:
    StudentRecord(IndexNo indexNumber,
                  const std::string& firstName,
                  const std::string& lastName,
                  const std::string& pesel,
                  const std::string& address,
                  Gender gender);
    // getters
    std::string firstName() const;
    std::string lastName() const;
    std::string pesel() const;
    std::string address() const;
    IndexNo index() const;
    Gender gender() const;

    bool operator==(const StudentRecord&) const = default;

  private:
    IndexNo index_;
    std::string first_name_;
    std::string last_name_;
    std::string pesel_;
    std::string address_;
    Gender gender_;
};

}   // namespace university::student_record