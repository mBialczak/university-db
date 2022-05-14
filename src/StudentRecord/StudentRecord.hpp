#pragma once

#include <string>
class StudentRecord
{
  public:
    StudentRecord(std::string firstName, std::string lastName);
    // getters
    std::string firstName() const;

  private:
    std::string first_name_;
    std::string last_name_;
};