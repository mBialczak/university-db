#include "DBfileManager/DBfileManager.hpp"
#include "Employee/Employee.hpp"
#include "Student/Student.hpp"
#include "UniversityDB/UniversityDB.hpp"

#include "gtest/gtest.h"
#include <filesystem>

namespace university::ut {

namespace {
    using employee::Employee;
    using person::Gender;
    using student::IndexNo;
    using student::Student;
    using namespace testing;
}   // anonymous namespace

class DBFileManagerTest : public Test
{
  public:
    DBFileManagerTest();

  protected:
    UniversityDB data_base_;
    DBfileManager sut_;

    Student student_1;
    Student student_2;
    Student student_3;
    Student student_4;
    Employee employee_1;
    Employee employee_2;
};

DBFileManagerTest::DBFileManagerTest()
    : sut_(data_base_)
    , student_1({ "001/2020",
                  "Sally",
                  "Smith",
                  "81100216357",
                  "Poland, Opole, ul. Deszczowa 23/m.22",
                  Gender::female })
    , student_2({ "003/2019",
                  "Joseph",
                  "Kowalski",
                  "90080517455",
                  "Poland, Laskowice, ul. Niedzielna 304A",
                  Gender::male })
    , student_3({ "023/2020",
                  "Anna",
                  "Zielinska",
                  "90090515836",
                  "Poland, Opole, ul. Sobotnia 15A",
                  Gender::female })
    , student_4({ "012/2018",
                  "Peter",
                  "Pikiel",
                  "67040500538",
                  "Poland, Zabrze, ul. Nieznana 1C/44",
                  Gender::male })
    , employee_1("Teacher:001",
                 "Miroslaw",
                 "Kowalski",
                 "92071314764",
                 "Poland, Lublin, ul. Cwaniaka 4D/28",
                 Gender::male,
                 6500.50)
    , employee_2("Management:003",
                 "Sandra",
                 "Smith",
                 "65071209862",
                 "Poland, Szczecin, ul. Zachodnia 33/83",
                 Gender::female,
                 10000.40)
{ }

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
    path_to_template += "test-resources/File-writing-result-DBfileManager-test.txt";

    return path_to_template;
}

TEST_F(DBFileManagerTest, readFileShouldCorrectlyReadDBfromFile)
{
    std::string path_to_template = getPathToReadingTemplateFile();
    // prepare second database for comparison
    UniversityDB databaseToCompare;
    databaseToCompare.add(student_1);
    databaseToCompare.add(student_2);
    databaseToCompare.add(employee_1);
    databaseToCompare.add(student_3);
    databaseToCompare.add(employee_2);
    databaseToCompare.add(student_4);

    int records_read = sut_.readFile(path_to_template.data());
    auto internalStateToCompare = databaseToCompare.data();
    auto internalStateOfAssociatedDataBase = data_base_.data();

    EXPECT_EQ(records_read, 6);
    for (std::size_t i = 0; i < internalStateToCompare.size(); ++i) {
        EXPECT_EQ(*internalStateToCompare[i], *internalStateOfAssociatedDataBase[i]);
    }
}

TEST_F(DBFileManagerTest, writeToFileShouldCorrectlyWriteDBtoFile)
{
    data_base_.add(student_1);
    data_base_.add(student_2);
    data_base_.add(employee_1);
    data_base_.add(student_3);
    data_base_.add(employee_2);
    data_base_.add(student_4);
    std::string path_to_write = getPathToWritingTemplateFile();

    int records_written = sut_.writeToFile(path_to_write.data());
    UniversityDB databaseToCompare;
    int records_read_back = databaseToCompare.readFromFile(path_to_write.data());

    EXPECT_EQ(records_written, 6);
    EXPECT_EQ(records_read_back, 6);
    for (std::size_t i = 0; i < data_base_.data().size(); ++i) {
        EXPECT_EQ(*data_base_.data()[i], *databaseToCompare.data()[i]);
    }
}

}   // namespace university::ut
