#pragma once

#include "PeselValidator/PeselValidator.hpp"

// TODO: VERIFY all headers
#include <memory>
#include <random>
#include <vector>

namespace university {

class UniversityDB;

namespace student {
    class Student;
}
// TODO: VERIFY
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

      private:
        long unsigned randomNumber(long unsigned from, long unsigned to) const;
        student::Student generateStudent() const;
        std::string generateIndex() const;
        university::person::Gender generateGender() const;
        std::string generateFirstName(university::person::Gender gender) const;
        std::string generateLastName() const;
        std::string generatePesel() const;
        std::string generateAddress() const;
        std::string generateDayForMonth(long unsigned month) const;
        void addZerosIfTooShort(std::string& digitString, unsigned requestedLength = 2) const;
        std::string generateControlDigit(const std::string& tenFirstDigits) const;

        const static std::vector<std::string> femaleFirstNames;
        const static std::vector<std::string> maleFirstNames;
        const static std::vector<std::string> lastNames;
        const static std::vector<std::string> cities;
        const static std::vector<std::string> streets;
        UniversityDB& database_;
        mutable std::mt19937_64 generator_;
        pesel_validator::PeselValidator pesel_validator_;
    };

}   // namespace data_generator
}   // namespace university
