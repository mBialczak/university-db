#pragma once

#include "PeselValidator/PeselValidator.hpp"
#include "StudentRecord/StudentRecord.hpp"

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace university {

class UniversityDB
{
    using StudentIterator = std::vector<student_record::StudentRecord>::iterator;

  public:
    bool addStudent(const student_record::StudentRecord& record);
    bool addStudent(student_record::StudentRecord&& record);
    bool addStudent(student_record::IndexNo index,
                    const std::string& firstName,
                    const std::string& lastName,
                    const std::string& pesel,
                    const std::string& address,
                    const student_record::Gender gender);

    bool removeStudent(student_record::IndexNo indexNo);

    void sortByLastName();
    void sortByPesel();

    bool readFromFile(const char* fileName);

    const std::vector<student_record::StudentRecord>& data() const;

    std::shared_ptr<const student_record::StudentRecord> findByPesel(const std::string& pesel) const;
    std::vector<student_record::StudentRecord> findByLastName(const std::string& lastName) const;

    void Display(std::ostream& stream = std::cout) const;

    std::size_t size() const;

  private:
    // TODO: remove unnesecery?
    // std::string parseRecordFromFile(const std::ifstream& stream) const;
    // bool readHeaderLines(const std::ifstream& stream, int lines) const;
    // std::string readRecordPart(const std::string& fullText, const std::string& searched) const;
    // std::string readLastName(const std::string& text) const;
    // bool tryMakeRecord(const std::map<std::string, std::string>& parts);

    StudentIterator findByIndex(student_record::IndexNo index);
    pesel_validator::PeselValidator pesel_validator_;
    std::vector<student_record::StudentRecord> students_;
};   // namespace UniversityDB

std::ostream& operator<<(std::ostream& os, const UniversityDB& database);
}   // namespace university
