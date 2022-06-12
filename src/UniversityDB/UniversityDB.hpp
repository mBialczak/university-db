#pragma once

// #include "StudentRecord/StudentRecord.hpp"

#include <cstddef>
#include <vector>

namespace university {

namespace student_record {
    class StudentRecord;
}

using student_record::StudentRecord;

class UniversityDB
{
  public:
    std::size_t size() const;

  private:
    std::vector<StudentRecord> students_;
};

}   // namespace university