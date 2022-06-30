#include "StudentRecord/StudentRecord.hpp"
#include "UniversityDB/UniversityDB.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <filesystem>

namespace university::mt {

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
    StudentRecord valid_rec_3;
    StudentRecord valid_rec_4;
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
    , valid_rec_3({ IndexNo { 333ul },
                    "Anna",
                    "Zielinska",
                    "90090515836",
                    "Poland, Opole, ul. Sobotnia 15A",
                    Gender::female })
    , valid_rec_4({ IndexNo { 144ul },
                    "Peter",
                    "Pikiel",
                    "67040500538",
                    "Poland, Zabrze, ul. Nieznana 1C/44",
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

TEST_F(UniversityDBTest, addStudentShouldAddNewStudentWithCorrectPeselFromCompositeData)
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

TEST_F(UniversityDBTest, addStudentShouldNOTaddNewStudentWithInvalidPeselFromCompositeData)
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

TEST_F(UniversityDBTest, addStudentShouldAddNewStudentWithCorrectPeselFromReadyStudentRecord)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    sut.addStudent(valid_rec_3);
    sut.addStudent(valid_rec_4);

    EXPECT_EQ(sut.size(), 4);
}

TEST_F(UniversityDBTest, addStudentShouldNOTaddNewStudentWithInvalidPeselFromReadyStudentRecord)
{
    sut.addStudent(invalid_rec_1);
    sut.addStudent(invalid_rec_2);

    EXPECT_EQ(sut.size(), 0);
}

TEST_F(UniversityDBTest, addStudentShouldAddNewStudentUsingMoveSemanticsFromCompositeData)
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

TEST_F(UniversityDBTest, findByPeselShouldFindStudentIfExistsInDatabase)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    sut.addStudent(valid_rec_3);
    sut.addStudent(valid_rec_4);
    auto retrieved_student = sut.findByPesel(valid_rec_2.pesel());
    auto should_not_be_found = sut.findByPesel("65071209862");

    EXPECT_EQ(*retrieved_student, valid_rec_2);
    EXPECT_EQ(should_not_be_found, nullptr);
}

TEST_F(UniversityDBTest, findByLastNameShouldFindAllStudentsWithSameLastNameIfAnyExistInDatabase)
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

TEST_F(UniversityDBTest, removeStudentShouldFindAndRemoveStudentRecordGivenIndexNo)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    sut.addStudent(valid_rec_3);
    sut.addStudent(valid_rec_4);
    auto size_before_removal = sut.size();

    bool has_removed = sut.removeStudent(valid_rec_1.index());

    EXPECT_TRUE(has_removed);
    EXPECT_EQ(sut.size(), size_before_removal - 1ul);
}

TEST_F(UniversityDBTest, removeStudentShouldDoNothingIfThereIsNoStudentWithGivenRecord)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    sut.addStudent(valid_rec_3);
    sut.addStudent(valid_rec_4);
    auto size_before_removal = sut.size();
    IndexNo non_existing_index = valid_rec_1.index() + 5ul;

    bool has_removed = sut.removeStudent(non_existing_index);

    ASSERT_NE(valid_rec_2.index(), non_existing_index);
    ASSERT_NE(valid_rec_3.index(), non_existing_index);
    ASSERT_NE(valid_rec_4.index(), non_existing_index);
    EXPECT_FALSE(has_removed);
    EXPECT_EQ(sut.size(), size_before_removal);
}

TEST_F(UniversityDBTest, sortByLastNameShouldCorrectlyRearangeDataBaseRecords)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    sut.addStudent(valid_rec_3);
    sut.addStudent(valid_rec_4);

    sut.sortByLastName();

    EXPECT_THAT(sut.data(), ElementsAre(valid_rec_2, valid_rec_4, valid_rec_1, valid_rec_3));
}

TEST_F(UniversityDBTest, sortByPeselShouldCorrectlyRearangeDataBaseRecords)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    sut.addStudent(valid_rec_3);
    sut.addStudent(valid_rec_4);

    sut.sortByPesel();

    EXPECT_THAT(sut.data(), ElementsAre(valid_rec_4, valid_rec_1, valid_rec_2, valid_rec_3));
}

