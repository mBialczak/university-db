#pragma once

#include "UniversityDB/UniversityDB.hpp"

#include <map>
#include <optional>
#include <string>

namespace university {

class UniversityDB;

namespace person {
    class Person;
    enum class Gender;
}   // namespace person

class DBfileManager
{
    using StringMap = std::map<std::string, std::string>;

  public:
    explicit DBfileManager(UniversityDB& dataBase);
    int readFile(const char* fileName) const; // NOTE: verified
    int writeToFile(const char* fileName) const; // NOTE: verified

  private:
    std::string parseRecordFromFile(std::ifstream& stream) const;   // NOTE: verified
    std::string readRecordPart(const std::string& fullText, const std::string& searched) const;   // NOTE: verified
    StringMap getRecordAsMap(const std::string& rawRecord) const;   // NOTE: verified
    bool tryMakeRecord(const StringMap& parts) const;   // NOTE: verified
    std::optional<person::Gender> determineGender(const std::string& gender) const;   // NOTE: verified
    bool tryAddStudent(const StringMap& parts, person::Gender gender) const;   // NOTE: verified
    bool tryAddEmployee(const StringMap& parts, person::Gender gender) const;   // NOTE: verified

    UniversityDB& data_base_;
};

}   // namespace university