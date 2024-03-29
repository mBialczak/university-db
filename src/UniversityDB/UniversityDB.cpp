#include "UniversityDB.hpp"

#include "Employee/Employee.hpp"
#include "Student/Student.hpp"

#include <algorithm>
#include <fstream>
#include <regex>
#include <sstream>

namespace university {

namespace {
    using employee::Employee;
    using person::Person;
    using student::Student;
    using PersonShPtr = UniversityDB::PersonShPtr;
}   // namespace

UniversityDB::UniversityDB()
    : file_manager_(std::make_unique<DBfileManager>(*this))
{ }

bool UniversityDB::add(const Student& student)
{
    if (canBeAdded(student)) {
        records_.emplace_back(std::make_shared<Student>(student));
        return true;
    }

    return false;
}

bool UniversityDB::add(const Employee& employee)
{
    if (canBeAdded(employee)) {
        records_.emplace_back(std::make_shared<Employee>(employee));
        return true;
    }

    return false;
}

bool UniversityDB::add(Student&& student)
{
    if (canBeAdded(student)) {
        records_.emplace_back(std::make_shared<Student>(std::move(student)));
        return true;
    }

    return false;
}

bool UniversityDB::add(Employee&& employee)
{
    if (canBeAdded(employee)) {
        records_.emplace_back(std::make_shared<Employee>(std::move(employee)));
        return true;
    }

    return false;
}

std::size_t UniversityDB::size() const
{
    return records_.size();
}

PersonShPtr UniversityDB::findByPesel(const std::string& pesel) const
{
    auto result_iter = std::find_if(records_.begin(),
                                    records_.end(),
                                    [&pesel](const auto& record) {
                                        return record->pesel() == pesel;
                                    });

    if (result_iter != records_.end()) {
        return *result_iter;
    }

    return nullptr;
}

std::vector<PersonShPtr> UniversityDB::findByLastName(const std::string& lastName) const

{
    std::vector<PersonShPtr> found_persons;
    std::copy_if(records_.begin(),
                 records_.end(),
                 std::back_inserter(found_persons),
                 [&lastName](const auto& record) {
                     return record->lastName() == lastName;
                 });

    return found_persons;
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

bool UniversityDB::removeEmployee(const std::string& id)
{
    auto to_be_removed = findById(id);
    if (to_be_removed != records_.end()) {
        records_.erase(to_be_removed);
        return true;
    }

    return false;
}

void UniversityDB::remove(const std::string& pesel)
{
    auto removal_start = std::remove_if(records_.begin(),
                                        records_.end(),
                                        [&pesel](const auto& personPtr) {
                                            return personPtr->pesel() == pesel;
                                        });

    records_.erase(removal_start, records_.end());
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

UniversityDB::PersonIter UniversityDB::findById(const std::string& id)
{
    return std::find_if(records_.begin(),
                        records_.end(),
                        [&id](const auto& record) {
                            auto maybe_employee_ptr = std::dynamic_pointer_cast<Employee>(record);
                            if (maybe_employee_ptr) {
                                return maybe_employee_ptr->id() == id;
                            }

                            return false;
                        });
}

bool UniversityDB::canBeAdded(const student::Student& student)
{
    return (!findByPesel(student.pesel())
            && findByIndex(student.index()) == records_.end()
            && pesel_validator_(student.pesel()));
}
bool UniversityDB::canBeAdded(const employee::Employee& employee)
{
    return (!findByPesel(employee.pesel())
            && findById(employee.id()) == records_.end()
            && pesel_validator_(employee.pesel()));
}

void UniversityDB::sortByLastName()
{
    std::sort(records_.begin(),
              records_.end(),
              [](const auto& lhs, const auto& rhs) {
                  return *lhs < *rhs;
              });
}

UniversityDB::ContainerType& UniversityDB::data()
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

// sorts records by salary in descending order
void UniversityDB::sortBySalary()
{
    std::sort(records_.begin(),
              records_.end(),
              [](const auto& lhs, const auto& rhs) {
                  auto lhs_ptr = std::dynamic_pointer_cast<Employee>(lhs);
                  auto rhs_ptr = std::dynamic_pointer_cast<Employee>(rhs);
                  // both are employees
                  if (lhs_ptr && rhs_ptr) {
                      return lhs_ptr->salary() > rhs_ptr->salary();
                  }
                  // not employee vs. employee
                  else if (!lhs_ptr && rhs_ptr) {
                      return false;
                  }
                  // employee vs. not employee
                  else if (lhs_ptr && !rhs_ptr) {
                      return true;
                  }
                  // both not employees order doesn't matter
                  else {
                      return false;
                  }
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

bool UniversityDB::changeSalary(const std::string& pesel, double newSalary)
{
    auto person_ptr = findByPesel(pesel);
    if (!person_ptr || newSalary <= 0) {
        return false;
    }

    auto employee_ptr = std::dynamic_pointer_cast<Employee>(person_ptr);
    if (employee_ptr) {
        employee_ptr->setSalary(newSalary);
        return true;
    }

    return false;
}

void UniversityDB::display(std::ostream& stream) const
{
    for (const auto& record : records_) {
        stream << *record
               << "========================================\n";
    }
}

std::ostream& operator<<(std::ostream& os, const UniversityDB& database)
{
    database.display(os);

    return os;
}

}   // namespace university
