#pragma once

#include "DBfileManager/DBfileManager.hpp"
#include "PeselValidator/PeselValidator.hpp"
#include "StudentRecord/StudentRecord.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <vector>

namespace university {

class DBfileManager;

class UniversityDB
{
    using StudentIterator = std::vector<student::StudentRecord>::iterator;

  public:
    UniversityDB();

    bool addStudent(const student::StudentRecord& record);
    bool addStudent(student::StudentRecord&& record);
    bool addStudent(student::IndexNo index,
                    const std::string& firstName,
                    const std::string& lastName,
                    const std::string& pesel,
                    const std::string& address,
                    const student::Gender gender);
    bool removeStudent(student::IndexNo indexNo);
    void sortByLastName();
    void sortByPesel();
    int readFromFile(const char* fileName);
    int writeToFile(const char* fileName) const;
    std::vector<student::StudentRecord>& data();
    std::shared_ptr<const student::StudentRecord> findByPesel(const std::string& pesel) const;
    std::vector<student::StudentRecord> findByLastName(const std::string& lastName) const;
    void Display(std::ostream& stream = std::cout) const;
    std::size_t size() const;

  private:
    StudentIterator findByIndex(student::IndexNo index);

    std::unique_ptr<DBfileManager> file_manager_;
    pesel_validator::PeselValidator pesel_validator_;
    std::vector<student::StudentRecord> students_;
};   // namespace UniversityDB

std::ostream& operator<<(std::ostream& os, const UniversityDB& database);
}   // namespace university
