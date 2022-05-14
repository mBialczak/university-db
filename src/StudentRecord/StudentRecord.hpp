#pragma once
#include <string>
class StudentRecord
{
  public:
    StudentRecord(std::string firstName, std::string lastName);

  private:
    std::string first_name_;
    std::string last_name_;
};