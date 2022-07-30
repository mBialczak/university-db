#include "UniversityDB.hpp"

#include <algorithm>
#include <fstream>
#include <regex>
#include <sstream>

namespace university {

UniversityDB::UniversityDB()
    : file_manager_(std::make_unique<DBfileManager>(*this))
{ }

bool UniversityDB::addStudent(student::IndexNo index,
                              const std::string& firstName,
                              const std::string& lastName,
                              const std::string& pesel,
                              const std::string& address,
                              const person::Gender gender)
{
    if (pesel_validator_(pesel)) {
        student::Student student { index,
                                   firstName,
                                   lastName,
                                   pesel,
                                   address,
                                   gender };
        students_.emplace_back(student);
        return true;
    }

    return false;
}

bool UniversityDB::addStudent(const student::Student& record)
{
    if (pesel_validator_(record.pesel())) {
        students_.emplace_back(record);
        return true;
    }

    return false;
}

bool UniversityDB::addStudent(student::Student&& record)
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

std::shared_ptr<const student::Student> UniversityDB::findByPesel(const std::string& pesel) const
{
    auto result_iter = std::find_if(students_.begin(),
                                    students_.end(),
                                    [&pesel](const auto& record) {
                                        return record.pesel() == pesel;
                                    });
    if (result_iter != students_.end()) {
        return std::make_shared<const student::Student>(*result_iter);
    }

    return nullptr;
}

std::vector<student::Student> UniversityDB::findByLastName(const std::string& lastName) const
{
    std::vector<student::Student> found_students;
    std::copy_if(students_.begin(),
                 students_.end(),
                 std::back_inserter(found_students),
                 [&lastName](const auto& record) {
                     return record.lastName() == lastName;
                 });

    return found_students;
}

bool UniversityDB::removeStudent(student::IndexNo index)
{
    auto to_be_removed = findByIndex(index);
    if (to_be_removed != students_.end()) {
        students_.erase(to_be_removed);
        return true;
    }

    return false;
}

UniversityDB::StudentIterator UniversityDB::findByIndex(student::IndexNo index)
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

std::vector<student::Student>& UniversityDB::data()
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

int UniversityDB::writeToFile(const char* fileName) const
{
    return file_manager_->writeToFile(fileName);
}

int UniversityDB::readFromFile(const char* fileName)
{
    return file_manager_->readFile(fileName);
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
