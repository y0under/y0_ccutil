#ifndef Y0_CCUTIL_DATABASE_DBMS_IDATAREPOSITORY_H
#define Y0_CCUTIL_DATABASE_DBMS_IDATAREPOSITORY_H

#include <map>
#include <string>
#include <vector>

namespace y0_ccutil {
  /**
   * @brief interface for dbms with repository pattern
   */
  class IDataRepository {
    public:
      virtual ~IDataRepository() = default;

      virtual void CreateTable(const std::string& tableName, const std::vector<std::pair<std::string, std::string>>& columns) = 0;
      virtual void InsertRecord(const std::string& tableName, const std::map<std::string, std::string>& data) = 0;
      virtual std::vector<std::map<std::string, std::string>> FetchRecords(const std::string& tableName) = 0;
      virtual void UpdateRecord(const std::string& tableName, int id, const std::map<std::string, std::string>& data) = 0;
      virtual void DeleteRecord(const std::string& tableName, int id) = 0;
  };
}  // namespace y0_ccutil

#endif
