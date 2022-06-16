#include "PeselValidatorMock.hpp"
#include "StudentRecord/StudentRecord.hpp"
#include "UniversityDB/UniversityDB.hpp"

#include "gtest/gtest.h"

namespace university::ut {

using student_record::Gender;
using student_record::IndexNo;
using student_record::StudentRecord;
using namespace testing;

class UniversityDBTest : public Test
{
  public:
    UniversityDBTest();

  protected:
    UniversityDB sut;
    // student records with valid PESEL numbers
    StudentRecord valid_rec_1;
    StudentRecord valid_rec_2;
    // student records with invalid PESEL numbers;
    StudentRecord invalid_rec_1;
    StudentRecord invalid_rec_2;
};

UniversityDBTest::UniversityDBTest()
    : valid_rec_1({ IndexNo(133ul),
                    "Sally",
                    "Smith",
                    "81100216357",
                    "Poland, Opole, ul. Deszczowa 23/m.22",
                    Gender::female })
    , valid_rec_2({ IndexNo { 173ul },
                    "Joseph",
                    "Kowalski",
                    "90080517455",
                    "Poland, Laskowice, ul. Niedzielna 304A",
                    Gender::male })
    , invalid_rec_1({ IndexNo { 200ul },
                      "Harold",
                      "Butterhand",
                      "2535325",
                      "Poland, Waszawa, ul. Niekaczki 12/80",
                      Gender::male })
    , invalid_rec_2({ IndexNo { 44ul },
                      "Zofia",
                      "Popularna",
                      "7b110c01745",
                      "Poland, Gdynia, ul. Towarowa 80/74",
                      Gender::female })

{ }

TEST_F(UniversityDBTest, ShouldAddNewStudentWithCorrectPeselFromCompositeData)
{
    IndexNo johns_index { 4ul };
    std::string johns_first { "John" };
    std::string johns_last { "Dickens" };
    std::string johns_pesel { "90090515836" };   // valid PESEL
    std::string johns_address { "England, London, Puddle of Mudd st. 37" };
    Gender johns_gender { Gender::male };

    auto size_before = sut.size();
    sut.addStudent(johns_index,
                   johns_first,
                   johns_last,
                   johns_pesel,
                   johns_address,
                   johns_gender);

    EXPECT_EQ(sut.size(), size_before + 1);
}

TEST_F(UniversityDBTest, ShouldNOTaddNewStudentWithInvalidPeselFromCompositeData)
{
    IndexNo joans_index { 12ul };
    std::string joans_first { "Joahne" };
    std::string joans_last { "Hopkins" };
    std::string joans_pesel { "74110101745" };   // invalid PESEL
    std::string joans_address { "Poland, Szczecin, ul. Podmokła 20/10" };
    Gender joans_gender { Gender::female };

    auto size_before = sut.size();
    bool was_student_added = sut.addStudent(joans_index,
                                            joans_first,
                                            joans_last,
                                            joans_pesel,
                                            joans_address,
                                            joans_gender);
    auto size_after = sut.size();
    EXPECT_FALSE(was_student_added);
    EXPECT_EQ(size_before, size_after);
}

TEST_F(UniversityDBTest, ShouldAddNewStudentWithCorrectPesel)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);

    EXPECT_EQ(sut.size(), 2);
}

TEST_F(UniversityDBTest, ShouldNOTaddNewStudentWithInvalidPesel)
{
    sut.addStudent(invalid_rec_1);
    sut.addStudent(invalid_rec_2);

    EXPECT_EQ(sut.size(), 0);
}

TEST_F(UniversityDBTest, ShouldAddNewStudentUsingMoveSemanticsFromCompositeData)
{
    auto size_before = sut.size();
    sut.addStudent(StudentRecord(4ul,
                                 "John",
                                 "Dickens",
                                 "90090515836",
                                 "England, London, Puddle of Mudd st. 37",
                                 Gender::male));

    EXPECT_EQ(sut.size(), size_before + 1);
}

TEST_F(UniversityDBTest, ShouldFindStudentBasedOnPeselIfExistsInDatabase)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    std::optional<StudentRecord> retrieved_student = sut.findByPesel(valid_rec_2.pesel());
    std::optional<StudentRecord> should_not_be_found = sut.findByPesel("65071209862");

    EXPECT_EQ(*retrieved_student, valid_rec_2);
    EXPECT_EQ(should_not_be_found, std::nullopt);
}

TEST_F(UniversityDBTest, ShouldFindAllStudentsWithSameLastNameIfAnyExistInDatabase)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    StudentRecord student_with_same_name { 339ul,
                                           "John",
                                           valid_rec_1.lastName(),
                                           "67040500538",
                                           "Poland, Gdynia, ul. Towarowa 80/74",
                                           Gender::male };
    sut.addStudent(student_with_same_name);

    auto retrieved_students = sut.findByLastName(valid_rec_1.lastName());
    auto should_not_be_found = sut.findByLastName("Psikuta");

    EXPECT_EQ(should_not_be_found.size(), 0);
    EXPECT_EQ(retrieved_students.size(), 2);
    EXPECT_EQ(retrieved_students[0].lastName(), valid_rec_1.lastName());
    EXPECT_EQ(retrieved_students[1].lastName(), valid_rec_1.lastName());
}

}   // end of namespace university::ut
