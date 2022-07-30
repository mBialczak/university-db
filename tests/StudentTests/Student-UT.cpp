#include "Student/Student.hpp"

#include "gtest/gtest.h"
namespace university::student::ut {

using person::Gender;

class StudentTests : public ::testing::Test
{
  public:
    StudentTests();

  protected:
    Student john;
    Student sally;
};

StudentTests::StudentTests()
    : john("001/2020",
           "John",
           "Dickens",
           "90090515836",
           "England, London, Puddle of Mudd st. 37",
           Gender::male)
    , sally("012/2021",
            "Sally",
            "Smith",
            "81100216357",
            "Australia, Sydney, Long Shore st. 22",
            Gender::female)
{
}

TEST_F(StudentTests, indexShouldReturnIndexNumber)
{
    EXPECT_EQ(john.index(), "001/2020");
    EXPECT_EQ(sally.index(), "012/2021");
}

std::string prepPatternString(const Student& student)
{
    std::string pattern;
    pattern += std::string("STUDENT") + "\n";
    pattern += std::string("-------------") + "\n";
    pattern += "Index number: " + student.index() + "\n";
    pattern += "First name: " + student.firstName() + "\n";
    pattern += "Last name: " + student.lastName() + "\n";
    pattern += "PESEL: " + student.pesel() + "\n";
    pattern += "Address: " + student.address() + "\n";
    pattern += "Gender: ";
    pattern += student.gender() == Gender::male ? "male"
                                                : "female";
    pattern += "\n";

    return pattern;
}

TEST_F(StudentTests, outputOperatorShouldCorrectlyInsertStudentToOuptutStream)
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
