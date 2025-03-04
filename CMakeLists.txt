cmake_minimum_required(VERSION 3.22)

project(MoneyMaze CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

find_package(Poco REQUIRED COMPONENTS Foundation Net)
find_package(Qt5 REQUIRED COMPONENTS Core Sql)

include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

include_directories(
    "C:/Qt/6.5.2/msvc2019_64/include"
    "C:/Qt/6.5.2/msvc2019_64/include/QtCore"
    "C:/Qt/6.5.2/msvc2019_64/include/QtSql"
)

set(SOURCES
    src/server/main.cpp
    src/server/http_server.cpp
    src/server/request_handler.cpp
    src/database/database.cpp
    src/utils/json_parser.cpp
    src/client/http_client.cpp
)

add_executable(money_maze ${SOURCES})

target_link_libraries(money_maze 
    Poco::Foundation
    Poco::Net
    Qt5::Core
    Qt5::Sql
    nlohmann_json::nlohmann_json
)
