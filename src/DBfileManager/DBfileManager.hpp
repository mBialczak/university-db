#pragma once

#include "StudentRecord/StudentRecord.hpp"
#include "UniversityDB/UniversityDB.hpp"

#include <map>
#include <optional>
#include <string>

namespace university {

class UniversityDB;

class DBfileManager
{
    using StringMap = std::map<std::string, std::string>;

  public:
    explicit DBfileManager(UniversityDB& dataBase);
    int readFile(const char* fileName) const;
    int writeToFile(const char* fileName) const;

  private:
    std::string parseRecordFromFile(std::ifstream& stream) const;
    std::string readRecordPart(const std::string& fullText, const std::string& searched) const;
    StringMap getRecordAsMap(const std::string& rawRecord) const;
    bool tryMakeRecord(const StringMap& parts) const;
    std::optional<student_record::Gender> determineGender(const std::string& gender) const;

    UniversityDB& data_base_;
};

}   // namespace university