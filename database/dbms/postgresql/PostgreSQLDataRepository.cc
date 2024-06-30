#include <cctype>
#include <utility>

namespace y0_ccutil {
  /**
   * @brief constructor
   *
   * @param connection_string
   */
  PostgreSQLDataRepository::PostgreSQLDataRepository(
      const std::string &connection_string)
    : C(connection_string) {
      if (!conn_.is_open())
        throw runtime_error("Can't open database");
    }

  /**
   * @brief destructor
   */
  PostgreSQLDataRepository::~PostgreSQLDataRepository() override {
    conn_.disconnect();
  }

  /**
   * @brief create table following table_name
   *
   * @param table_name
   * @param columns
   */
  void PostgreSQLDataRepository::CreateTable(
      const std::string &table_name,
      const std::vector<std::pair<std::string, std::string>> &columns) override {
    if (!IsValidIdentifier(table_name))
      throw invalid_argument("Invalid table name");

    std::string sql = "CREATE TABLE IF NOT EXISTS " + table_name + " (ID SERIAL PRIMARY KEY, ";
    for (const auto &column: columns) {
      if (!IsValidIdentifier(column.first))
        throw invalid_argument("Invalid column name");

      sql += conn_.quote_name(column.first) + " " + column.second + ", ";
    }

    // remove the last comma
    sql.pop_back();
    sql.pop_back();
    sql += ");";

    work wk(conn_);
    wk.exec(sql);
    wk.commit();
  }

  /**
   * @brief insert data to table
   * @param table_name
   * @param data
   */
  void PostgreSQLDataRepository::InsertRecord(
      const std::string &table_name,
      const std::map<std::string, std::string> &data) override {
    if (!IsValidIdentifier(table_name))
      throw invalid_argument("Invalid table name");

    std::string sql = "INSERT INTO " + conn_.quote_name(table_name) + " (";
    std::string values = "VALUES (";
    std::vector<std::string> params;

    for (const auto &pair: data) {
      if (!IsValidIdentifier(pair.first))
        throw invalid_argument("Invalid column name");

      sql += conn_.quote_name(pair.first) + ", ";
      values += "$" + std::to_string(params.size() + 1) + ", ";
      params.emplace_back(pair.second);
    }
    // remove the last comma
    sql.pop_back();
    sql.pop_back();
    values.pop_back();
    values.pop_back();
    sql += ") " + values + ")";

    work wk(conn_);
    prepared_statement stmt = conn_.prepare("insert_statement", sql);
    for (size_t i = 0; i < params.size(); ++i) {
      stmt.bind(i + 1, params[i]);
    }

    stmt.exec();
    wk.commit();
  }

  std::vector<std::map<std::string, std::string>> FetchRecords(
      const std::string &table_name) override {
    if (!IsValidIdentifier(table_name))
      throw invalid_argument("Invalid table name");

    std::string sql = "SELECT * FROM " + conn_.quote_name(table_name);
    nontransaction non_tran(C);
    result ret(non_tran.exec(sql));

    std::vector<std::map<std::string, std::string>> records;
    for (result::const_iterator c = ret.begin(); c != ret.end(); ++c) {
      std::map<std::string, std::string> record;
      for (const auto &field: c) {
        record[field.name()] = field.as<string>();
      }
      records.emplace_back(record);
    }
    cout << "Operation done successfully" << endl;
    return records;
  }

  /**
   * @brief update table with id
   *
   * @param tableName
   * @param id
   * @param data
   */
  void UpdateRecord(const std::string& tableName,
                    const int &id,
                    const std::map<std::string, std::string>& data) override {
    if (!IsValidIdentifier(table_name))
      throw invalid_argument("Invalid table name");

    std::string sql = "UPDATE " + conn_.quote_name(table_name) + " SET ";
    std::vector<std::string> params;

    // build SET part of the SQL statement
    size_t param_index = 1;
    for (const auto &pair: data) {
        if (!IsValidIdentifier(pair.first))
            throw invalid_argument("Invalid column name");

        sql += conn_.quote_name(pair.first) +
          " = $" + std::to_string(paramIndex++) + ", ";
        params.emplace_back(pair.second);
    }

    // remove the last comma
    sql.pop_back();
    sql.pop_back();
    
    // add WHERE clause for ID
    sql += " WHERE ID = $" + std::to_string(param_index);
    params.emplace_back(std::to_string(id));

    work wk(conn_);
    prepared_statement stmt = wk.prepare(sql);
    
    // bind parameters
    for (size_t i = 0; i < params.size(); ++i) {
        stmt[i].as<std::string>() = params[i];
    }

    stmt.exec();
    wk.commit();
  }

  /**
   * @brief delete record following id
   *
   * @param table_name
   * @param id
   */
  void PostgreSQLDataRepository::DeleteRecord(
      const std::string &table_name, const int &id) override {
    if (!IsValidIdentifier(table_name))
      throw invalid_argument("Invalid table name");

    std::string sql = "DELETE FROM " +
      conn_.quote_name(table_name) + " WHERE ID = $1";

    work wk(conn_);
    wk.exec_params(sql, std::to_string(id));
    wk.commit();
  }

  /**
   * @brief for anti sql injection
   *
   * @param identifier
   *
   * @return 
   */
  bool PostgreSQLDataRepository::IsValidIdentifier(const string &identifier) {
    if (identifier.empty() || !isalpha(identifier[0]))
      return false;

    for (char c : identifier) {
      if (!std::isalnum(c) && c != '_')
        return false;
    }

    return true;
  }
};

#endif // POSTGRESQLDATAREPOSITORY_H
