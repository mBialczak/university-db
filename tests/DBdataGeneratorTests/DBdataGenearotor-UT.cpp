// TODO: VERIFY all includes
#include "Employee/Employee.hpp"
#include "Student/Student.hpp"
// #include "UniversityDB/UniversityDB.hpp"
#include "DBdataGenerator/DBdataGenerator.hpp"
// TODO: REMOVE
// #include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace university::data_generator::tests {
// TODO: VERIFY
//  using employee::Employee;
//  using person::Gender;
//  using student::IndexNo;
using student::Student;
using namespace testing;
}   // namespace university::data_generator::tests

// TODO: REMOVE
// ====== TESTCASES TO COVER

/*
Generate student should:
- generate student with not empty index number choosen
- generated index number should be in the predefined set
- for larger number of indexNo there should be some randomness

- generate student with valid (not empty) firstName
- first name should be from predefined set predefined set
- for larger number of firstName there should be some randomness

- generate student with valid (not empty) lastName
- first name should be from predefined set predefined set
- for larger number of lastName there should be some randomness

- generate student with valid random pesel

- generate student with valid (not empty) address
- first name should be from predefined set predefined set
- for larger number of address there should be some randomness

- for gender in larger set there should be at least some different genders


Generate employee should:
- generate employee with valid pesel


STATISTICS test

*/

TEST(GeneratedStudentShould, haveNotEmptyIndexNo)
{
    Student student1 = DBdataGenerator::generateStudent();

    EXPECT_FALSE(student1.index().empty)
}