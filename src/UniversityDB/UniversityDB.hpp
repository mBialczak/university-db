#pragma once

#include "DBfileManager/DBfileManager.hpp"
#include "PeselValidator/PeselValidator.hpp"
#include "Student/Student.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <vector>

namespace university {

class DBfileManager;

class UniversityDB
{
    using StudentIterator = std::vector<student::Student>::iterator;

  public:
    UniversityDB();

    bool addStudent(const student::Student& record);
    bool addStudent(student::Student&& record);
    bool addStudent(const std::string& index,
                    const std::string& firstName,
                    const std::string& lastName,
                    const std::string& pesel,
                    const std::string& address,
                    const person::Gender gender);
    bool removeStudent(const std::string& index);
    void sortByLastName();
    void sortByPesel();
    int readFromFile(const char* fileName);
    int writeToFile(const char* fileName) const;
    std::vector<student::Student>& data();
    std::shared_ptr<const student::Student> findByPesel(const std::string& pesel) const;
    std::vector<student::Student> findByLastName(const std::string& lastName) const;
    void Display(std::ostream& stream = std::cout) const;
    std::size_t size() const;

  private:
    StudentIterator findByIndex(const std::string& index);

    std::unique_ptr<DBfileManager> file_manager_;
    pesel_validator::PeselValidator pesel_validator_;
    std::vector<student::Student> students_;
};   // namespace UniversityDB

std::ostream& operator<<(std::ostream& os, const UniversityDB& database);
}   // namespace university
