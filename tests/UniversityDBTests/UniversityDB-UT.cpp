#include "PeselValidatorMock.hpp"
#include "StudentRecord/StudentRecord.hpp"
#include "UniversityDB/UniversityDB.hpp"

#include "gtest/gtest.h"

namespace university::ut {

using student_record::Gender;
using testing::Test;

class UniversityDBTest : public Test
{
  public:
    UniversityDBTest();

  protected:
    UniversityDB sut;
};

UniversityDBTest::UniversityDBTest()
{ }

TEST_F(UniversityDBTest, ShouldBeAbleToAddNewStudentWithCorrectPeselAndChangeSize)
{
    std::string johns_first { "John" };
    std::string johns_last { "Dickens" };
    std::string johns_pesel { "90090515836" };
    std::string johns_address { "England, London, Puddle of Mudd st. 37" };
    Gender johns_gender { Gender::male };

    auto size_before = sut.size();
    sut.addStudent(johns_first,
                   johns_last,
                   johns_pesel,
                   johns_address,
                   johns_gender);

    EXPECT_EQ(sut.size(), size_before + 1);
}

}   // end of namespace university::ut
