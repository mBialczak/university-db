// TODO: VERIFY all includes
#include "DBdataGenerator/DBdataGenerator.hpp"
#include "Employee/Employee.hpp"
#include "PeselValidator/PeselValidator.hpp"
#include "Student/Student.hpp"
#include "UniversityDB/UniversityDB.hpp"
// TODO: REMOVE

// #include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace university::data_generator::tests {
// TODO: VERIFY
//  using employee::Employee;
//  using person::Gender;
//  using student::IndexNo;
using student::Student;
using university::pesel_validator::PeselValidator;
using namespace testing;

// TODO: REMOVE
// ====== TEST-CASES TO COVER

/*
Generate student should:
                        OK generate student with not empty index number choosen
- generated index number should be in the predefined set
- for larger number of indexNo there should be some randomness
- add test for format of index

                        OK  generate student with valid (not empty) firstName
- first name should be from predefined set predefined set
- for larger number of firstName there should be some randomness

                        OK  generate student with valid (not empty) lastName
- first name should be from predefined set predefined set
- for larger number of lastName there should be some randomness

- generate student with valid  pesel

                        OK generate student with valid (not empty) address
- address should be from predefined set predefined set
- for larger number of address there should be some randomness

- for gender in larger set there should be at least some different genders


Generate employee should:
- generate employee with valid pesel


STATISTICS test

*/

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

TEST_F(DBdataGeneratorShould, generateStudentsWithNotEmptyFirstName)
{
    sut.addStudents(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        // TODO: VERIFY
        //  std::dynamic_pointer_cast<Student>(person);
        EXPECT_FALSE(person->firstName().empty());
    }
}

TEST_F(DBdataGeneratorShould, generateStudentsWithNotEmptyLastName)
{
    sut.addStudents(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        // TODO: VERIFY
        //  std::dynamic_pointer_cast<Student>(person);
        EXPECT_FALSE(person->lastName().empty());
    }
}

TEST_F(DBdataGeneratorShould, generateStudentsWithValidPesel)
{
    sut.addStudents(20);
    auto db_internal_data = database_.data();
    PeselValidator validator;

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        // TODO: VERIFY
        //  std::dynamic_pointer_cast<Student>(person);
        EXPECT_TRUE(validator(person->pesel()));
    }
}

TEST_F(DBdataGeneratorShould, generateStudentsWithNotEmptyAddress)
{
    sut.addStudents(20);
    auto db_internal_data = database_.data();

    EXPECT_EQ(database_.size(), 20);
    for (const auto& person : db_internal_data) {
        // TODO: VERIFY
        //  std::dynamic_pointer_cast<Student>(person);
        EXPECT_FALSE(person->address().empty());
    }
}

// TEST(GeneratedStudentShould, haveNotEmptyFirstName)
// {
//     for (auot i = 0; i < 10; ++i) {
//         Student student = DBdataGenerator::generateStudent();

//         EXPECT_FALSE(student.firstName().empty);
//     };
// }

// TEST(GeneratedStudentShould, haveNotEmptyLastName)
// {
//     for (auot i = 0; i < 10; ++i) {
//         Student student = DBdataGenerator::generateStudent();

//         EXPECT_FALSE(student.lastName().empty);
//     }
// }

// TEST(GeneratedStudentShould, haveNotEmptyAndValidPesel)
// {
//     pesel_validator validator;

//     for (auot i = 0; i < 10; ++i) {
//         Student student = DBdataGenerator::generateStudent();

//         EXPECT_FALSE(student.pesel().empty);
//         EXPECT_TRUE(validator.validatePesel(student.pesel()));
//     }
// }

// TEST(GeneratedStudentShould, haveNotEmptyAddress)
// {
//     for (auot i = 0; i < 10; ++i) {
//         Student student = DBdataGenerator::generateStudent();

//         EXPECT_FALSE(student.address().empty);
//     }
// }

}   // namespace university::data_generator::tests