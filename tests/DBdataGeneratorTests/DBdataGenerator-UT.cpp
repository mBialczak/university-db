#include "DBdataGenerator/DBdataGenerator.hpp"
#include "Employee/Employee.hpp"
#include "PeselValidator/PeselValidator.hpp"
#include "Student/Student.hpp"
#include "UniversityDB/UniversityDB.hpp"

// #include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace university::data_generator::tests {
using employee::Employee;
using person::Gender;
using student::Student;
using university::data_generator::DBdataGenerator;
using university::person::Person;
using university::pesel_validator::PeselValidator;
using namespace testing;

// NOTE: the only purpose of providing teetable class is to force-set
//       the seed of random-number generator member of DBdataGenerator
//       in order to provide stable testing
class DBdataGeneratorTestable : public DBdataGenerator
{
  public:
    DBdataGeneratorTestable(UniversityDB& dataBaseToFill)
        : DBdataGenerator(dataBaseToFill)
    {
        generator_.seed(1);
    }
};

class DBdataGeneratorShould : public Test
{
  public:
    DBdataGeneratorShould()
        : sut(database_)
    { }

  protected:
    university::UniversityDB database_;
    DBdataGeneratorTestable sut;
};

TEST_F(DBdataGeneratorShould, generateStudentsWithNotEmptyIndexNo)
{
    sut.addStudents(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_FALSE(std::dynamic_pointer_cast<Student>(person)->index().empty());
    }
}

TEST_F(DBdataGeneratorShould, generatedIndexesShouldBeDifferent)
{
    sut.addStudents(100);
    std::set<std::string> generatedIndexes;
    for (const auto& person : database_.data()) {
        auto student = std::dynamic_pointer_cast<Student>(person);
        ASSERT_TRUE(student);
        generatedIndexes.insert(student->index());
    }
    // because UniversityDB does not allow to insert students with same index number,
    // all the indexes in the database should be different
    EXPECT_EQ(database_.size(), generatedIndexes.size());
}

TEST_F(DBdataGeneratorShould, generateStudentsWithNotEmptyFirstName)
{
    sut.addStudents(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_FALSE(person->firstName().empty());
    }
}

TEST_F(DBdataGeneratorShould, generatedStudentsShouldHaveReasonablyDifferentFirstNames)
{
    sut.addStudents(100);
    std::set<std::string> generatedFirstNames;
    for (const auto& person : database_.data()) {
        auto student = std::dynamic_pointer_cast<Student>(person);
        ASSERT_TRUE(student);
        generatedFirstNames.insert(student->firstName());
    }
    // due to usage of random number generator internally in DBdataGenerator, the
    // stability of tests is ensured by:
    //   1. setting the hard-coded seed in DBdataGeneratorTestable
    //   2. keeping the  expected size of generated names set at reasonably low value
    //      (the available range of different names is constrained, and we do not intend
    //      to test the quality of random generator but the fact, that SUT tries to pick
    //      different names each time).
    // The chosen value was tested with --gtest_repeat=1000 not causing the test to break
    EXPECT_GE(generatedFirstNames.size(), 40);
}

TEST_F(DBdataGeneratorShould, generateStudentsWithNotEmptyLastName)
{
    sut.addStudents(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_FALSE(person->lastName().empty());
    }
}

TEST_F(DBdataGeneratorShould, generatedStudentsShouldHaveReasonablyDifferentLastNames)
{
    sut.addStudents(100);
    std::set<std::string> generatedLastNames;
    for (const auto& person : database_.data()) {
        auto student = std::dynamic_pointer_cast<Student>(person);
        ASSERT_TRUE(student);
        generatedLastNames.insert(student->lastName());
    }
    // due to usage of random number generator internally in DBdataGenerator, the
    // stability of tests is ensured by:
    //   1. setting the hard-coded seed in DBdataGeneratorTestable
    //   2. keeping the  expected size of generated names set at reasonably low value
    //      (the available range of different names is constrained, and we do not intend
    //      to test the quality of random generator but the fact, that SUT tries to pick
    //      different names each time).
    // The chosen value was tested with --gtest_repeat=1000 not causing the test to break
    EXPECT_GE(generatedLastNames.size(), 60);
}

TEST_F(DBdataGeneratorShould, generateStudentsWithValidPesel)
{
    sut.addStudents(20);
    auto db_internal_data = database_.data();
    PeselValidator validator;

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_TRUE(validator(person->pesel()));
    }
}

TEST_F(DBdataGeneratorShould, generatedStudentsShouldHaveDifferentPesels)
{
    sut.addStudents(100);
    std::set<std::string> generatedPesels;
    for (const auto& person : database_.data()) {
        auto student = std::dynamic_pointer_cast<Student>(person);
        ASSERT_TRUE(student);
        generatedPesels.insert(student->pesel());
    }
    // because UniversityDB does not allow to insert people with same pesel number,
    // all the pesels in the database should be different
    EXPECT_EQ(database_.size(), generatedPesels.size());
}

