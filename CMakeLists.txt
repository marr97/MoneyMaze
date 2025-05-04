cmake_minimum_required(VERSION 3.15)
project(MoneyMaze LANGUAGES CXX)

# 1. Общие настройки
set(CMAKE_CXX_STANDARD        17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS      OFF)

# 2. Пути к заголовкам
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# 3. Внешние зависимости

## 3.1 libpqxx (PostgreSQL C++ API)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

## 3.2 Qt5 Widgets (для UI-модуля)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 4. Database-модуль
add_library(database
    src/database/database.cpp
)
target_include_directories(database PUBLIC
    ${CMAKE_SOURCE_DIR}/include/database
    ${PQXX_INCLUDE_DIRS}
)
target_link_libraries(database PUBLIC
    ${PQXX_LIBRARIES}
)

# 5. UI-модуль

# 5.1 Обёртка .ui → заголовки
qt5_wrap_ui(UI_HEADERS
    ${CMAKE_SOURCE_DIR}/src/ui/forms/auth_window.ui
    ${CMAKE_SOURCE_DIR}/src/ui/forms/mainwindow.ui
    ${CMAKE_SOURCE_DIR}/src/ui/forms/reg_window.ui
)

add_library(ui
    src/ui/auth_window.cpp
    src/ui/mainwindow.cpp
    src/ui/reg_window.cpp
    ${UI_HEADERS}
)
target_include_directories(ui PUBLIC
    ${CMAKE_SOURCE_DIR}/include/ui
)


target_link_libraries(ui PUBLIC
    Qt5::Widgets
)

# 6. Client-модуль (использует nlohmann/json)
add_library(client
    src/client/http_client.cpp
)

target_include_directories(ui PUBLIC
    ${CMAKE_SOURCE_DIR}/include/ui
    ${CMAKE_BINARY_DIR}            
)

target_include_directories(client PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# 7. Utils-модуль (JSON-парсер)
add_library(utils
    src/utils/json_parser.cpp
)

target_link_libraries(utils PUBLIC Qt5::Widgets)

target_include_directories(utils PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

