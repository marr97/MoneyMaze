cmake_minimum_required(VERSION 3.10)
project(DatabaseManagerProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Поиск libpqxx
find_package(PQXX)
if(NOT PQXX_FOUND)
    # Если стандартный поиск не удался, попробуем найти вручную
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

# Добавить исходные файлы
add_executable(database_manager_app 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database/DatabaseManager.cpp
)

# Включить директории заголовков
target_include_directories(database_manager_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PQXX_INCLUDE_DIRS}
)

# Связать с libpqxx
target_link_libraries(database_manager_app PRIVATE ${PQXX_LIBRARIES})

# Добавить флаги компиляции для вывода всех предупреждений
if(MSVC)
    target_compile_options(database_manager_app PRIVATE /W4)
else()
    target_compile_options(database_manager_app PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Добавление цели для clang-format (если доступен)
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_SOURCE_FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/database/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    )

    add_custom_target(
        clang_format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
        COMMENT "Formatting code with clang-format"
    )

    # Сделать так, чтобы clang-format выполнялся перед сборкой
    add_dependencies(database_manager_app clang_format)
else()
    message(STATUS "clang-format not found, formatting target will not be available")
endif()

# Опция для включения тестов
option(BUILD_TESTS "Build the tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Вывод информации о конфигурации
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "libpqxx include dir: ${PQXX_INCLUDE_DIRS}")
message(STATUS "libpqxx library: ${PQXX_LIBRARIES}")