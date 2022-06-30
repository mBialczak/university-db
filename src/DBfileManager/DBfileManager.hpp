#pragma once

#include "UniversityDB/UniversityDB.hpp"

#include <map>
#include <optional>
#include <string>

namespace university::db_file_manager {

class DBFileManager
{
  public:
    DBFileManager(UniversityDB& dataBase);
    int readFile(const char* fileName) const;
    int writeToFile(const char* fileName) const;

  private:
    std::string parseRecordFromFile(std::ifstream& stream) const;
    std::string readRecordPart(const std::string& fullText, const std::string& searched) const;
    std::map<std::string, std::string> getRecordAsMap(const std::string& rawRecord) const;
    bool tryMakeRecord(const std::map<std::string, std::string>& parts) const;
    std::optional<student_record::Gender> determineGender(const std::string& gender) const;

    UniversityDB& data_base_;
};

}   // namespace university::db_file_manager