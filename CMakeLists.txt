cmake_minimum_required(VERSION 3.10)
project(DatabaseManagerProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)  # Enables automatic moc processing
set(CMAKE_AUTOUIC ON)  # Enables automatic UI processing 

# Find libpqxx
find_package(PQXX)
if(NOT PQXX_FOUND)
    find_path(PQXX_INCLUDE_DIRS NAMES pqxx/pqxx pqxx/version.hxx
        PATHS ${CMAKE_SOURCE_DIR}/external/libpqxx/include /usr/include /usr/local/include)
    find_library(PQXX_LIBRARIES NAMES pqxx
        PATHS ${CMAKE_SOURCE_DIR}/external/libpqxx/lib /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu)

    if(PQXX_INCLUDE_DIRS AND PQXX_LIBRARIES)
        message(STATUS "Found libpqxx: ${PQXX_LIBRARIES}")
    else()
        message(FATAL_ERROR "Could not find libpqxx. Please install it or provide its location.")
    endif()
endif()

# Find Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Define source files
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database/DatabaseManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/profile_window.cpp
)

# Define UI files
set(UI_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/profile_window.ui
)

# Define header files
set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/database/DatabaseManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui/profile_window.h
)

# Add executable with all source files
add_executable(database_manager_app 
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${UI_FILES}
)

# Include directories
# Add the directory containing http_client.h
target_include_directories(database_manager_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # This is important
    ${CMAKE_CURRENT_BINARY_DIR}  # For ui_*.h files
    ${PQXX_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(database_manager_app PRIVATE 
    Qt5::Widgets 
    ${PQXX_LIBRARIES}
)

# Add compiler flags for warnings
if(MSVC)
    target_compile_options(database_manager_app PRIVATE /W4)
else()
    target_compile_options(database_manager_app PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Add clang-format target (if available)
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_SOURCE_FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/database/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*.cpp
    )

    add_custom_target(
        clang_format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
        COMMENT "Formatting code with clang-format"
    )
else()
    message(STATUS "clang-format not found, formatting target will not be available")
endif()

# Option for building tests
option(BUILD_TESTS "Build the tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Output configuration information
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "libpqxx include dir: ${PQXX_INCLUDE_DIRS}")
message(STATUS "libpqxx library: ${PQXX_LIBRARIES}")
message(STATUS "Qt5Widgets library: ${Qt5Widgets_FOUND}")