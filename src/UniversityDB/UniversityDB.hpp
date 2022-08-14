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

namespace person {
    class Person;
}
namespace employee {
    class Employee;
}

class UniversityDB
{
  public:
    using PersonShPtr = std::shared_ptr<person::Person>;
    using PersonIter = std::vector<PersonShPtr>::iterator;
    using ContainerType = std::vector<PersonShPtr>;

    UniversityDB();

    bool add(const student::Student& student);
    bool add(const employee::Employee& employee);
    bool add(student::Student&& student);
    bool add(employee::Employee&& employee);
    bool removeStudent(const std::string& index);
    bool removeEmployee(const std::string& id);
    void remove(const std::string& pesel);
    void sortByLastName();
    void sortByPesel();
    int readFromFile(const char* fileName);
    int writeToFile(const char* fileName) const;
    ContainerType& data();
    UniversityDB::PersonShPtr findByPesel(const std::string& pesel) const;
    std::vector<PersonShPtr> findByLastName(const std::string& lastName) const;
    bool changeSalary(const std::string& pesel, double newSalary);
    void display(std::ostream& stream = std::cout) const;
    std::size_t size() const;

  private:
    PersonIter findByIndex(const std::string& index);
    PersonIter findById(const std::string& id);
    bool canBeAdded(const student::Student& student);
    bool canBeAdded(const employee::Employee& employee);
    std::unique_ptr<DBfileManager> file_manager_;
    pesel_validator::PeselValidator pesel_validator_;
    ContainerType records_;
};   // class UniversityDB

std::ostream& operator<<(std::ostream& os, const UniversityDB& database);
}   // namespace university