TEST_F(DBdataGeneratorShould, generateStudentsWithNotEmptyAddress)
{
    sut.addStudents(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_FALSE(person->address().empty());
    }
}

TEST_F(DBdataGeneratorShould, generatedStudentsShouldHaveReasonablyDifferentAddresses)
{
    sut.addStudents(100);
    std::set<std::string> generatedAddresses;
    for (const auto& person : database_.data()) {
        auto student = std::dynamic_pointer_cast<Student>(person);
        ASSERT_TRUE(student);
        generatedAddresses.insert(student->address());
    }
    // due to usage of random number generator internally in DBdataGenerator, the
    // stability of tests is ensured by:
    //   1. setting the hard-coded seed in DBdataGeneratorTestable
    //   2. keeping the  expected size of generated addresses set at reasonably low value
    //      (the available range of different addresses is constrained, and we do not intend
    //      to test the quality of random generator but the fact, that SUT tries to pick
    //      different address each time).
    // The chosen value was tested with --gtest_repeat=1000 not causing the test to break
    EXPECT_GE(generatedAddresses.size(), 75);
}

TEST_F(DBdataGeneratorShould, generatedStudentsShouldHaveReasonablyDifferentGenders)
{
    sut.addStudents(100);
    std::map<Gender, int> generatedGenders;
    for (const auto& person : database_.data()) {
        auto student = std::dynamic_pointer_cast<Student>(person);
        ASSERT_TRUE(student);
        Gender gender = student->gender();
        if (gender == Gender::female) {
            generatedGenders[Gender::female] += 1;
        }
        else {
            generatedGenders[Gender::male] += 1;
        }
    }
    // due to usage of random number generator internally in DBdataGenerator, the
    // stability of tests is ensured by:
    //   1. setting the hard-coded seed in DBdataGeneratorTestable
    //   2. keeping the  expected size of generated genders set at reasonably low value
    //      (the available range of different gender is just 2 and we do not intend
    //      to test the quality of random generator but the fact, that SUT tries to pick
    //      different gender each time).
    // The chosen value was tested with --gtest_repeat=1000 not causing the test to break
    EXPECT_GE(generatedGenders[Gender::female], 25);
    EXPECT_GE(generatedGenders[Gender::male], 25);
}

TEST_F(DBdataGeneratorShould, generateEmployeesWithNotEmptyId)
{
    sut.addEmployees(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_FALSE(std::dynamic_pointer_cast<Employee>(person)->id().empty());
    }
}

TEST_F(DBdataGeneratorShould, generatedIdsShouldBeDifferent)
{
    sut.addEmployees(100);
    std::set<std::string> generatedIds;
    for (const auto& person : database_.data()) {
        auto employee = std::dynamic_pointer_cast<Employee>(person);
        ASSERT_TRUE(employee);
        generatedIds.insert(employee->id());
    }
    // because UniversityDB does not allow to insert employees with same id,
    // all the ids in the database should be different
    EXPECT_EQ(database_.size(), generatedIds.size());
}

TEST_F(DBdataGeneratorShould, generateEmployeesWithNotEmptyFirstName)
{
    sut.addEmployees(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_FALSE(person->firstName().empty());
    }
}

TEST_F(DBdataGeneratorShould, generatedEmployeesShouldHaveReasonablyDifferentFirstNames)
{
    sut.addEmployees(100);
    std::set<std::string> generatedFirstNames;
    for (const auto& person : database_.data()) {
        auto employee = std::dynamic_pointer_cast<Employee>(person);
        ASSERT_TRUE(employee);
        generatedFirstNames.insert(employee->firstName());
    }
    // due to usage of random number generator internally in DBdataGenerator, the
    // stability of tests is ensured by:
    //   1. setting the hard-coded seed in DBdataGeneratorTestable
    //   2. keeping the  expected size of generated names set at reasonably low value
    //      (the available range of different names is constrained, and we do not intend
    //      to test the quality of random generator but the fact, that SUT tries to pick
    //      different name each time).
    // The chosen value was tested with --gtest_repeat=1000 not causing the test to break
    EXPECT_GE(generatedFirstNames.size(), 40);
}

TEST_F(DBdataGeneratorShould, generateEmployeesWithNotEmptyLastName)
{
    sut.addEmployees(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_FALSE(person->lastName().empty());
    }
}

TEST_F(DBdataGeneratorShould, generatedEmployeesShouldHaveReasonablyDifferentLastNames)
{
    sut.addEmployees(100);
    std::set<std::string> generatedLastNames;
    for (const auto& person : database_.data()) {
        auto employee = std::dynamic_pointer_cast<Employee>(person);
        ASSERT_TRUE(employee);
        generatedLastNames.insert(employee->lastName());
    }
    // due to usage of random number generator internally in DBdataGenerator, the
    // stability of tests is ensured by:
    //   1. setting the hard-coded seed in DBdataGeneratorTestable
    //   2. keeping the  expected size of generated names set at reasonably low value
    //      (the available range of different names is constrained, and we do not intend
    //      to test the quality of random generator but the fact, that SUT tries to pick
    //      different name each time).
    // The chosen value was tested with --gtest_repeat=1000 not causing the test to break
    EXPECT_GE(generatedLastNames.size(), 60);
}

