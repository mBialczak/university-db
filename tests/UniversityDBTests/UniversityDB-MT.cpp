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
    void addAllPeopleToDataBase();

    UniversityDB sut;
    // people with valid PESEL numbers
    Student ok_student_1;
    Student ok_student_2;
    Student ok_student_3;
    Student ok_student_4;
    Employee ok_employee_1;
    Employee ok_employee_2;
    // people with invalid PESEL numbers;
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
                    "Kowalski",
                    "92071314764",
                    "Poland, Lublin, ul. Cwaniaka 4D/28",
                    Gender::male,
                    6500.50)
    , ok_employee_2("Management:003",
                    "Sandra",
                    "Smith",
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

void UniversityDBTest::addAllPeopleToDataBase()
{
    sut.add(ok_student_1);
    sut.add(ok_student_2);
    sut.add(ok_employee_1);
    sut.add(ok_student_3);
    sut.add(ok_employee_2);
    sut.add(ok_student_4);
}

TEST_F(UniversityDBTest, addShouldAddNewStudentsAndEmployeesWithCorrectPeselAndReturnTrue)
{
    auto size_before = sut.size();
    bool adding_result_1 = sut.add(ok_student_1);
    bool adding_result_2 = sut.add(ok_student_2);
    bool adding_result_3 = sut.add(ok_employee_1);
    bool adding_result_4 = sut.add(ok_employee_2);

    EXPECT_TRUE(adding_result_1);
    EXPECT_TRUE(adding_result_2);
    EXPECT_TRUE(adding_result_3);
    EXPECT_TRUE(adding_result_4);
    EXPECT_EQ(sut.size(), size_before + 4);
}

TEST_F(UniversityDBTest, addShouldNOTaddNewStudentOrEmployeeWithInvalidPeselAndReturnFalse)
{
    auto size_before = sut.size();

    bool was_student_added = sut.add(invalid_student_1);
    bool was_employee_added = sut.add(invalid_employee_1);
    auto size_after = sut.size();

    EXPECT_FALSE(was_student_added);
    EXPECT_FALSE(was_employee_added);
    EXPECT_EQ(size_before, size_after);
}

TEST_F(UniversityDBTest, addShouldNOTaddNewStudentOrEmployeeIfPeselExistsInDatabaseAndReturnFalse)
{
    sut.add(ok_student_1);
    sut.add(ok_employee_1);
    auto size_before_adding_same_pesel = sut.size();
    std::string same_pesel_1 = ok_student_1.pesel();
    std::string same_pesel_2 = ok_employee_1.pesel();
    Student student_with_same_pesel_1 { "200/2011",
                                        "John",
                                        "Doe",
                                        same_pesel_1,
                                        "USA, New York, Some street no 203",
                                        Gender::male };
    Employee employee_with_same_pesel_1 { "Teacher:010",
                                          "Max",
                                          "Golonko",
                                          same_pesel_1,
                                          "Poland, Opole, ul. Nieznana 14c/28",
                                          Gender::male,
                                          2500.0 };
    Student student_with_same_pesel_2 { "30/2011",
                                        "Sally",
                                        "Doe",
                                        same_pesel_2,
                                        "USA, Chicago, Other Street no 203",
                                        Gender::female };
    Employee employee_with_same_pesel_2 { "Security:020",
                                          "Anna",
                                          "Strong",
                                          same_pesel_2,
                                          "USA, Orlando, Blue street no 203/20",
                                          Gender::female,
                                          7000.0 };

    bool adding_result_1 = sut.add(student_with_same_pesel_1);
    bool adding_result_2 = sut.add(employee_with_same_pesel_1);
    bool adding_result_3 = sut.add(student_with_same_pesel_2);
    bool adding_result_4 = sut.add(employee_with_same_pesel_2);

    EXPECT_FALSE(adding_result_1);
    EXPECT_FALSE(adding_result_2);
    EXPECT_FALSE(adding_result_3);
    EXPECT_FALSE(adding_result_4);
    EXPECT_EQ(sut.size(), size_before_adding_same_pesel);
}

TEST_F(UniversityDBTest, addShouldNOTaddNewStudentIfIndexExistsInDatabaseAndReturnFalse)
{
    sut.add(ok_student_1);
    auto size_before_adding_same_index = sut.size();
    std::string same_index = ok_student_1.index();
    Student student_with_same_index { same_index,
                                      "John",
                                      "Doe",
                                      ok_student_4.pesel(),
                                      "USA, New York, Some street no 203",
                                      Gender::male };

    bool adding_result = sut.add(student_with_same_index);

    EXPECT_FALSE(adding_result);
    EXPECT_EQ(sut.size(), size_before_adding_same_index);
}

TEST_F(UniversityDBTest, addShouldNOTaddNewEmployeeIfIdExistsInDatabaseAndReturnFalse)
{
    sut.add(ok_employee_1);
    auto size_before_adding_same_id = sut.size();
    std::string same_id = ok_employee_1.id();
    Employee employee_with_same_id { same_id,
                                     "Max",
                                     "Golonko",
                                     ok_student_4.pesel(),
                                     "Poland, Opole, ul. Nieznana 14c/28",
                                     Gender::male,
                                     2500.0 };

    bool adding_result = sut.add(employee_with_same_id);

    EXPECT_FALSE(adding_result);
    EXPECT_EQ(sut.size(), size_before_adding_same_id);
}

TEST_F(UniversityDBTest, findByPeselShouldFindPersonIfExistsInDatabase)
{
    sut.add(ok_student_1);
    sut.add(ok_employee_1);
    sut.add(ok_student_2);
    sut.add(ok_student_3);
    sut.add(ok_employee_2);

    auto retrieved_student = sut.findByPesel(ok_student_2.pesel());
    auto retrieved_employee = sut.findByPesel(ok_employee_2.pesel());
    auto should_not_be_found = sut.findByPesel(ok_student_4.pesel());

    EXPECT_EQ(*retrieved_student, ok_student_2);
    EXPECT_EQ(*retrieved_employee, ok_employee_2);
    EXPECT_EQ(should_not_be_found, nullptr);
}

TEST_F(UniversityDBTest, findByLastNameShouldFindAllPersonsWithSameLastNameIfAnyExistInDatabase)
{
    sut.add(ok_student_1);
    sut.add(ok_student_2);
    sut.add(ok_employee_1);
    sut.add(ok_employee_2);
    Student student_with_same_name { "001/2014",
                                     "John",
                                     ok_student_1.lastName(),
                                     "67040500538",
                                     "Poland, Gdynia, ul. Towarowa 80/74",
                                     Gender::male };
    Employee employee_with_same_name { "Teacher: 004",
                                       "Tommy",
                                       ok_student_1.lastName(),
                                       ok_student_4.pesel(),
                                       "Poland, Olsztyn, ul. Wojska Polskiego 30/13",
                                       Gender::male,
                                       4800.0 };
    sut.add(student_with_same_name);
    sut.add(employee_with_same_name);

    auto found_persons = sut.findByLastName(ok_student_1.lastName());
    auto should_not_be_found = sut.findByLastName("Pikiel");

    EXPECT_EQ(should_not_be_found.size(), 0);
    EXPECT_EQ(found_persons.size(), 3);
    EXPECT_EQ(found_persons[0]->lastName(), ok_student_1.lastName());
    EXPECT_EQ(found_persons[1]->lastName(), ok_student_1.lastName());
    EXPECT_EQ(found_persons[2]->lastName(), ok_student_1.lastName());
    EXPECT_NE(found_persons[0]->pesel(), found_persons[1]->pesel());
    EXPECT_NE(found_persons[0]->pesel(), found_persons[2]->pesel());
    EXPECT_NE(found_persons[1]->pesel(), found_persons[2]->pesel());
}

TEST_F(UniversityDBTest, removeStudentShouldFindAndRemoveStudentGivenIndexEvenWhenEmployeesCoexist)
{
    addAllPeopleToDataBase();
    auto size_before_removal = sut.size();

    bool has_removed = sut.removeStudent(ok_student_1.index());

    EXPECT_TRUE(has_removed);
    EXPECT_EQ(sut.size(), size_before_removal - 1ul);
}

TEST_F(UniversityDBTest, removeStudentShouldDoNothingIfThereIsNoStudentWithGivenIndex)
{
    addAllPeopleToDataBase();
    auto size_before_removal = sut.size();
    std::string non_existing_index { "100/1999" };

    bool has_removed = sut.removeStudent(non_existing_index);

    ASSERT_NE(ok_student_2.index(), non_existing_index);
    ASSERT_NE(ok_student_3.index(), non_existing_index);
    ASSERT_NE(ok_student_4.index(), non_existing_index);
    EXPECT_FALSE(has_removed);
    EXPECT_EQ(sut.size(), size_before_removal);
}

TEST_F(UniversityDBTest, removeEmployeeShouldFindAndRemoveEmployeeGivenIdEvenWhenStudentsCoexist)
{
    addAllPeopleToDataBase();
    auto size_before_removal = sut.size();

    bool has_removed = sut.removeEmployee(ok_employee_2.id());

    EXPECT_TRUE(has_removed);
    EXPECT_EQ(sut.size(), size_before_removal - 1ul);
}

TEST_F(UniversityDBTest, removeEmployeeShouldDoNothingIfThereIsNoEmployeeWithGivenId)
{
    addAllPeopleToDataBase();
    auto size_before_removal = sut.size();
    std::string non_existing_id { "Security:001" };

    bool has_removed = sut.removeEmployee(non_existing_id);

    ASSERT_NE(ok_employee_1.id(), non_existing_id);
    ASSERT_NE(ok_employee_2.id(), non_existing_id);
    EXPECT_FALSE(has_removed);
    EXPECT_EQ(sut.size(), size_before_removal);
}

TEST_F(UniversityDBTest, removeShouldFindAndRemovePeopleGivenPesel)
{
    addAllPeopleToDataBase();
    auto size_before_removal = sut.size();

    sut.remove(ok_employee_2.pesel());
    sut.remove(ok_student_2.pesel());

    EXPECT_EQ(sut.size(), size_before_removal - 2ul);
}

TEST_F(UniversityDBTest, removeShouldDoNothingIfThereIsNoPersonWithGivenPesel)
{
    addAllPeopleToDataBase();
    auto size_before_removal = sut.size();
    std::string non_existing_PESEL { "353253111" };

    sut.remove(non_existing_PESEL);

    EXPECT_EQ(sut.size(), size_before_removal);
}

TEST_F(UniversityDBTest, sortByLastNameShouldCorrectlyRearrangeDataBaseRecords)
{
    addAllPeopleToDataBase();
    sut.sortByLastName();
    auto sorted_people = sut.data();

    EXPECT_EQ(*sorted_people[0], ok_student_2);
    EXPECT_EQ(*sorted_people[1], ok_employee_1);
    EXPECT_EQ(*sorted_people[2], ok_student_4);
    EXPECT_EQ(*sorted_people[3], ok_student_1);
    EXPECT_EQ(*sorted_people[4], ok_employee_2);
    EXPECT_EQ(*sorted_people[5], ok_student_3);
}

TEST_F(UniversityDBTest, sortByPeselShouldCorrectlyRearangeDataBaseRecords)
{
    addAllPeopleToDataBase();
    sut.sortByPesel();
    auto sorted_people = sut.data();

    EXPECT_EQ(*sorted_people[0], ok_employee_2);
    EXPECT_EQ(*sorted_people[1], ok_student_4);
    EXPECT_EQ(*sorted_people[2], ok_student_1);
    EXPECT_EQ(*sorted_people[3], ok_student_2);
    EXPECT_EQ(*sorted_people[4], ok_student_3);
    EXPECT_EQ(*sorted_people[5], ok_employee_1);
}

TEST_F(UniversityDBTest, sortBySalaryShouldSortInDescedningOrder)
{
    Employee ok_employee_3 { "Dean: 001",
                             "Gregory",
                             "Hope",
                             ok_student_3.pesel(),
                             ok_student_3.address(),
                             Gender::male,
                             30000.0 };
    Employee ok_employee_4 { "Security: 002",
                             "John",
                             "Rambo",
                             ok_student_4.pesel(),
                             ok_student_4.address(),
                             Gender::female,
                             3800.0 };
    sut.add(ok_student_1);
    sut.add(ok_employee_2);
    sut.add(ok_student_2);
    sut.add(ok_employee_1);
    sut.add(ok_employee_4);
    sut.add(ok_employee_3);

    sut.sortBySalary();
    auto sorted_internal_container = sut.data();

    EXPECT_EQ(*sorted_internal_container[0], ok_employee_3);
    EXPECT_EQ(*sorted_internal_container[1], ok_employee_2);
    EXPECT_EQ(*sorted_internal_container[2], ok_employee_1);
    EXPECT_EQ(*sorted_internal_container[3], ok_employee_4);
    // checking last two elements
    auto student_ptr1 = std::dynamic_pointer_cast<Student>(sorted_internal_container[4]);
    auto student_ptr2 = std::dynamic_pointer_cast<Student>(sorted_internal_container[5]);
    EXPECT_NE(student_ptr1, nullptr);
    EXPECT_NE(student_ptr2, nullptr);
}

void addStudentToPattern(const Student& student, std::string& pattern)
{
    pattern += std::string("STUDENT\n")
        + "-------------\n"
        + "Index number: " + student.index() + "\n"
        + "First name: " + student.firstName() + "\n"
        + "Last name: " + student.lastName() + "\n"
        + "PESEL: " + student.pesel() + "\n"
        + "Address: " + student.address() + "\n"
        + "Gender: ";
    std::string gender = (student.gender() == Gender::male) ? "male"
                                                            : "female";
    pattern += gender + "\n"
        + "========================================\n";
}

void addEmployeeToPattern(const Employee& employee, std::string& pattern)
{
    pattern += std::string("EMPLOYEE\n")
        + "-------------\n"
        + "Employee ID: " + employee.id() + "\n"
        + "First name: " + employee.firstName() + "\n"
        + "Last name: " + employee.lastName() + "\n"
        + "PESEL: " + employee.pesel() + "\n"
        + "Address: " + employee.address() + "\n"
        + "Gender: ";
    std::string gender = (employee.gender() == Gender::male) ? "male"
                                                             : "female";
    pattern += gender + "\n"
        + "Salary: " + std::to_string(employee.salary()) + "\n"
        + "========================================\n";
}

TEST_F(UniversityDBTest, displayShouldCorrectlyInsertRecordToOuptutStream)
{
    addAllPeopleToDataBase();
    std::string pattern;
    addStudentToPattern(ok_student_1, pattern);
    addStudentToPattern(ok_student_2, pattern);
    addEmployeeToPattern(ok_employee_1, pattern);
    addStudentToPattern(ok_student_3, pattern);
    addEmployeeToPattern(ok_employee_2, pattern);
    addStudentToPattern(ok_student_4, pattern);

    // ostringstream used as substitution for std::cout and other streams
    std::ostringstream osstream;

    sut.display(osstream);
    std::string display_result = osstream.str();

    EXPECT_EQ(pattern, display_result);
}

TEST_F(UniversityDBTest, outputOperatorShouldCorrectlyInsertRecordToOuptutStream)
{
    addAllPeopleToDataBase();
    std::string pattern;
    addStudentToPattern(ok_student_1, pattern);
    addStudentToPattern(ok_student_2, pattern);
    addEmployeeToPattern(ok_employee_1, pattern);
    addStudentToPattern(ok_student_3, pattern);
    addEmployeeToPattern(ok_employee_2, pattern);
    addStudentToPattern(ok_student_4, pattern);

    // ostringstream used as substitution for std::cout and other streams
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
    databaseToCompare.add(ok_student_1);
    databaseToCompare.add(ok_student_2);
    databaseToCompare.add(ok_employee_1);
    databaseToCompare.add(ok_student_3);
    databaseToCompare.add(ok_employee_2);
    databaseToCompare.add(ok_student_4);

    int records_read = sut.readFromFile(path_to_template.data());
    auto internalStateToCompare = databaseToCompare.data();
    auto internalStateReadToSut = sut.data();

    EXPECT_EQ(records_read, 6);
    for (std::size_t i = 0; i < internalStateToCompare.size(); ++i) {
        EXPECT_EQ(*internalStateToCompare[i], *internalStateReadToSut[i]);
    }
}

TEST_F(UniversityDBTest, writeToFileShouldCorrectlyWriteDatabaseToFile)
{
    addAllPeopleToDataBase();
    std::string path_to_write = getPathToWritingTemplateFile();

    int records_written = sut.writeToFile(path_to_write.data());
    UniversityDB sut_to_compare;
    int records_read_back = sut_to_compare.readFromFile(path_to_write.data());

    EXPECT_EQ(records_written, 6);
    EXPECT_EQ(records_read_back, 6);
    for (std::size_t i = 0; i < sut.data().size(); ++i) {
        EXPECT_EQ(*sut.data()[i], *sut_to_compare.data()[i]);
    }
}

TEST_F(UniversityDBTest, sizeShouldReturnDataBaseSize)
{
    addAllPeopleToDataBase();

    EXPECT_EQ(sut.size(), 6);
}

TEST_F(UniversityDBTest, dataShouldReturnReferenceToInternalDataBaseContainer)
{
    addAllPeopleToDataBase();
    auto database_internal_container = sut.data();

    const std::type_info& type_to_compare = typeid(std::vector<UniversityDB::PersonShPtr>&);
    const std::type_info& returned_type = typeid(database_internal_container);

    EXPECT_EQ(type_to_compare, returned_type);
    EXPECT_EQ(database_internal_container.size(), 6);
}

TEST_F(UniversityDBTest, changeSalaryShouldFindCorrectEmployeeByPeselAndModifySalary)
{
    addAllPeopleToDataBase();
    double salary_before_change = ok_employee_2.salary();

    bool has_changed = sut.changeSalary(ok_employee_2.pesel(), 13000.0);
    auto person_ptr = sut.findByPesel(ok_employee_2.pesel());
    auto employee_ptr = std::dynamic_pointer_cast<Employee>(person_ptr);
    double salary_after_change = employee_ptr->salary();

    EXPECT_TRUE(has_changed);
    EXPECT_NE(salary_before_change, salary_after_change);
    EXPECT_EQ(salary_after_change, 13000.0);
}

TEST_F(UniversityDBTest, changeSalaryShouldNotModifyOtherRecordsThanRequested)
{
    addAllPeopleToDataBase();
    bool has_searched_changed = sut.changeSalary(ok_employee_2.pesel(), 13000.0);

    auto employee_1_ptr_after = std::dynamic_pointer_cast<Employee>(sut.findByPesel(ok_employee_1.pesel()));
    auto employee_2_ptr_after = std::dynamic_pointer_cast<Employee>(sut.findByPesel(ok_employee_2.pesel()));

    ASSERT_TRUE(has_searched_changed);
    EXPECT_NE(ok_employee_2.salary(), employee_2_ptr_after->salary());
    EXPECT_EQ(ok_employee_1.salary(), employee_1_ptr_after->salary());
}

TEST_F(UniversityDBTest, changeSalaryShouldNotModifySalaryIfNegativeSalaryPassed)
{
    addAllPeopleToDataBase();
    double salary_before_change = ok_employee_2.salary();

    bool has_changed = sut.changeSalary(ok_employee_2.pesel(), -1000.0);
    auto person_ptr = sut.findByPesel(ok_employee_2.pesel());
    auto employee_ptr = std::dynamic_pointer_cast<Employee>(person_ptr);
    double salary_after_change = employee_ptr->salary();

    EXPECT_FALSE(has_changed);
    EXPECT_EQ(salary_before_change, salary_after_change);
}

}   // end of namespace university::mt
