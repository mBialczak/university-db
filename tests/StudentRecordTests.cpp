#include "StudentRecord/StudentRecord.hpp"

#include "gtest/gtest.h"
namespace university::student_record::ut {

class StudentRecordTests : public ::testing::Test
{
  protected:
    StudentRecord rec1_ { "John", "Dickens" };
};

TEST_F(StudentRecordTests, FirstNameShouldReturnStudentsFirstName)
{
    EXPECT_EQ(rec1_.firstName(), "John");
}

TEST_F(StudentRecordTests, LastNameShouldReturnSutdentsLastName)
{
    EXPECT_EQ(rec1_.lastName(), "Dickens");
}

}   // namespace university::student_record::ut
