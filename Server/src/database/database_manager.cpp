#include "database_manager.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <optional>
#include <cstdlib>
#include <ctime>
#include <cmath>


void Logger::log(LogLevel level, const std::string &message) {
    std::string levelStr;
    switch (level) {
        case LogLevel::DEBUG:   levelStr = "DEBUG"; break;
        case LogLevel::INFO:    levelStr = "INFO"; break;
        case LogLevel::WARNING: levelStr = "WARNING"; break;
        case LogLevel::ERROR:   levelStr = "ERROR"; break;
    }

    setenv("TZ", "Europe/Moscow", 1);
    tzset(); 

    std::time_t now = std::time(nullptr);
    char buf[101];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    std::string logMsg = std::string(buf) + " [" + levelStr + "] " + message + "\n";
    std::cout << logMsg;
    std::ofstream ofs("application.log", std::ios::app);
    if (ofs.is_open()) ofs << logMsg;
}

DatabaseManager::DatabaseManager() : conn(nullptr) {}
DatabaseManager::~DatabaseManager() { disconnect(); }

bool DatabaseManager::connect() {
    try {
        std::string connStr = "postgres://money-maze-backend:yc&+qJ`XM=&g,QMB6Hj$9{>g`IM)5|rq2@rc1a-jwq5jn2b23cxfn3i.mdb.yandexcloud.net:6432/money-maze"
                     "?ssl=true"
                     "&sslmode=verify-full"
                     "&target_session_attrs=read-write";
        conn = std::make_unique<pqxx::connection>(connStr);
        if (!conn->is_open()) {
            Logger::log(LogLevel::ERROR, "Failed to open DB connection.");
            return false;
        }
        Logger::log(LogLevel::INFO, "Connected to database.");

        pqxx::work txn(*conn);

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec("SELECT to_regclass('public.users');");
        if (r[0][0].is_null()) {
            txn.exec(R"(
                CREATE TABLE users (
                    id SERIAL PRIMARY KEY,
                    username VARCHAR(255) UNIQUE NOT NULL,
                    password VARCHAR(255) NOT NULL
                );
            )");
            Logger::log(LogLevel::INFO, "Created table 'users'.");
        }
        #pragma GCC diagnostic pop

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r3 = txn.exec("SELECT to_regclass('public.financial_profile');");
        if (r3[0][0].is_null()) {
            txn.exec(R"(
                CREATE TABLE financial_profile (
                    id SERIAL PRIMARY KEY,
                    user_id INTEGER UNIQUE REFERENCES users(id),
                    balance INTEGER NOT NULL,
                    monthly_minimum INTEGER NOT NULL,
                    savings INTEGER NOT NULL,
                    debt INTEGER NOT NULL,
                    salary INTEGER NOT NULL,
                    played_months INTEGER NOT NULL,
                    deposits INTEGER NOT NULL DEFAULT 0
                );
            )");
            Logger::log(LogLevel::INFO, "Created table 'financial_profile'.");
        }
            auto checkMonthly = txn.exec(R"(
                SELECT 1
                FROM information_schema.columns
                WHERE table_name = 'financial_profile'
                    AND column_name = 'monthly_minimum';
            )");
            if (checkMonthly.empty()) {
                txn.exec(R"(
                    ALTER TABLE financial_profile
                    ADD COLUMN monthly_minimum INTEGER NOT NULL DEFAULT 0;
                )");
                Logger::log(LogLevel::WARNING, "Added missing column 'monthly_minimum' to financial_profile.");
            }

            auto checkSalary = txn.exec(R"(
                SELECT 1
                FROM information_schema.columns
                WHERE table_name = 'financial_profile'
                AND column_name = 'salary';
            )");
            if (checkSalary.empty()) {
                txn.exec(R"(
                    ALTER TABLE financial_profile
                    ADD COLUMN salary INTEGER NOT NULL DEFAULT 0;
                )");
                Logger::log(LogLevel::WARNING, "Added missing column 'salary' to financial_profile.");
            }

            auto checkPlayed = txn.exec(R"(
                SELECT 1
                FROM information_schema.columns
                WHERE table_name = 'financial_profile'
                AND column_name = 'played_months';
            )");
            if (checkPlayed.empty()) {
                txn.exec(R"(
                    ALTER TABLE financial_profile
                    ADD COLUMN played_months INTEGER NOT NULL DEFAULT 0;
                )");
                Logger::log(LogLevel::WARNING, "Added missing column 'played_months' to financial_profile.");
            }

            auto checkDeposits = txn.exec(R"(
                SELECT 1
                FROM information_schema.columns
                WHERE table_name = 'financial_profile'
                AND column_name = 'deposits';
            )");

            auto checkTotalDeposit = txn.exec(R"(
                SELECT 1 FROM information_schema.columns
                WHERE table_name = 'financial_profile' AND column_name = 'total_deposit';
            )");
            if (checkTotalDeposit.empty()) {
                txn.exec(R"(
                    ALTER TABLE financial_profile ADD COLUMN total_deposit INTEGER NOT NULL DEFAULT 0;
                )");
                Logger::log(LogLevel::WARNING, "Added missing column 'total_deposit' to financial_profile.");
            }

            auto checkSavings = txn.exec(R"(
                SELECT 1
                FROM information_schema.columns
                WHERE table_name = 'financial_profile'
                AND column_name = 'savings';
            )");
            if (checkSavings.empty()) {
                txn.exec(R"(
                    ALTER TABLE financial_profile
                    ADD COLUMN savings INTEGER NOT NULL DEFAULT 0;
                )");
                Logger::log(LogLevel::WARNING, "Added missing column 'savings' to financial_profile.");
            }

            auto r4 = txn.exec("SELECT to_regclass('public.deposits');");
            if (r4.size() && r4[0][0].is_null()) {
                txn.exec(R"(
                    CREATE TABLE deposits (
                        id SERIAL PRIMARY KEY,
                        user_id INTEGER REFERENCES users(id),
                        principal BIGINT NOT NULL,
                        rate DOUBLE PRECISION NOT NULL,
                        term_months INTEGER NOT NULL,
                        start_date DATE NOT NULL,
                        status VARCHAR(20) NOT NULL DEFAULT 'active',
                        passed_months INTEGER NOT NULL DEFAULT 0,
                        created_at TIMESTAMP NOT NULL DEFAULT NOW()
                    );
                )");
                Logger::log(LogLevel::INFO, "Created table 'deposits'.");
            }
        #pragma GCC diagnostic pop

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r2 = txn.exec("SELECT to_regclass('public.loans');");
        if (r2[0][0].is_null()) {
            txn.exec(R"(
                CREATE TABLE loans (
                    id SERIAL PRIMARY KEY,
                    user_id INTEGER REFERENCES users(id),
                    amount INTEGER NOT NULL,
                    period INTEGER NOT NULL,
                    rate DOUBLE PRECISION NOT NULL,
                    passed_months INTEGER DEFAULT 0
                );
            )");
            Logger::log(LogLevel::INFO, "Created table 'loans'.");
        }
        #pragma GCC diagnostic pop

        txn.commit();
        return true;
    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("Connection error: ") + e.what());
        return false;
    }
}

