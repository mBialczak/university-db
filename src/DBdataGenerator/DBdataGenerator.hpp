#pragma once

#include "PeselValidator/PeselValidator.hpp"

#include <random>
#include <vector>

namespace university {

class UniversityDB;

namespace student {
    class Student;
}

namespace person {
    class Person;
    enum class Gender;
}   // namespace person

namespace employee {
    class Employee;
}

namespace pesel_validator {
    class PeselValidator;
}

namespace data_generator {
    class DBdataGenerator
    {
      public:
        DBdataGenerator(UniversityDB& dataBaseToFill);

        void addStudents(unsigned numberOfStudents) const;
        void addEmployees(unsigned numberOfEmployees) const;

      private:
        student::Student generateStudent() const;
        employee::Employee generateEmployee() const;
        std::string generateIndex() const;
        std::string generateId() const;
        university::person::Gender generateGender() const;
        std::string generateFirstName(university::person::Gender gender) const;
        std::string generateLastName() const;
        std::string generatePesel() const;
        std::string generateAddress() const;
        double generateSalary() const;
        std::string generateDayForMonth(long unsigned month) const;
        void addZerosIfTooShort(std::string& digitString, unsigned requestedLength = 2) const;
        std::string generateControlDigit(const std::string& tenFirstDigits) const;
        long unsigned randomInt(long unsigned from, long unsigned to) const;
        double randomDouble(double from, double to) const;

        const static std::vector<std::string> femaleFirstNames;
        const static std::vector<std::string> maleFirstNames;
        const static std::vector<std::string> lastNames;
        const static std::vector<std::string> cities;
        const static std::vector<std::string> streets;
        const static std::vector<std::string> departments;
        UniversityDB& database_;
        mutable std::mt19937_64 generator_;
        pesel_validator::PeselValidator pesel_validator_;
    };

}   // namespace data_generator
}   // namespace university
