#include "Employee/Employee.hpp"
#include "Student/Student.hpp"
#include "UniversityDB/UniversityDB.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <filesystem>

namespace university::mt {

using employee::Employee;
using person::Gender;
using student::IndexNo;
using student::Student;
using namespace testing;

class UniversityDBTest : public Test
{
  public:
    UniversityDBTest();

  protected:
    UniversityDB sut;
    // student records with valid PESEL numbers
    Student ok_student_1;
    Student ok_student_2;
    Student ok_student_3;
    Student ok_student_4;
    Employee ok_employee_1;
    Employee ok_employee_2;
    // student records with invalid PESEL numbers;
    Student invalid_student_1;
    Student invalid_student_2;
    Employee invalid_employee_1;
    Employee invalid_employee_2;
};

UniversityDBTest::UniversityDBTest()
    : ok_student_1("001/2020",
                   "Sally",
                   "Smith",
                   "81100216357",
                   "Poland, Opole, ul. Deszczowa 23/m.22",
                   Gender::female)
    , ok_student_2("003/2019",
                   "Joseph",
                   "Kowalski",
                   "90080517455",
                   "Poland, Laskowice, ul. Niedzielna 304A",
                   Gender::male)
    , ok_student_3("023/2020",
                   "Anna",
                   "Zielinska",
                   "90090515836",
                   "Poland, Opole, ul. Sobotnia 15A",
                   Gender::female)
    , ok_student_4("012/2018",
                   "Peter",
                   "Pikiel",
                   "67040500538",
                   "Poland, Zabrze, ul. Nieznana 1C/44",
                   Gender::male)
    , ok_employee_1("Teacher:001",
                    "Miroslaw",
                    "Webski",
                    "92071314764",
                    "Poland, Lublin, ul. Cwaniaka 4D/28",
                    Gender::male,
                    6500.50)
    , ok_employee_2("Management:003",
                    "Sandra",
                    "Tulipan",
                    "65071209862",
                    "Poland, Szczecin, ul. Zachodnia 33/83",
                    Gender::female,
                    10000.40)
    , invalid_student_1("032/2022",
                        "Harold",
                        "Butterhand",
                        "2535325",
                        "Poland, Waszawa, ul. Niekaczki 12/80",
                        Gender::male)
    , invalid_student_2("003/2018",
                        "Zofia",
                        "Popularna",
                        "7b110c01745",
                        "Poland, Gdynia, ul. Towarowa 80/74",
                        Gender::female)
    , invalid_employee_1("Administrative:008",
                         "Nicolas",
                         "Sadowski",
                         "99012723456",
                         "Poland, Zabrze, ul. Topolowa 144",
                         Gender::male,
                         5300.00)
    , invalid_employee_2("Management:012",
                         "Anna",
                         "Cudna",
                         "6704050053A",
                         "Poland, Wielkie Wody, ul. Zalana 48/30",
                         Gender::female,
                         9700.90)
{ }

TEST_F(UniversityDBTest, addStudentShouldAddNewStudentWithCorrectPeselFromCompositeData)
{
    std::string johns_index { "099/2017" };
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
    std::string joans_index { "011/2018" };
    std::string joans_first { "Joanne" };
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

TEST_F(UniversityDBTest, addStudentShouldAddNewStudentWithCorrectPeselFromReadyStudent)
{
    sut.addStudent(ok_student_1);
    sut.addStudent(ok_student_2);
    sut.addStudent(ok_student_3);
    sut.addStudent(ok_student_4);

    EXPECT_EQ(sut.size(), 4);
}

TEST_F(UniversityDBTest, addStudentShouldNOTaddNewStudentWithInvalidPeselFromReadyStudent)
{
    sut.addStudent(invalid_student_1);
    sut.addStudent(invalid_student_2);

    EXPECT_EQ(sut.size(), 0);
}

TEST_F(UniversityDBTest, addStudentShouldAddNewStudentUsingMoveSemanticsFromCompositeData)
{
    auto size_before = sut.size();
    sut.addStudent(Student("004/2020",
                           "John",
                           "Dickens",
                           "90090515836",
                           "England, London, Puddle of Mudd st. 37",
                           Gender::male));

    EXPECT_EQ(sut.size(), size_before + 1);
}

TEST_F(UniversityDBTest, findByPeselShouldFindStudentIfExistsInDatabase)
{
    sut.addStudent(ok_student_1);
    sut.addStudent(ok_student_2);
    sut.addStudent(ok_student_3);
    sut.addStudent(ok_student_4);
    auto retrieved_student = sut.findByPesel(ok_student_2.pesel());
    auto should_not_be_found = sut.findByPesel("65071209862");

    EXPECT_EQ(*retrieved_student, ok_student_2);
    EXPECT_EQ(should_not_be_found, nullptr);
}

TEST_F(UniversityDBTest, findByLastNameShouldFindAllStudentsWithSameLastNameIfAnyExistInDatabase)
{
    sut.addStudent(ok_student_1);
    sut.addStudent(ok_student_2);
    Student student_with_same_name { "001/2014",
                                     "John",
                                     ok_student_1.lastName(),
                                     "67040500538",
                                     "Poland, Gdynia, ul. Towarowa 80/74",
                                     Gender::male };
    sut.addStudent(student_with_same_name);

    auto retrieved_students = sut.findByLastName(ok_student_1.lastName());
    auto should_not_be_found = sut.findByLastName("Psikuta");

    EXPECT_EQ(should_not_be_found.size(), 0);
    EXPECT_EQ(retrieved_students.size(), 2);
    EXPECT_EQ(retrieved_students[0]->lastName(), ok_student_1.lastName());
    EXPECT_EQ(retrieved_students[1]->lastName(), ok_student_1.lastName());
}

TEST_F(UniversityDBTest, removeStudentShouldFindAndRemoveStudentGivenIndexNo)
{
    sut.addStudent(ok_student_1);
    sut.addStudent(ok_student_2);
    sut.addStudent(ok_student_3);
    sut.addStudent(ok_student_4);
    auto size_before_removal = sut.size();

    bool has_removed = sut.removeStudent(ok_student_1.index());

    EXPECT_TRUE(has_removed);
    EXPECT_EQ(sut.size(), size_before_removal - 1ul);
}

TEST_F(UniversityDBTest, removeStudentShouldDoNothingIfThereIsNoStudentWithGivenRecord)
{
    sut.addStudent(ok_student_1);
    sut.addStudent(ok_student_2);
    sut.addStudent(ok_student_3);
    sut.addStudent(ok_student_4);
    auto size_before_removal = sut.size();
    std::string non_existing_index { "100/1999" };

    bool has_removed = sut.removeStudent(non_existing_index);

    ASSERT_NE(ok_student_2.index(), non_existing_index);
    ASSERT_NE(ok_student_3.index(), non_existing_index);
    ASSERT_NE(ok_student_4.index(), non_existing_index);
    EXPECT_FALSE(has_removed);
    EXPECT_EQ(sut.size(), size_before_removal);
}

TEST_F(UniversityDBTest, sortByLastNameShouldCorrectlyRearangeDataBaseRecords)
{
    sut.addStudent(ok_student_1);
    sut.addStudent(ok_student_2);
    sut.addStudent(ok_student_3);
    sut.addStudent(ok_student_4);

    sut.sortByLastName();
    auto sorted_people = sut.data();
    EXPECT_EQ(sorted_people[0]->lastName(), ok_student_2.lastName());
    EXPECT_EQ(sorted_people[1]->lastName(), ok_student_4.lastName());
    EXPECT_EQ(sorted_people[2]->lastName(), ok_student_1.lastName());
    EXPECT_EQ(sorted_people[3]->lastName(), ok_student_3.lastName());
}

TEST_F(UniversityDBTest, sortByPeselShouldCorrectlyRearangeDataBaseRecords)
{
    sut.addStudent(ok_student_1);
    sut.addStudent(ok_student_2);
    sut.addStudent(ok_student_3);
    sut.addStudent(ok_student_4);

    sut.sortByPesel();
    auto sorted_people = sut.data();
    EXPECT_EQ(sorted_people[0]->pesel(), ok_student_4.pesel());
    EXPECT_EQ(sorted_people[1]->pesel(), ok_student_1.pesel());
    EXPECT_EQ(sorted_people[2]->pesel(), ok_student_2.pesel());
    EXPECT_EQ(sorted_people[3]->pesel(), ok_student_3.pesel());
}

void addStudentsToPattern(const std::vector<Student>& students, std::string& pattern)
{
    for (const auto& student : students) {
        pattern += std::string("STUDENT\n")
            // + std::to_string(counter) + "\n"
            + "-------------\n"
            + "Index number: " + student.index() + "\n"
            + "First name: " + student.firstName() + "\n"
            + "Last name: " + student.lastName() + "\n"
            + "PESEL: " + student.pesel() + "\n"
            + "Address: " + student.address() + "\n"
            + "Gender: ";
        std::string gender = (student.gender() == Gender::male) ? "male"
                                                                : "female";
        pattern += gender + "\n";
        pattern += "========================================\n";
    }
}

TEST_F(UniversityDBTest, displayShouldCorrectlyInsertRecordToOuptutStream)
{
    std::string pattern;
    std::vector<Student> students { ok_student_1,
                                    ok_student_2,
                                    ok_student_3,
                                    ok_student_4 };
    addStudentsToPattern(students, pattern);
    sut.addStudent(ok_student_1);
    sut.addStudent(ok_student_2);
    sut.addStudent(ok_student_3);
    sut.addStudent(ok_student_4);
    // ostringstream used as substitution for std::cout and other streams
    std::ostringstream osstream;

    sut.Display(osstream);
    std::string display_result = osstream.str();

    EXPECT_EQ(pattern, display_result);
}

TEST_F(UniversityDBTest, outputOperatorShouldCorrectlyInsertRecordToOuptutStream)
{
    std::string pattern;
    std::vector<Student> students { ok_student_1,
                                    ok_student_2,
                                    ok_student_3,
                                    ok_student_4 };
    addStudentsToPattern(students, pattern);
    sut.addStudent(ok_student_1);
    sut.addStudent(ok_student_2);
    sut.addStudent(ok_student_3);
    sut.addStudent(ok_student_4);
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
    path_to_template += "test-resources/File-writing-result-UniversityDB-test.txt";

    return path_to_template;
}

TEST_F(UniversityDBTest, readFromFileShouldCorrectlyReadDatabaseFromFile)
{
    std::string path_to_template = getPathToReadingTemplateFile();
    // prepare second database for comparison
    UniversityDB databaseToCompare;
    databaseToCompare.addStudent(ok_student_1);
    databaseToCompare.addStudent(ok_student_2);
    databaseToCompare.addStudent(ok_student_3);
    databaseToCompare.addStudent(ok_student_4);

    int records_read = sut.readFromFile(path_to_template.data());
    auto internalStateToCompare = databaseToCompare.data();
    auto internalStateReadToSut = sut.data();

    EXPECT_EQ(records_read, 4);
    for (std::size_t i = 0; i < internalStateToCompare.size(); ++i) {
        EXPECT_EQ(*internalStateToCompare[i], *internalStateReadToSut[i]);
    }
}

TEST_F(UniversityDBTest, writeToFileShouldCorrectlyWriteDatabaseToFile)
{
    sut.addStudent(ok_student_1);
    sut.addStudent(ok_student_2);
    sut.addStudent(ok_student_3);
    sut.addStudent(ok_student_4);
    std::string path_to_write = getPathToWritingTemplateFile();

    int records_written = sut.writeToFile(path_to_write.data());
    UniversityDB sut_to_compare;
    int records_read_back = sut_to_compare.readFromFile(path_to_write.data());

    EXPECT_EQ(records_written, 4);
    EXPECT_EQ(records_read_back, 4);
    for (std::size_t i = 0; i < sut.data().size(); ++i) {
        EXPECT_EQ(*sut.data()[i], *sut_to_compare.data()[i]);
    }
}
}   // end of namespace university::mt