bool DatabaseManager::disconnect() {
    if (conn) {
        conn.reset();
        Logger::log(LogLevel::INFO, "Disconnected from database.");
        return true;
    }
    return false;
}

bool DatabaseManager::createFinancialProfile(int user_id) {
    if (!conn || !conn->is_open()) return false;

    try {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        pqxx::work txn(*conn);
        txn.exec_params(
            "INSERT INTO financial_profile (user_id, balance, monthly_minimum, savings, debt, salary, played_months, deposits, total_deposit) "
            "VALUES ($1, 60000, 25000, 0, 0, 60000, 1, 0, 0);",
            user_id
        );
        txn.commit();
        #pragma GCC diagnostic pop
        Logger::log(LogLevel::INFO, "Created financial profile for user_id: " + std::to_string(user_id));
        return true;
    } catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, "createFinancialProfile error: " + std::string(e.what()));
        return false;
    }
}

bool DatabaseManager::createUser(const std::string &username, const std::string &password) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "No open DB connection for createUser.");
        return false;
    }
    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params(
            "INSERT INTO users (username, password) VALUES ($1, $2) "
            "ON CONFLICT (username) DO NOTHING RETURNING id;",
            username, password
        );
        #pragma GCC diagnostic pop

        txn.commit();
                if (r.empty()) {
            Logger::log(LogLevel::WARNING, "User already exists: " + username);
            return false;
        }

        int user_id = r[0][0].as<int>();

        if (!createFinancialProfile(user_id)) {
            Logger::log(LogLevel::ERROR, "Failed to create financial profile for new user.");
            return false;
        }

        Logger::log(LogLevel::INFO, "Created user: " + username);
        return true;


    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("createUser error: ") + e.what());
        return false;
    }
}

