cmake_minimum_required(VERSION 3.10)
project(DatabaseManagerProject)

set(CMAKE_CXX_STANDARD 17)

# Попытка найти libpqxx вручную
find_path(PQXX_INCLUDE_DIRS NAMES pqxx/pqxx pqxx/version.hxx
    PATHS /usr/include /usr/local/include)
find_library(PQXX_LIBRARIES NAMES pqxx
    PATHS /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu)

if(PQXX_INCLUDE_DIRS AND PQXX_LIBRARIES)
    message(STATUS "Found libpqxx: ${PQXX_LIBRARIES}")
else()
    message(FATAL_ERROR "Could not find libpqxx")
endif()

# Добавить исходные файлы
add_executable(database_manager_app 
    main.cpp
    src/database/DatabaseManager.cpp
)

# Включить директории заголовков
target_include_directories(database_manager_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PQXX_INCLUDE_DIRS}
)

# Связать с libpqxx
target_link_libraries(database_manager_app PRIVATE ${PQXX_LIBRARIES})

# Добавить флаги компиляции для вывода всех предупреждений
target_compile_options(database_manager_app PRIVATE -Wall -Wextra -Wpedantic)