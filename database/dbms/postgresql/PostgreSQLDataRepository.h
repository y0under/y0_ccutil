#ifndef Y0_CCUTIL_DATABASE_DBMS_POSTGRESQL_POSTGRESQLDATAREPOSITORY_H
#define Y0_CCUTIL_DATABASE_DBMS_POSTGRESQL_POSTGRESQLDATAREPOSITORY_H

#include <pqxx/pqxx>
#include <string>

#include "IDataRepository.h"

using namespace pqxx;

namespace y0_ccutil {
  /**
   * @brief CRUD for postgresql
   */
  class PostgreSQLDataRepository : public IDataRepository {
    public:
      PostgreSQLDataRepository(const std::string &connection_string);
      void CreateTable(const std::string &table_name, const std::vector<std::pair<std::string, std::string>> &columns) override;
      void InsertRecord(const std::string &table_name, const std::map<std::string, std::string> &data) override;
      std::vector<std::map<std::string, std::string>> FetchRecords(const std::string &table_name) override;
      void UpdateRecord(const std::string &table_name, const int &id, const std::map<std::string, std::string> &data) override;
      void DeleteRecord(const std::string &table_name, const int &id) override;

    private:
      connection conn_;

      bool IsValidIdentifier(const std::string &identifier);
  };
}  // namespace y0_ccutil

#endif