std::optional<std::string> DatabaseManager::getPasswordByUsername(const std::string& username) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "No open DB connection for getPasswordByUsername.");
        return std::nullopt;
    }
    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params("SELECT password FROM users WHERE username = $1;", username);
        #pragma GCC diagnostic pop
        txn.commit();

        if (r.empty()) {
            Logger::log(LogLevel::WARNING, "User not found: " + username);
            return std::nullopt;
        }
        return r[0][0].as<std::string>();
    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("getPasswordByUsername error: ") + e.what());
        return std::nullopt;
    }
}

std::optional<int> DatabaseManager::getUserIdByUsername(const std::string& username) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "Database not connected");
        return std::nullopt;
    }

    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        pqxx::result result = txn.exec_params(
            "SELECT id FROM users WHERE username = $1",
            username
        );
        #pragma GCC diagnostic pop

        if (result.empty()) {
            return std::nullopt;
        }

        int user_id = result[0][0].as<int>();
        return user_id;

    } catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, std::string("getUserIdByUsername failed: ") + e.what());
        return std::nullopt;
    }
}


bool DatabaseManager::authenticateUser(const std::string &username, const std::string &password) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "No open DB connection for authenticateUser.");
        return false;
    }
    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params(
            "SELECT id FROM users WHERE username = $1 AND password = $2;",
            username, password
        );
        #pragma GCC diagnostic pop
        return !r.empty();
    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("authenticateUser error: ") + e.what());
        return false;
    }
}



std::optional<FinancialProfile> DatabaseManager::getFinancialProfile(int user_id) {
    if (!conn || !conn->is_open()) return std::nullopt;
    
    try {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        pqxx::work txn(*conn);
        auto r = txn.exec_params(
            "SELECT "
            "  balance, "
            "  monthly_minimum, "
            "  COALESCE(savings, 0)   AS savings, "
            "  debt, "
            "  salary, "
            "  played_months, "
            "  deposits "
            "FROM financial_profile WHERE user_id = $1;",
            user_id
        );
        
        if (r.empty()) return std::nullopt;

        auto depositSum = txn.exec_params(
            "SELECT COALESCE(SUM(\"principal\" * POW(1 + rate/100/12, passed_months)), 0) "
            "FROM deposits WHERE user_id = $1 AND status = 'active';",
            user_id
        );

        auto checkColumn = txn.exec(
            "SELECT 1 FROM information_schema.columns "
            "WHERE table_name = 'deposits' AND column_name = 'principal'");
            
        if (checkColumn.empty()) {
            Logger::log(LogLevel::ERROR, "Column 'principal' does not exist in deposits table");
            throw std::runtime_error("Database schema error: missing principal column");
        }
        
        FinancialProfile profile;
        profile.balance = r[0][0].as<int>();
        profile.monthly_minimum = r[0][1].as<int>();
        profile.savings = r[0][2].as<int>();
        profile.debt = r[0][3].as<int>();
        profile.salary = r[0][4].as<int>();
        profile.played_months = r[0][5].as<int>();
        profile.deposits = r[0][6].as<int>();
        profile.total_deposit = depositSum[0][0].as<int>();

        auto hasDeposits = txn.exec_params(
            "SELECT 1 FROM deposits WHERE user_id = $1 AND status = 'active' LIMIT 1;",
            user_id
        );

        if (hasDeposits.empty()) {
            profile.total_deposit = 0;
        } else {
            auto depositSum = txn.exec_params(
                "SELECT COALESCE(SUM(\"principal\" * POW(1 + rate/100/12, passed_months)), 0) "
                "FROM deposits WHERE user_id = $1 AND status = 'active';",
                user_id
            );
            profile.total_deposit = depositSum[0][0].as<int>();
        }

        txn.exec_params(
            "UPDATE financial_profile SET total_deposit = $1 WHERE user_id = $2;",
            profile.total_deposit, user_id
        );
        #pragma GCC diagnostic pop
        
        return profile;
    } catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, "getFinancialProfile error: " + std::string(e.what()));
        return std::nullopt;
    }
}

