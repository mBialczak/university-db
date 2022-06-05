#include "StudentRecord/StudentRecord.hpp"
#include "UniversityDB/UniversityDB.hpp"

#include "gtest/gtest.h"

namespace university::mt {

using testing::Test;

class UniversityDBTest : public Test
{
  public:
    UniversityDBTest();

  protected:
    UniversityDB sut();
};

UniversityDBTest::UniversityDBTest()
{ }

}   // end of namespace university::mt
