#include "StudentRecord/StudentRecord.hpp"

#include "gtest/gtest.h"
namespace university::student_record::ut {

class StudentRecordTests : public ::testing::Test
{
  public:
    StudentRecordTests();

  protected:
    StudentRecord john;
    StudentRecord sally;
};

StudentRecordTests::StudentRecordTests()
    : john(1ul,
           "John",
           "Dickens",
           "England, London, Puddle of Mudd st. 37",
           Gender::male)
    , sally(5ul,
            "Sally",
            "Smith",
            "Australia, Sydney, Long Shore st. 22",
            Gender::female)
{
}

TEST_F(StudentRecordTests, FirstNameShouldReturnStudentsFirstName)
{
    EXPECT_EQ(john.firstName(), "John");
    EXPECT_EQ(sally.firstName(), "Sally");
}

TEST_F(StudentRecordTests, LastNameShouldReturnSutdentsLastName)
{
    EXPECT_EQ(john.lastName(), "Dickens");
    EXPECT_EQ(sally.lastName(), "Smith");
}

TEST_F(StudentRecordTests, AddressShouldReturnStudentsAddres)
{
    EXPECT_EQ(john.address(), "England, London, Puddle of Mudd st. 37");
    EXPECT_EQ(sally.address(), "Australia, Sydney, Long Shore st. 22");
}

TEST_F(StudentRecordTests, IndexShouldReturnIndexNumber)
{
    EXPECT_EQ(john.index(), 1ul);
    EXPECT_EQ(sally.index(), 5ul);
}

TEST_F(StudentRecordTests, GenderShouldReturnStudentsGender)
{
    EXPECT_EQ(john.gender(), Gender::male);
    EXPECT_EQ(sally.gender(), Gender::female);
}
}   // namespace university::student_record::ut
