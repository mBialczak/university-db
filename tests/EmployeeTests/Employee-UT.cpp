#include "Employee/Employee.hpp"

#include "gtest/gtest.h"
namespace university::employee::ut {

using person::Gender;

class EmployeeTests : public ::testing::Test
{
  public:
    EmployeeTests();

  protected:
    Employee john;
    Employee sally;
};

EmployeeTests::EmployeeTests()
    : john("Teacher:001",
           "John",
           "Dickens",
           "90090515836",
           "England, London, Puddle of Mudd st. 37",
           Gender::male,
           6500.50)
    , sally("Administrative:001",
            "Sally",
            "Smith",
            "81100216357",
            "Australia, Sydney, Long Shore st. 22",
            Gender::female,
            4800.33)
{
}

TEST_F(EmployeeTests, idShouldReturnUniverityId)
{
    EXPECT_EQ(john.id(), "Teacher:001");
    EXPECT_EQ(sally.id(), "Administrative:001");
}

TEST_F(EmployeeTests, salaryShouldReturnEmployeesSalary)
{
    EXPECT_EQ(john.salary(), 6500.50);
    EXPECT_EQ(sally.salary(), 4800.33);
}

TEST_F(EmployeeTests, setSalaryShouldChangeEmployeesSalary)
{
    john.setSalary(3000.0);
    sally.setSalary(7000.0);

    EXPECT_EQ(john.salary(), 3000.0);
    EXPECT_EQ(sally.salary(), 7000.0);
}

std::string prepPatternString(const Employee& employee)
{
    std::string pattern;
    pattern += "Employee: " + employee.id() + "\n";
    pattern += "First name: " + employee.firstName() + "\n";
    pattern += "Last name: " + employee.lastName() + "\n";
    pattern += "PESEL: " + employee.pesel() + "\n";
    pattern += "Address: " + employee.address() + "\n";
    pattern += "Gender: ";
    pattern += employee.gender() == Gender::male ? "male"
                                                 : "female";
    pattern += "\n";
    pattern += "Salary: " + std::to_string(employee.salary()) + "\n";

    return pattern;
}

TEST_F(EmployeeTests, outputOperatorShouldCorrectlyInsertEmployeeToOuptutStream)
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
}   // namespace university::employee::ut
