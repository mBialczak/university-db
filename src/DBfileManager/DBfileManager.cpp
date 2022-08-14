#include "DBfileManager.hpp"

#include "Employee/Employee.hpp"
#include "Student/Student.hpp"

#include <algorithm>
#include <fstream>
#include <regex>

namespace university {

DBfileManager::DBfileManager(UniversityDB& dataBase)
    : data_base_(dataBase)
{
}

int DBfileManager::writeToFile(const char* fileName) const
{
    int records_written { 0 };
    std::ofstream stream(fileName);
    if (stream) {
        for (const auto& record : data_base_.data()) {
            stream << *record
                   << "========================================"
                   << std::endl;
            ++records_written;
        }
    }

    return records_written;
}

int DBfileManager::readFile(const char* fileName) const
{
    std::ifstream stream(fileName);
    int records_read { 0 };
    if (!stream) {
        std::cerr << "file not found";
        return records_read;
    }
    std::string raw_record_text;
    while (stream) {
        raw_record_text = parseRecordFromFile(stream);
        if (raw_record_text.empty()) {
            break;
        }
        auto record_parts = getRecordAsMap(raw_record_text);
        if (tryMakeRecord(record_parts)) {
            ++records_read;
        }
    }

    return records_read;
}

DBfileManager::StringMap DBfileManager::getRecordAsMap(const std::string& rawRecord) const
{
    StringMap record_parts;
    record_parts["Employee_ID"] = readRecordPart(rawRecord, "Employee ID:");
    record_parts["index"] = readRecordPart(rawRecord, "Index number:");
    record_parts["first_name"] = readRecordPart(rawRecord, "First name:");
    record_parts["last_name"] = readRecordPart(rawRecord, "Last name:");
    record_parts["pesel"] = readRecordPart(rawRecord, "PESEL:");
    record_parts["address"] = readRecordPart(rawRecord, "Address:");
    record_parts["gender"] = readRecordPart(rawRecord, "Gender:");
    record_parts["salary"] = readRecordPart(rawRecord, "Salary:");

    return record_parts;
}

std::string DBfileManager::readRecordPart(const std::string& fullText, const std::string& searched) const
{
    const std::regex to_find { searched };
    std::istringstream stream { fullText };
    std::string line;
    // find line with searched text
    while (getline(stream, line) && !std::regex_search(line, to_find)) {
    }
    auto pos = line.find(": ");

    if (pos != std::string::npos) {
        return line.substr(pos + 2);
    }

    return std::string {};
}

std::string DBfileManager::parseRecordFromFile(std::ifstream& stream) const
{
    std::string line;
    std::string record_text;
    const std::regex end_line { "======" };
    while (getline(stream, line) && !std::regex_search(line, end_line)) {
        record_text += line + "\n";
    }

    return record_text;
}

bool DBfileManager::tryMakeRecord(const StringMap& parts) const
{
    auto maybe_gender = determineGender(parts.at("gender"));
    if (!maybe_gender) {
        return false;
    }

    if (parts.at("index").size() != 0) {
        return tryAddStudent(parts, *maybe_gender);
    }
    else if (parts.at("Employee_ID").size() != 0) {
        return tryAddEmployee(parts, *maybe_gender);
    }

    return false;   // unable to determine person type
}

std::optional<person::Gender> DBfileManager::determineGender(const std::string& gender) const
{
    if (gender == "female") {
        return person::Gender::female;
    }
    else if (gender == "male") {
        return person::Gender::male;
    }

    return std::nullopt;
}

bool DBfileManager::tryAddStudent(const StringMap& parts, person::Gender gender) const
{
    return data_base_.add(student::Student(parts.at("index"),
                                           parts.at("first_name"),
                                           parts.at("last_name"),
                                           parts.at("pesel"),
                                           parts.at("address"),
                                           gender));
}

bool DBfileManager::tryAddEmployee(const StringMap& parts, person::Gender gender) const
{
    std::string salary_str = parts.at("salary");
    double salary = std::stod(salary_str);

    return data_base_.add(employee::Employee(parts.at("Employee_ID"),
                                             parts.at("first_name"),
                                             parts.at("last_name"),
                                             parts.at("pesel"),
                                             parts.at("address"),
                                             gender,
                                             salary));
}

}   // namespace university
