#include "DBfileManager/DBfileManager.hpp"
#include "StudentRecord/StudentRecord.hpp"
#include "UniversityDB/UniversityDB.hpp"

#include "gtest/gtest.h"
#include <filesystem>

namespace university::ut {

namespace {
    using student_record::Gender;
    using student_record::IndexNo;
    using student_record::StudentRecord;
    using namespace testing;
}   // anonymous namespace

class DBFileManagerTest : public Test
{
  public:
    DBFileManagerTest();

  protected:
    UniversityDB data_base_;
    DBfileManager sut_;

    StudentRecord student_1_;
    StudentRecord student_2_;
    StudentRecord student_3_;
    StudentRecord student_4_;
};

DBFileManagerTest::DBFileManagerTest()
    : sut_(data_base_)
    , student_1_({ IndexNo(133ul),
                   "Sally",
                   "Smith",
                   "81100216357",
                   "Poland, Opole, ul. Deszczowa 23/m.22",
                   Gender::female })
    , student_2_({ IndexNo { 173ul },
                   "Joseph",
                   "Kowalski",
                   "90080517455",
                   "Poland, Laskowice, ul. Niedzielna 304A",
                   Gender::male })
    , student_3_({ IndexNo { 333ul },
                   "Anna",
                   "Zielinska",
                   "90090515836",
                   "Poland, Opole, ul. Sobotnia 15A",
                   Gender::female })
    , student_4_({ IndexNo { 144ul },
                   "Peter",
                   "Pikiel",
                   "67040500538",
                   "Poland, Zabrze, ul. Nieznana 1C/44",
                   Gender::male })
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
    path_to_template += "test-resources/File-writing-template.txt";

    return path_to_template;
}

TEST_F(DBFileManagerTest, readFileShouldCorrectlyReadDBfromFile)
{
    std::string path_to_template = getPathToReadingTemplateFile();
    // prepare second database for comparison
    UniversityDB databaseToCompare;
    databaseToCompare.addStudent(student_1_);
    databaseToCompare.addStudent(student_2_);
    databaseToCompare.addStudent(student_3_);
    databaseToCompare.addStudent(student_4_);

    int records_read = sut_.readFile(path_to_template.data());
    auto internalStateToCompare = databaseToCompare.data();
    auto internalStateOfAssociatedDataBase = data_base_.data();

    EXPECT_EQ(records_read, 4);
    EXPECT_EQ(internalStateToCompare, internalStateOfAssociatedDataBase);
}

TEST_F(DBFileManagerTest, writeToFileShouldCorrectlyWriteDBtoFile)
{
    data_base_.addStudent(student_1_);
    data_base_.addStudent(student_2_);
    data_base_.addStudent(student_3_);
    data_base_.addStudent(student_4_);
    std::string path_to_write = getPathToWritingTemplateFile();

    int records_written = sut_.writeToFile(path_to_write.data());
    UniversityDB databaseToCompare;
    int records_read_back = databaseToCompare.readFromFile(path_to_write.data());

    EXPECT_EQ(records_written, 4);
    EXPECT_EQ(records_read_back, 4);
    EXPECT_EQ(data_base_.data(), databaseToCompare.data());
}

}   // namespace university::ut