void addStudentsToPattern(const std::vector<StudentRecord>& students, std::string& pattern)
{
    int counter { 1 };
    for (const auto& student : students) {
        pattern += "Student record "
            + std::to_string(counter) + "\n"
            + " ------------------\n"
            + "First name: " + student.firstName() + "\n"
            + "Last name: " + student.lastName() + "\n"
            + "PESEL: " + student.pesel() + "\n"
            + "Index number: " + std::to_string(student.index()) + "\n"
            + "Address: " + student.address() + "\n"
            + "Gender: ";
        std::string gender = (student.gender() == Gender::male) ? "male"
                                                                : "female";
        pattern += gender + "\n";
        pattern += "========================================\n";
        ++counter;
    }
}

TEST_F(UniversityDBTest, displayShouldCorrectlyInsertRecordToOuptutStream)
{
    std::string pattern;
    std::vector<StudentRecord> students { valid_rec_1,
                                          valid_rec_2,
                                          valid_rec_3,
                                          valid_rec_4 };
    addStudentsToPattern(students, pattern);
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    sut.addStudent(valid_rec_3);
    sut.addStudent(valid_rec_4);
    // ostringstream used as substitution for std::cout and other streams
    std::ostringstream osstream;

    sut.Display(osstream);
    std::string display_result = osstream.str();

    EXPECT_EQ(pattern, display_result);
}

TEST_F(UniversityDBTest, outputOperatorShouldCorrectlyInsertRecordToOuptutStream)
{
    std::string pattern;
    std::vector<StudentRecord> students { valid_rec_1,
                                          valid_rec_2,
                                          valid_rec_3,
                                          valid_rec_4 };
    addStudentsToPattern(students, pattern);
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    sut.addStudent(valid_rec_3);
    sut.addStudent(valid_rec_4);
    // ostringstream used as substitution for std::cout
    std::ostringstream osstream;

    osstream << sut;
    std::string operator_result = osstream.str();

    EXPECT_EQ(pattern, operator_result);
}

std::string getPathToReadingTemplateFile()
{
    std::string current_path = std::filesystem::current_path().string();
    auto position = current_path.find("build");
    std::string path_to_template = current_path.substr(0, position);
    path_to_template += "test-resources/File-reading-template.txt";

    return path_to_template;
}

std::string getPathToWritingTemplateFile()
{
    std::string current_path = std::filesystem::current_path().string();
    auto position = current_path.find("build");
    std::string path_to_template = current_path.substr(0, position);
    path_to_template += "test-resources/File-writing-template.txt";

    return path_to_template;
}

TEST_F(UniversityDBTest, readFromFileShouldCorrectlyReadDatabaseFromFile)
{
    std::string path_to_template = getPathToReadingTemplateFile();
    // prepare second database for comparison
    UniversityDB databaseToCompare;
    databaseToCompare.addStudent(valid_rec_1);
    databaseToCompare.addStudent(valid_rec_2);
    databaseToCompare.addStudent(valid_rec_3);
    databaseToCompare.addStudent(valid_rec_4);

    int records_read = sut.readFromFile(path_to_template.data());
    auto internalStateToCompare = databaseToCompare.data();
    auto internalStateReadToSut = sut.data();

    EXPECT_EQ(records_read, 4);
    EXPECT_EQ(internalStateToCompare, internalStateReadToSut);
}

TEST_F(UniversityDBTest, writeToFileShouldCorrectlyWriteDatabaseToFile)
{
    sut.addStudent(valid_rec_1);
    sut.addStudent(valid_rec_2);
    sut.addStudent(valid_rec_3);
    sut.addStudent(valid_rec_4);
    std::string path_to_write = getPathToWritingTemplateFile();

    int records_written = sut.writeToFile(path_to_write.data());
    UniversityDB sut_to_compare;
    int records_read_back = sut_to_compare.readFromFile(path_to_write.data());

    EXPECT_EQ(records_written, 4);
    EXPECT_EQ(records_read_back, 4);
    EXPECT_EQ(sut.data(), sut_to_compare.data());
}
}   // end of namespace university::mt
