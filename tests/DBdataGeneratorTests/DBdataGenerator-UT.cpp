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
using university::person::Person;
using university::pesel_validator::PeselValidator;
using namespace testing;

class DBdataGeneratorShould : public Test
{
  public:
    DBdataGeneratorShould()
        : sut(database_)
    { }

  protected:
    university::UniversityDB database_;
    university::data_generator::DBdataGenerator sut;
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
    // due to randomness of generated first names and reasonably constrained set of
    // possible names it is hard to predict, how many different names there should be
    // in the given set not causing the test to fail randomly. The expected set-size of
    // generated names need to reasonably low then.
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
    // due to randomness of generated  names and reasonably constrained set of
    // possible names it is hard to predict, how many different names there should be
    // in the given set not causing the test to fail randomly. The expected set-size of
    // generated names need to reasonably low then.
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
    // due to randomness of generated addresses and reasonably constrained set of
    // possible addresses it is hard to predict, how many different addresses there should be
    // in the given set not causing the test to fail randomly. The expected set-size of
    // generated names need to reasonably low then.
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
    // due to randomness of generated genders it is hard to predict, how many male of females
    // there should be in the generated database not causing the test to fail randomly.
    // The expected count of each needs to be reasonably low then.
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
    // due to randomness of generated first names and reasonably constrained set of
    // possible names it is hard to predict, how many different names there should be
    // in the given set not causing the test to fail randomly. The expected set-size of
    // generated names need to reasonably low then.
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
    // due to randomness of generated  names and reasonably constrained set of
    // possible names it is hard to predict, how many different names there should be
    // in the given set not causing the test to fail randomly. The expected set-size of
    // generated names need to reasonably low then.
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
    // due to randomness of generated addresses and reasonably constrained set of
    // possible addresses it is hard to predict, how many different addresses there should be
    // in the given set not causing the test to fail randomly. The expected set-size of
    // generated names need to reasonably low then.
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
    // due to randomness of generated genders it is hard to predict, how many male of females
    // there should be in the generated database not causing the test to fail randomly.
    // The expected count of each needs to be reasonably low then.
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
    // due to randomness of generated salaries, it is hard to predict, how many different salaries
    // there should be in the given set not causing the test to fail randomly. The expected set-size of
    // generated names need to reasonably low then.
    EXPECT_GE(generatedSalaries.size(), 95);
}

}   // namespace university::data_generator::tests
