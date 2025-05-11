cmake_minimum_required(VERSION 3.15)
project(MoneyMaze LANGUAGES CXX)

# Общие настройки
set(CMAKE_CXX_STANDARD        17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS      OFF)

# Пути к заголовкам
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}       # здесь будут генерироваться ui_*.h
)

## libpqxx (PostgreSQL C++ API)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Database-модуль
add_library(database
    src/database/database_manager.cpp
    src/database/database.cpp
)
target_include_directories(database PUBLIC
    ${CMAKE_SOURCE_DIR}/include/database
    ${PQXX_INCLUDE_DIRS}
)
target_link_libraries(database PUBLIC
    ${PQXX_LIBRARIES}
)


# Utils-модуль (JSON-парсер)
add_library(utils
    src/utils/json_parser.cpp
)
target_link_libraries(utils PUBLIC Qt6::Widgets)

target_include_directories(utils PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/ui
)

# Server-модуль (HTTP-сервер на базе Poco)
find_package(Poco REQUIRED COMPONENTS Net Foundation Util)
add_library(server
    src/server/http_server.cpp
    src/server/request_handler.cpp  # если используется
)
target_include_directories(server PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/server
)
target_link_libraries(server PUBLIC Poco::Net Poco::Foundation Poco::Util)


# Основное приложение
add_executable(money_maze_app
    src/server/main.cpp
)

target_include_directories(money_maze_app PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(money_maze_app PRIVATE
    database
    ui
    client
    utils
    server
    Qt6::Widgets
)