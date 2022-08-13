#pragma once

#include "DBfileManager/DBfileManager.hpp"
#include "PeselValidator/PeselValidator.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <vector>

namespace university {

namespace student {
    class Student;
}

namespace employee {
    class Employee;
}

class DBfileManager;

class UniversityDB
{
  public:
    using PersonShPtr = std::shared_ptr<person::Person>;
    using PersonIter = std::vector<PersonShPtr>::iterator;

    UniversityDB();

    bool add(const student::Student& student);   // TODO: REMOVE DONE
    bool add(const employee::Employee& employee);   // TODO: REMOVE DONE
    bool add(student::Student&& student);   // TODO: REMOVE DONE
    bool add(employee::Employee&& employee);   // TODO: REMOVE DONE
    bool removeStudent(const std::string& index);   // TODO: REMOVE DONE
    bool removeEmployee(const std::string& id);   // TODO: REMOVE DONE
    void remove(const std::string& pesel);   // TODO: REMOVE DONE
    void sortByLastName();   // TODO: DONE
    void sortByPesel();   // TODO: DONE
    int readFromFile(const char* fileName);
    int writeToFile(const char* fileName) const;
    std::vector<PersonShPtr>& data();   // TODO: DONE
    UniversityDB::PersonShPtr findByPesel(const std::string& pesel) const;   // TODO: DONE
    std::vector<PersonShPtr> findByLastName(const std::string& lastName) const;   // TODO: DONE
    void Display(std::ostream& stream = std::cout) const;
    std::size_t size() const;

  private:
    // TODO: consider making public and returning shared_ptr as additional functionality
    PersonIter findByIndex(const std::string& index);
    PersonIter findById(const std::string& id);
    bool canBeAdded(const student::Student& student);
    bool canBeAdded(const employee::Employee& employee);
    std::unique_ptr<DBfileManager> file_manager_;
    pesel_validator::PeselValidator pesel_validator_;
    std::vector<PersonShPtr> records_;
};   // namespace UniversityDB

std::ostream& operator<<(std::ostream& os, const UniversityDB& database);
}   // namespace university