bool DatabaseManager::updateFinancialProfile(int user_id, const FinancialProfile& profile) {
    if (!conn || !conn->is_open()) return false;
    
    try {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        pqxx::work txn(*conn);
        txn.exec_params(
            "UPDATE financial_profile SET "
            "balance = $1, monthly_minimum = $2, savings = $3, debt = $4, "
            "salary = $5, played_months = $6, deposits = $7 "
            "WHERE user_id = $8;",
            profile.balance, profile.monthly_minimum, profile.savings, 
            profile.debt, profile.salary, profile.played_months, profile.deposits, user_id
        );
        #pragma GCC diagnostic pop
        txn.commit();
        return true;
    } catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, "updateFinancialProfile error: " + std::string(e.what()));
        return false;
    }
}

bool DatabaseManager::createLoan(int user_id, int amount, int period, double rate) {
    if (!conn || !conn->is_open()) return false;
    
    try {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        pqxx::work txn(*conn);
        txn.exec_params(
            "INSERT INTO loans (user_id, amount, period, rate, passed_months) "
            "VALUES ($1, $2, $3, $4, 0);",
            user_id, amount, period, rate
        );
        #pragma GCC diagnostic pop
        txn.commit();
        
        auto profileOpt = getFinancialProfile(user_id);
        if (!profileOpt) return false;
        FinancialProfile profile = *profileOpt;

        profile.balance += amount;
        profile.debt += amount;
        updateFinancialProfile(user_id, profile);
        
        return true;
    } catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, "createLoan error: " + std::string(e.what()));
        return false;
    }
}

LoanInfo DatabaseManager::getLoanInfo(int user_id) {
    constexpr int DEFAULT_MIN_LOAN = 1000;

    auto profileOpt = getFinancialProfile(user_id);
    if (!profileOpt) {
        return {15.0, 1, 12, DEFAULT_MIN_LOAN, DEFAULT_MIN_LOAN};
    }
    const FinancialProfile &p = *profileOpt;
    int maxLoan = p.salary - p.monthly_minimum;
    if (maxLoan < DEFAULT_MIN_LOAN) {
        maxLoan = DEFAULT_MIN_LOAN;
    }
    return {15.0, 1, 12, DEFAULT_MIN_LOAN, maxLoan};
}

std::vector<LoanRecord> DatabaseManager::getUserLoans(int user_id) {
    std::vector<LoanRecord> loans;
    if (!conn || !conn->is_open()) return loans;

    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params(
            "SELECT id, amount, period, rate, passed_months "
            "FROM loans WHERE user_id = $1;",
            user_id
        );
        #pragma GCC diagnostic pop
        for (const auto &row : r) {
            loans.push_back(LoanRecord{
                row[0].as<int>(),
                row[1].as<int>(),
                row[2].as<int>(),
                row[3].as<double>(),
                row[4].as<int>()
            });
        }
    } catch (const std::exception& e) {
    Logger::log(LogLevel::ERROR, "getUserLoans error: " + std::string(e.what()));
    }
    return loans;
}

bool DatabaseManager::updateLoan(const LoanRecord& loan) {
    if (!conn || !conn->is_open()) return false;
    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        txn.exec_params(
            "UPDATE loans "
            "SET amount = $1, passed_months = $2 "
            "WHERE id = $3;",
            loan.amount,
            loan.passed_months,
            loan.id
        );
        #pragma GCC diagnostic pop
        txn.commit();
        return true;
    } catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, "updateLoan error: " + std::string(e.what()));
        return false;
    }
}

