#pragma once

namespace university {

class StudentRecord;
class UniversityDB
{
  public:
    std::size_t size() const;

  private:
    std::vector<StudentRecord> students_;
};

}   // namespace university