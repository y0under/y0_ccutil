#ifndef Y0_CCUTIL_DATABASE_DBMS_IDATAREPOSITORY_H
#define Y0_CCUTIL_DATABASE_DBMS_IDATAREPOSITORY_H

#include <vector>
#include <string>
#include <map>

namespace y0_ccutil {
  class IDataRepository {
    public:
      virtual ~IDataRepository() = default;

      virtual void createTable(const std::string& tableName, const std::vector<std::pair<std::string, std::string>>& columns) = 0;
      virtual void insertRecord(const std::string& tableName, const std::map<std::string, std::string>& data) = 0;
      virtual std::vector<std::map<std::string, std::string>> getRecords(const std::string& tableName) = 0;
      virtual void updateRecord(const std::string& tableName, int id, const std::map<std::string, std::string>& data) = 0;
      virtual void deleteRecord(const std::string& tableName, int id) = 0;
  };
}  // namespace y0_ccutil

#endif
