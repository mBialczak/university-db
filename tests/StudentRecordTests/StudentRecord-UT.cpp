#include "StudentRecord/StudentRecord.hpp"

#include "gtest/gtest.h"
namespace university::student::ut {

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
           "90090515836",
           "England, London, Puddle of Mudd st. 37",
           Gender::male)
    , sally(5ul,
            "Sally",
            "Smith",
            "81100216357",
            "Australia, Sydney, Long Shore st. 22",
            Gender::female)
{
}

TEST_F(StudentRecordTests, firstNameShouldReturnStudentsFirstName)
{
    EXPECT_EQ(john.firstName(), "John");
    EXPECT_EQ(sally.firstName(), "Sally");
}

TEST_F(StudentRecordTests, lastNameShouldReturnSutdentsLastName)
{
    EXPECT_EQ(john.lastName(), "Dickens");
    EXPECT_EQ(sally.lastName(), "Smith");
}

TEST_F(StudentRecordTests, addressShouldReturnStudentsAddres)
{
    EXPECT_EQ(john.address(), "England, London, Puddle of Mudd st. 37");
    EXPECT_EQ(sally.address(), "Australia, Sydney, Long Shore st. 22");
}

TEST_F(StudentRecordTests, indexShouldReturnIndexNumber)
{
    EXPECT_EQ(john.index(), 1ul);
    EXPECT_EQ(sally.index(), 5ul);
}

TEST_F(StudentRecordTests, genderShouldReturnStudentsGender)
{
    EXPECT_EQ(john.gender(), Gender::male);
    EXPECT_EQ(sally.gender(), Gender::female);
}

TEST_F(StudentRecordTests, peselShouldReturnStudentsPesel)
{
    EXPECT_EQ(john.pesel(), "90090515836");
    EXPECT_EQ(sally.pesel(), "81100216357");
}

std::string prepPatternString(const StudentRecord& student)
{
    std::string pattern;
    pattern += "First name: " + student.firstName() + "\n";
    pattern += "Last name: " + student.lastName() + "\n";
    pattern += "PESEL: " + student.pesel() + "\n";
    pattern += "Index number: " + std::to_string(student.index()) + "\n";
    pattern += "Address: " + student.address() + "\n";
    pattern += "Gender: ";
    pattern += student.gender() == Gender::male ? "male"
                                                : "female";
    pattern += "\n";

    return pattern;
}

TEST_F(StudentRecordTests, outputOperatorShouldCorretlyInsertStudentRecordToOuptutStream)
{
    std::string pattern1 = prepPatternString(john);
    std::string pattern2 = prepPatternString(sally);
    std::ostringstream osstream;

    osstream << john;
    std::string insertion_result1 = osstream.str();
    osstream.str("");
    osstream << sally;
    std::string insertion_result2 = osstream.str();

    EXPECT_EQ(pattern1, insertion_result1);
    EXPECT_EQ(pattern2, insertion_result2);
}
}   // namespace university::student::ut
