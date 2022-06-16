#include "PeselValidatorMock.hpp"
#include "StudentRecord/StudentRecord.hpp"
#include "UniversityDB/UniversityDB.hpp"

#include "gtest/gtest.h"

namespace university::ut {

using student_record::Gender;
using student_record::IndexNo;
using student_record::StudentRecord;
using testing::Test;

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

TEST_F(UniversityDBTest, ShouldAddNewStudentWithCorrectPeselAndChangeSize)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);

    EXPECT_EQ(sut.size(), 2);
}

}   // end of namespace university::ut
