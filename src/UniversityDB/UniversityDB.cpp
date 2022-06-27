#include "UniversityDB.hpp"

#include <algorithm>
#include <fstream>
// TODO: remove INU
#include <map>
#include <regex>
#include <sstream>

namespace university {

const char* fileToread = "../test-resources/File-reading-template.txt";

bool UniversityDB::addStudent(student_record::IndexNo index,
                              const std::string& firstName,
                              const std::string& lastName,
                              const std::string& pesel,
                              const std::string& address,
                              const student_record::Gender gender)
{
    if (pesel_validator_(pesel)) {
        student_record::StudentRecord added { index,
                                              firstName,
                                              lastName,
                                              pesel,
                                              address,
                                              gender };
        students_.emplace_back(added);
        return true;
    }

    return false;
}

bool UniversityDB::addStudent(const student_record::StudentRecord& record)
{
    if (pesel_validator_(record.pesel())) {
        students_.emplace_back(record);
        return true;
    }

    return false;
}

bool UniversityDB::addStudent(student_record::StudentRecord&& record)
{
    if (pesel_validator_(record.pesel())) {
        students_.emplace_back(std::move(record));
        return true;
    }

    return false;
}

std::size_t UniversityDB::size() const
{
    return students_.size();
}

std::shared_ptr<const student_record::StudentRecord> UniversityDB::findByPesel(const std::string& pesel) const
{
    auto result_iter = std::find_if(students_.begin(),
                                    students_.end(),
                                    [&pesel](const auto& record) {
                                        return record.pesel() == pesel;
                                    });
    if (result_iter != students_.end()) {
        return std::make_shared<const student_record::StudentRecord>(*result_iter);
    }

    return nullptr;
}

std::vector<student_record::StudentRecord> UniversityDB::findByLastName(const std::string& lastName) const
{
    std::vector<student_record::StudentRecord> found_students;
    std::copy_if(students_.begin(),
                 students_.end(),
                 std::back_inserter(found_students),
                 [&lastName](const auto& record) {
                     return record.lastName() == lastName;
                 });

    return found_students;
}

bool UniversityDB::removeStudent(student_record::IndexNo index)
{
    auto to_be_removed = findByIndex(index);
    if (to_be_removed != students_.end()) {
        students_.erase(to_be_removed);
        return true;
    }

    return false;
}

UniversityDB::StudentIterator UniversityDB::findByIndex(student_record::IndexNo index)
{
    return std::find_if(students_.begin(),
                        students_.end(),
                        [&index](const auto& record) {
                            return record.index() == index;
                        });
}

void UniversityDB::sortByLastName()
{
    std::sort(students_.begin(),
              students_.end(),
              [](const auto& lhs, const auto& rhs) {
                  return lhs.lastName() < rhs.lastName();
              });
}

const std::vector<student_record::StudentRecord>& UniversityDB::data() const
{
    return students_;
}

void UniversityDB::sortByPesel()
{
    std::sort(students_.begin(),
              students_.end(),
              [](const auto& lhs, const auto& rhs) {
                  return lhs.pesel() < rhs.pesel();
              });
}

bool UniversityDB::readFromFile(const char* fileNameh)
{
    std::ifstream stream(fileToread);
    std::string raw_record_text;
    while (stream) {
        raw_record_text = parseRecordFromFile(stream);
        std::map<std::string, std::string> record_parts;
        record_parts["first_name"] = readRecordPart(raw_record_text, "First name:");
        record_parts["last_name"] = readRecordPart(raw_record_text, "Last name:");
        record_parts["pesel"] = readRecordPart(raw_record_text, "PESEL:");
        record_parts["address"] = readRecordPart(raw_record_text, "Address:");
        record_parts["gender"] = readRecordPart(raw_record_text, "Gender:");
    }
}

std::string UniversityDB::readRecordPart(const std::string& fullText, const std::string& searched) const
{
    std::regex to_find { searched };
    std::istringstream stream { text };
    std::string line;
    // find line with first name
    while (getline(stream, line) && !std::regex_match(line, exp)) {
    }
    auto pos = line.find(": ");

    return line.substr(pos);
}

std::string UniversityDB::readLastName(const std::string& text) const
{
    std::regex searched { "Last name:" };
    std::istringstream stream { text };
    std::string line;
    // find line with first name
    while (getline(stream, line) && !std::regex_match(line, exp)) {
    }
    auto pos = line.find(": ");

    return line.substr(pos);
}

std::string parseRecordFromFile(const std::ifstream& stream) const
{
    std::string line;
    std::string record_text;
    std::regex end_line { "*=====*" };
    while (getline(stream, line) && !std::regex_match(line, exp)) {
        record_text += line + "\n";
    }

    return record_text;
}

// TODO: remove if not use
bool UniversityDB::readHeaderLines(const std::ifstream& stream, int lines)
{
    bool result { true };
    if (stream) {
    }

    while (lines >= 0 & stream) {
        getline(stream);
    }
}

bool UniversityDB::tryMakeRecord(const std::map<std::string, std::string>& parts)
{
    // we don't want a record if any of field would be incomplete
    for (const auto [key, value] : parts) {
        if (value == "") {
            return false;
        }
    }

    return addStudent(, parts["first_name"])

               r = readRecordPart(raw_record_text, "First name:");
    record_parts["last_name"] = readRecordPart(raw_record_text, "Last name:");
    record_parts["pesel"] = readRecordPart(raw_record_text, "PESEL:");
    record_parts["address"] = readRecordPart(raw_record_text, "Address:");
    record_parts["gender"] = readRecordPart(raw_record_text, "Gender:");
}

void UniversityDB::Display(std::ostream& stream) const
{
    std::size_t counter = 1;
    for (const auto& student : students_) {
        stream << "Student record "
               << std::to_string(counter) + "\n"
               << " ------------------\n"
               << student
               << "========================================\n";
        ++counter;
    }
}

std::ostream& operator<<(std::ostream& os, const UniversityDB& database)
{
    database.Display(os);

    return os;
}
}   // namespace university
