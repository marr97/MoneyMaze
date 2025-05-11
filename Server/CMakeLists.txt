cmake_minimum_required(VERSION 3.20)
project(MoneyMazeServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS  OFF)

find_package(Poco REQUIRED COMPONENTS Net Util JSON Foundation)

file(GLOB_RECURSE SERVER_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(MoneyMazeServer
    ${SERVER_SOURCES}
)

target_include_directories(MoneyMazeServer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/database
        ${CMAKE_CURRENT_SOURCE_DIR}/src/database
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${PQXX_INCLUDE_DIR}
)


target_link_libraries(MoneyMazeServer
    PRIVATE
        pqxx
        Poco::Net
        Poco::Util
        Poco::JSON
        Poco::Foundation
)

install(TARGETS MoneyMazeServer
        RUNTIME DESTINATION bin)