TEST_F(DBdataGeneratorShould, generateEmployeesWithValidPesel)
{
    sut.addEmployees(20);
    auto db_internal_data = database_.data();
    PeselValidator validator;

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_TRUE(validator(person->pesel()));
    }
}

TEST_F(DBdataGeneratorShould, generatedeEmployeesShouldHaveDifferentPesels)
{
    sut.addEmployees(100);
    std::set<std::string> generatedPesels;
    for (const auto& person : database_.data()) {
        auto employee = std::dynamic_pointer_cast<Employee>(person);
        ASSERT_TRUE(employee);
        generatedPesels.insert(employee->pesel());
    }
    // because UniversityDB does not allow to insert people with same pesel number,
    // all the pesels in the database should be different
    EXPECT_EQ(database_.size(), generatedPesels.size());
}

TEST_F(DBdataGeneratorShould, generateEmployeesWithNotEmptyAddress)
{
    sut.addEmployees(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_FALSE(person->address().empty());
    }
}

TEST_F(DBdataGeneratorShould, generatedEmployeesShouldHaveReasonablyDifferentAddresses)
{
    sut.addEmployees(100);
    std::set<std::string> generatedAddresses;
    for (const auto& person : database_.data()) {
        auto employee = std::dynamic_pointer_cast<Employee>(person);
        ASSERT_TRUE(employee);
        generatedAddresses.insert(employee->address());
    }
    // due to usage of random number generator internally in DBdataGenerator, the
    // stability of tests is ensured by:
    //   1. setting the hard-coded seed in DBdataGeneratorTestable
    //   2. keeping the  expected size of generated addresses set at reasonably low value
    //      (the available range of different addresses is constrained, and we do not intend
    //      to test the quality of random generator but the fact, that SUT tries to pick
    //      different address each time).
    // The chosen value was tested with --gtest_repeat=1000 not causing the test to break
    EXPECT_GE(generatedAddresses.size(), 75);
}

TEST_F(DBdataGeneratorShould, generatedEmployeesShouldHaveReasonablyDifferentGenders)
{
    sut.addEmployees(100);
    std::map<Gender, int> generatedGenders;
    for (const auto& person : database_.data()) {
        auto employee = std::dynamic_pointer_cast<Employee>(person);
        ASSERT_TRUE(employee);
        Gender gender = employee->gender();
        if (gender == Gender::female) {
            generatedGenders[Gender::female] += 1;
        }
        else {
            generatedGenders[Gender::male] += 1;
        }
    }
    // due to usage of random number generator internally in DBdataGenerator, the
    // stability of tests is ensured by:
    //   1. setting the hard-coded seed in DBdataGeneratorTestable
    //   2. keeping the  expected size of generated genders set at reasonably low value
    //      (the available range of different gender is just 2 and we do not intend
    //      to test the quality of random generator but the fact, that SUT tries to pick
    //      different gender each time).
    // The chosen value was tested with --gtest_repeat=1000 not causing the test to break
    EXPECT_GE(generatedGenders[Gender::female], 25);
    EXPECT_GE(generatedGenders[Gender::male], 25);
}

TEST_F(DBdataGeneratorShould, generateEmployeesWithSalaryWithinGivenRange)
{
    sut.addEmployees(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        EXPECT_GT(std::dynamic_pointer_cast<Employee>(person)->salary(), 1000.0);
        EXPECT_LT(std::dynamic_pointer_cast<Employee>(person)->salary(), 15000.0);
    }
}

TEST_F(DBdataGeneratorShould, generatedEmployeesShouldHaveReasonablyDifferentSalary)
{
    sut.addEmployees(100);
    std::set<double> generatedSalaries;
    for (const auto& person : database_.data()) {
        auto employee = std::dynamic_pointer_cast<Employee>(person);
        ASSERT_TRUE(employee);
        generatedSalaries.insert(employee->salary());
    }
    // due to usage of random number generator internally in DBdataGenerator, the
    // stability of tests is ensured by:
    //   1. setting the hard-coded seed in DBdataGeneratorTestable
    //   2. keeping the  expected size of generated genders set at reasonably low value
    //      (although the available range of different salaries is not very much constrained,
    //       but it is still possible to generate two equal random doubles). Note that we
    //       do not intend to test the quality of random generator but the fact, that SUT tries
    //      to pick different salary each time).
    // The chosen value was tested with --gtest_repeat=1000 not causing the test to break
    EXPECT_GE(generatedSalaries.size(), 95);
}

}   // namespace university::data_generator::tests
