#include "UniversityDB.hpp"

#include <algorithm>
#include <fstream>
#include <regex>
#include <sstream>

namespace university {

namespace {
    using person::Person;
    using student::Student;
    using PersonShPtr = UniversityDB::PersonShPtr;
}   // namespace

UniversityDB::UniversityDB()
    : file_manager_(std::make_unique<DBfileManager>(*this))
{ }

bool UniversityDB::addStudent(const std::string& index,
                              const std::string& firstName,
                              const std::string& lastName,
                              const std::string& pesel,
                              const std::string& address,
                              const person::Gender gender)
{
    if (pesel_validator_(pesel)) {
        // Student student { index, TODO:: REMOVE
        //                            firstName,
        //                            lastName,
        //                            pesel,
        //                            address,
        //                            gender };
        // records_.emplace_back(student);
        records_.emplace_back(std::make_shared<Student>(index,
                                                        firstName,
                                                        lastName,
                                                        pesel,
                                                        address,
                                                        gender));
        return true;
    }

    return false;
}

bool UniversityDB::addStudent(const Student& student)
{
    if (pesel_validator_(student.pesel())) {
        records_.emplace_back(std::make_shared<Student>(student.index(),
                                                        student.firstName(),
                                                        student.lastName(),
                                                        student.pesel(),
                                                        student.address(),
                                                        student.gender()));
        // records_.emplace_back(student); TODO: REMOVE
        return true;
    }

    return false;
}

bool UniversityDB::addStudent(Student&& student)
{
    if (pesel_validator_(student.pesel())) {
        // records_.emplace_back(std::move(record));
        records_.emplace_back(std::make_shared<Student>(std::move(student)));
        return true;
    }

    return false;
}

std::size_t UniversityDB::size() const
{
    return records_.size();
}
// TODO: remove
// std::shared_ptr<const Student> UniversityDB::findByPesel(const std::string& pesel) const
// UniversityDB manages the life of its records
PersonShPtr UniversityDB::findByPesel(const std::string& pesel) const

{
    auto result_iter = std::find_if(records_.begin(),
                                    records_.end(),
                                    [&pesel](const auto& record) {
                                        return record->pesel() == pesel;
                                    });
    if (result_iter != records_.end()) {
        // return std::make_shared<const Student>(*result_iter); //TODO: remove
        return *result_iter;
    }

    return nullptr;
}
// TODO: remove
// std::vector<Student> UniversityDB::findByLastName(const std::string& lastName) const
std::vector<PersonShPtr> UniversityDB::findByLastName(const std::string& lastName) const

{
    // std::vector<Student> found_students; //TODO
    std::vector<PersonShPtr> found_students;
    std::copy_if(records_.begin(),
                 records_.end(),
                 std::back_inserter(found_students),
                 [&lastName](const auto& record) {
                     return record->lastName() == lastName;
                 });

    return found_students;
}

bool UniversityDB::removeStudent(const std::string& index)
{
    auto to_be_removed = findByIndex(index);
    if (to_be_removed != records_.end()) {
        records_.erase(to_be_removed);
        return true;
    }

    return false;
}

UniversityDB::PersonIter UniversityDB::findByIndex(const std::string& index)
{
    return std::find_if(records_.begin(),
                        records_.end(),
                        [&index](const auto& record) {
                            auto maybe_student_ptr = std::dynamic_pointer_cast<Student>(record);
                            if (maybe_student_ptr) {
                                return maybe_student_ptr->index() == index;
                            }

                            return false;
                        });
}

void UniversityDB::sortByLastName()
{
    std::sort(records_.begin(),
              records_.end(),
              [](const auto& lhs, const auto& rhs) {
                  return lhs->lastName() < rhs->lastName();
              });
}

std::vector<PersonShPtr>& UniversityDB::data()
{
    return records_;
}

void UniversityDB::sortByPesel()
{
    std::sort(records_.begin(),
              records_.end(),
              [](const auto& lhs, const auto& rhs) {
                  return lhs->pesel() < rhs->pesel();
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
    for (const auto& student : records_) {
        stream << *student
               << "========================================\n";
    }
}
// TODO: remove
// bool UniversityDB::isStudent(const PersonShPtr& personPtr) const
// {
//     using Student;
//     std::shared_ptr<Student> maybe_student_ptr = std::dynamic_pointer_cast<Student>;
// }

std::ostream& operator<<(std::ostream& os, const UniversityDB& database)
{
    database.Display(os);

    return os;
}

}   // namespace university