bool DatabaseManager::createDeposit(int user_id, long long principal, int term_months, double rate) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "createDeposit: no open DB connection");
        return false;
    }
    if (principal <= 0) {
        Logger::log(LogLevel::WARNING, "createDeposit: principal must be positive");
        return false;
    }
    if (term_months <= 0) {
        Logger::log(LogLevel::WARNING, "createDeposit: term_months must be positive");
        return false;
    }
    if (rate < 0.0) {
        Logger::log(LogLevel::WARNING, "createDeposit: rate must be non-negative");
        return false;
    }

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    try {
        pqxx::work txn(*conn);

        pqxx::result r = txn.exec_params(
            "SELECT balance FROM financial_profile WHERE user_id = $1 FOR UPDATE;",
            user_id
        );
        if (r.empty()) {
            Logger::log(LogLevel::WARNING, "createDeposit: financial_profile not found for user_id " + std::to_string(user_id));
            return false;
        }

        long long current_balance = r[0][0].as<long long>();

        if (principal > current_balance) {
            Logger::log(LogLevel::WARNING,
                "createDeposit: insufficient balance. user_id=" + std::to_string(user_id)
                + ", principal=" + std::to_string(principal)
                + ", balance=" + std::to_string(current_balance));
            return false;
        }

        txn.exec_params(
            "INSERT INTO deposits (user_id, principal, rate, term_months, start_date, status) "
            "VALUES ($1, $2, $3, $4, CURRENT_DATE, 'active');",
            user_id, principal, rate, term_months
        );

        long long new_balance = current_balance - principal;
        txn.exec_params(
            "UPDATE financial_profile SET balance = $1 WHERE user_id = $2;",
            new_balance, user_id
        );
        #pragma GCC diagnostic pop

        txn.commit();

        Logger::log(LogLevel::INFO,
            "createDeposit: success for user_id=" + std::to_string(user_id)
            + ", principal=" + std::to_string(principal)
            + ", term_months=" + std::to_string(term_months)
            + ", rate=" + std::to_string(rate));
        return true;
    }
    catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, "createDeposit error: " + std::string(e.what()));
        return false;
    }
}

std::vector<DepositInfo> DatabaseManager::getUserDeposits(int user_id) {
    std::vector<DepositInfo> deposits;
    if (!conn || !conn->is_open()) return deposits;

    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params(
            "SELECT id, principal, rate, term_months, passed_months, start_date "
            "FROM deposits WHERE user_id = $1 AND status = 'active';",
            user_id
        );
        #pragma GCC diagnostic pop
        
        for (const auto &row : r) {
            DepositInfo deposit;
            deposit.id = row[0].as<int>();
            deposit.principal = row[1].as<long long>();
            deposit.rate = row[2].as<double>();
            deposit.term_months = row[3].as<int>();
            deposit.passed_months = row[4].as<int>();
            deposit.start_date = row[5].as<std::string>();
            
            deposit.current_amount = static_cast<long long>(
                deposit.principal * pow(1 + deposit.rate/100/12, deposit.passed_months)
            );
            
            deposits.push_back(deposit);
        }
    } catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, "getUserDeposits error: " + std::string(e.what()));
    }
    return deposits;
}

std::optional<int> DatabaseManager::getUserDepositSum(int user_id) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "No DB connection in getUserDepositSum");
        return std::nullopt;
    }

    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto check = txn.exec_params(
            "SELECT 1 FROM deposits WHERE user_id = $1 AND status = 'active' LIMIT 1;",
            user_id
        );
        
        if (check.empty()) {
            return std::nullopt;
        }

        auto r = txn.exec_params(
            "SELECT COALESCE(SUM(principal * POW(1 + rate/100/12, passed_months)), 0) "
            "FROM deposits WHERE user_id = $1 AND status = 'active';",
            user_id
        );
        #pragma GCC diagnostic pop

        return r[0][0].as<int>();

    } catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, 
            std::string("getUserDepositSum error: ") + e.what());
        return std::nullopt;
    }
}

