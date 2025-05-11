cmake_minimum_required(VERSION 3.20)
project(MoneyMazeServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS  OFF)

find_package(Poco REQUIRED COMPONENTS Net Util JSON Foundation)


file(GLOB_RECURSE SERVER_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx")

file(GLOB_RECURSE SERVER_HEADERS CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_executable(MoneyMazeServer
    ${SERVER_SOURCES}
    ${SERVER_HEADERS}
)

target_include_directories(MoneyMazeServer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(MoneyMazeServer
    PRIVATE
        Poco::Net
        Poco::Util
        Poco::JSON
        Poco::Foundation
)
