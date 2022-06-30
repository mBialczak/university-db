#include "DBfileManager.hpp"

#include <algorithm>
#include <fstream>
#include <regex>

namespace university::db_file_manager {

DBFileManager::DBFileManager(UniversityDB& dataBase)
    : data_base_(dataBase)
{
}

int DBFileManager::writeToFile(const char* fileName) const
{
    std::ofstream stream(fileName);
    if (!stream) {
        return 0;
    }
    int records_written { 0 };
    for (const auto& student : data_base_.data()) {
        stream << "Student record "
               << std::to_string(records_written + 1) + "\n"
               << "------------------\n"
               << student
               << "========================================"
               << std::endl;
        ++records_written;
    }

    return records_written;
}

int DBFileManager::readFile(const char* fileName) const
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

std::map<std::string, std::string> DBFileManager::getRecordAsMap(const std::string& rawRecord) const
{
    std::map<std::string, std::string> record_parts;
    record_parts["first_name"] = readRecordPart(rawRecord, "First name:");
    record_parts["last_name"] = readRecordPart(rawRecord, "Last name:");
    record_parts["index"] = readRecordPart(rawRecord, "Index number:");
    record_parts["pesel"] = readRecordPart(rawRecord, "PESEL:");
    record_parts["address"] = readRecordPart(rawRecord, "Address:");
    record_parts["gender"] = readRecordPart(rawRecord, "Gender:");

    return record_parts;
}

std::string DBFileManager::readRecordPart(const std::string& fullText, const std::string& searched) const
{
    const std::regex to_find { searched };
    std::istringstream stream { fullText };
    std::string line;
    // find line with searched text
    while (getline(stream, line) && !std::regex_search(line, to_find)) {
    }
    auto pos = line.find(": ");

    return line.substr(pos + 2);
}

std::string DBFileManager::parseRecordFromFile(std::ifstream& stream) const
{
    std::string line;
    std::string record_text;
    const std::regex end_line { "======" };
    while (getline(stream, line) && !std::regex_search(line, end_line)) {
        record_text += line + "\n";
    }

    return record_text;
}

bool DBFileManager::tryMakeRecord(const std::map<std::string, std::string>& parts) const
{
    // we don't want a record if any of fields would be incomplete
    for (const auto& [key, value] : parts) {
        if (value == "") {
            return false;
        }
    }
    // TODO: remove unneeded
    //  student_record::Gender gender

    // if (parts.at("gender") == "female") {
    //     gender = student_record::Gender::female;
    // }
    // else if (parts.at("gender") == "male") {
    //     gender = student_record::Gender::male;
    // }
    // else {
    //     return false;
    // }

    auto gender = determineGender(parts.at("gender"));
    if (!gender) {
        return false;
    }

    return data_base_.addStudent(std::stoi(parts.at("index")),
                                 parts.at("first_name"),
                                 parts.at("last_name"),
                                 parts.at("pesel"),
                                 parts.at("address"),
                                 *gender);
}

std::optional<student_record::Gender> DBFileManager::determineGender(const std::string& gender) const
{
    if (gender == "female") {
        return student_record::Gender::female;
    }
    else if (gender == "male") {
        return student_record::Gender::male;
    }

    return std::nullopt;
}
}   // namespace university::db_file_manager
