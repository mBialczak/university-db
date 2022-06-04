#include "StudentRecord/StudentRecord.hpp"

#include "gtest/gtest.h"
namespace university::student_record::ut {

class StudentRecordTests : public ::testing::Test
{
  public:
    StudentRecordTests();

  protected:
    StudentRecord rec1_;
};

StudentRecordTests::StudentRecordTests()
    : rec1_(1ul,
            "John",
            "Dickens",
            "England, London, Puddle of Mudd st. 37",
            Gender::male)
{
}

TEST_F(StudentRecordTests, FirstNameShouldReturnStudentsFirstName)
{
    EXPECT_EQ(rec1_.firstName(), "John");
}

TEST_F(StudentRecordTests, LastNameShouldReturnSutdentsLastName)
{
    EXPECT_EQ(rec1_.lastName(), "Dickens");
}

TEST_F(StudentRecordTests, AddressShouldReturnStudentsAddres)
{
    EXPECT_EQ(rec1_.address(), "England, London, Puddle of Mudd st. 37");
}

TEST_F(StudentRecordTests, IndexShouldReturnIndexNumber)
{
    EXPECT_EQ(rec1_.index(), 1u);
}

TEST_F(StudentRecordTests, GenderShouldReturnStudentsGender)
{
    EXPECT_EQ(rec1_.gender(), Gender::male);
}
}   // namespace university::student_record::ut
