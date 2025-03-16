#pragma once
#include "db_config.h"
#include <pqxx/pqxx>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR };

class DatabaseManager {
public:
  DatabaseManager();
  ~DatabaseManager();

  bool connect();
  bool disconnect();

  // Методы для работы с пользователями
  bool createUser(const std::string &username, const std::string &password);
  bool authenticateUser(const std::string &username,
                        const std::string &password);

  // Методы для работы с финансовым профилем
  enum class FinancialProfile {
    BALANCE,
    DAILY_MINIMUM,
    SAVINGS,
    DEBT,
    UNKNOWN_COLUMN
  };

  FinancialProfile financial_profile_column(const std::string &column_name) {
    if (column_name == "balance") {
      return FinancialProfile::BALANCE;
    } else if (column_name == "daily minimum" ||
               column_name == "daily_minimum") {
      return FinancialProfile::DAILY_MINIMUM;
    } else if (column_name == "dept") {
      return FinancialProfile::DEBT;
    } else if (column_name == "savings") {
      return FinancialProfile::SAVINGS;
    } else {
      return FinancialProfile::UNKNOWN_COLUMN;
    }
  }

  bool create_financial_profile(int user_id, int initial_balance,
                                int daily_minimum, int savings, int debt);
  bool update_financial_profile(const std::string &column_name, int user_id,
                                int new_value);
  int get_value_from_financial_profile(const std::string &column_name,
                                       int user_id);

private:
  std::unique_ptr<pqxx::connection> conn;
};