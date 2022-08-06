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
  public:
    using PersonShPtr = std::shared_ptr<person::Person>;
    using PersonIter = std::vector<PersonShPtr>::iterator;

    UniversityDB();

    bool addStudent(const student::Student& student);
    bool addStudent(student::Student&& student);
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
    std::vector<PersonShPtr>& data();
    UniversityDB::PersonShPtr findByPesel(const std::string& pesel) const;
    std::vector<PersonShPtr> findByLastName(const std::string& lastName) const;
    void Display(std::ostream& stream = std::cout) const;
    std::size_t size() const;

  private:
    PersonIter findByIndex(const std::string& index);
    std::unique_ptr<DBfileManager> file_manager_;
    pesel_validator::PeselValidator pesel_validator_;
    std::vector<PersonShPtr> records_;
};   // namespace UniversityDB

std::ostream& operator<<(std::ostream& os, const UniversityDB& database);
}   // namespace university
