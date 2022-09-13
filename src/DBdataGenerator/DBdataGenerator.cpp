#include "DBdataGenerator.hpp"

#include "Employee/Employee.hpp"
#include "Student/Student.hpp"
#include "UniversityDB/UniversityDB.hpp"

namespace university::data_generator {

namespace {
    using university::employee::Employee;
    using university::person::Gender;
    using university::pesel_validator::PeselValidator;
    using university::student::Student;

    constexpr unsigned MIN_YEAR { 0 };
    constexpr unsigned MAX_YEAR { 99 };
    constexpr double SALARY_MIN { 1000.0 };
    constexpr double SALARY_MAX { 15000.0 };
}   // namespace

DBdataGenerator::DBdataGenerator(UniversityDB& dataBaseToFill)
    : generator_(std::random_device {}())
    , database_(dataBaseToFill)
{
}

void DBdataGenerator::addStudents(unsigned numberOfStudents) const
{
    unsigned actually_added { 0 };
    while (actually_added < numberOfStudents) {
        bool was_added = database_.add(generateStudent());
        if (was_added) {
            ++actually_added;
        }
    }
}

void DBdataGenerator::addEmployees(unsigned numberOfEmployees) const
{
    unsigned actually_added { 0 };
    while (actually_added < numberOfEmployees) {
        bool was_added = database_.add(generateEmployee());
        if (was_added) {
            ++actually_added;
        }
    }
}

student::Student DBdataGenerator::generateStudent() const
{
    std::string index = generateIndex();
    Gender gender = generateGender();
    std::string firstName = generateFirstName(gender);
    std::string lastName = generateLastName();
    std::string pesel = generatePesel();
    std::string address = generateAddress();

    return Student { index, firstName, lastName, pesel, address, gender };
}

employee::Employee DBdataGenerator::generateEmployee() const
{
    std::string id = generateId();
    Gender gender = generateGender();
    std::string firstName = generateFirstName(gender);
    std::string lastName = generateLastName();
    std::string pesel = generatePesel();
    std::string address = generateAddress();
    double salary = generateSalary();

    return Employee { id, firstName, lastName, pesel, address, gender, salary };
}

long unsigned DBdataGenerator::randomInt(uint_fast64_t from, uint_fast64_t to) const
{
    std::uniform_int_distribution<uint_fast64_t> distrib(from, to);

    return distrib(generator_);
}

double DBdataGenerator::randomDouble(double from, double to) const
{
    std::uniform_real_distribution<> distrib(from, to);

    return distrib(generator_);
}

std::string DBdataGenerator::generateIndex() const
{
    std::string result;
    long unsigned sequential_part = randomInt(1, 500);
    long unsigned year_part = randomInt(2016, 2026);

    return std::to_string(sequential_part) + "/" + std::to_string(year_part);
}

std::string DBdataGenerator::generateId() const
{
    std::string result;
    long unsigned department_number = randomInt(0, departments.size() - 1);
    std::string department_part = departments.at(department_number);

    std::string sequential_part = std::to_string(randomInt(1, 100));
    addZerosIfTooShort(sequential_part, 3);
    return department_part + ":" + sequential_part;
}

Gender DBdataGenerator::generateGender() const
{
    bool should_be_male = static_cast<bool>(randomInt(0, 1));

    return should_be_male ? Gender::male
                          : Gender::female;
}

std::string DBdataGenerator::generateFirstName(Gender gender) const
{
    if (gender == Gender::male) {
        long unsigned male_name_number = randomInt(0, maleFirstNames.size() - 1);
        return maleFirstNames.at(male_name_number);
    }

    long unsigned female_name_number = randomInt(0, femaleFirstNames.size() - 1);

    return femaleFirstNames.at(female_name_number);
}

std::string DBdataGenerator::generateLastName() const
{
    long unsigned last_name_number = randomInt(0, lastNames.size() - 1);

    return lastNames.at(last_name_number);
}

std::string DBdataGenerator::generatePesel() const
{
    std::string year_part = std::to_string(randomInt(MIN_YEAR, MAX_YEAR));
    addZerosIfTooShort(year_part);

    long unsigned month = randomInt(1, 12);
    std::string month_part = std::to_string(month);
    addZerosIfTooShort(month_part);

    std::string day_part = generateDayForMonth(month);
    addZerosIfTooShort(day_part);

    std::string four_digits = std::to_string(randomInt(1, 9999));
    addZerosIfTooShort(four_digits, 4);

    std::string ten_first_digits = year_part + month_part + day_part + four_digits;
    std::string control_digit = generateControlDigit(ten_first_digits);

    return year_part + month_part + day_part + four_digits + control_digit;
}

std::string DBdataGenerator::generateDayForMonth(long unsigned month) const
{
    switch (month) {
        case 2:
            // since we only generate fake pesel numbers we ignore leap year possibility
            return std::to_string(randomInt(1, 28));
        case 1:
            [[fallthrough]];
        case 3:
            [[fallthrough]];
        case 5:
            [[fallthrough]];
        case 7:
            [[fallthrough]];
        case 8:
            [[fallthrough]];
        case 10:
            [[fallthrough]];
        case 12:
            return std::to_string(randomInt(1, 31));
        default:   // for 4, 6, 9, 11
            return std::to_string(randomInt(1, 30));
    }
}

void DBdataGenerator::addZerosIfTooShort(std::string& digitString, unsigned requestedLength) const
{
    while (digitString.length() < requestedLength) {
        digitString = "0" + digitString;
    }
}

std::string DBdataGenerator::generateControlDigit(const std::string& tenFirstDigits) const
{
    unsigned sum_of_products { 0 };
    constexpr static std::array<unsigned, 10> digit_weights = { 1, 3, 7, 9, 1, 3, 7, 9, 1, 3 };
    for (std::size_t pos = 0; pos < 10; ++pos) {
        sum_of_products += (pos < 9) ? (digit_weights.at(pos) * std::stoi(tenFirstDigits.substr(pos, 1)))
                                     : (digit_weights.at(pos) * std::stoi(tenFirstDigits.substr(pos)));
    }

    unsigned modulo = sum_of_products % 10;

    return modulo == 0 ? "0"
                       : std::to_string(10 - modulo);
}

std::string DBdataGenerator::generateAddress() const
{
    std::string address { "Polska, " };
    std::string postal_code = std::to_string(randomInt(1, 99));
    addZerosIfTooShort(postal_code);
    address += postal_code + " ";
    address += cities.at(randomInt(0, cities.size() - 1)) + ", ul.";
    address += streets.at(randomInt(0, streets.size() - 1)) + " ";
    address += std::to_string(randomInt(1, 200)) + "/";
    address += std::to_string(randomInt(1, 70));

    return address;
}

double DBdataGenerator::generateSalary() const
{
    return randomDouble(SALARY_MIN, SALARY_MAX);
}

}   // namespace university::data_generator
