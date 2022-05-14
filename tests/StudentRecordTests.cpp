#include "StudentRecord/StudentRecord.hpp"

#include "gtest/gtest.h"
namespace university::student_record::ut {

class StudentRecordTests : public ::testing::Test
{
  protected:
    StudentRecord record_1_ { "John", "Dickens" };
};

TEST_F(StudentRecordTests, FirstNameShouldReturnStudentsFirstName)
{
    EXPECT_EQ(record_1_.firstName(), "John");
}

}   // namespace university::student_record::ut