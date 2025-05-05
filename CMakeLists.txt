cmake_minimum_required(VERSION 3.15)
project(MoneyMaze LANGUAGES CXX)

# 1. Общие настройки
set(CMAKE_CXX_STANDARD        17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS      OFF)

# 2. Включаем автоматическую обработку Qt (.ui, signals/slots, resources)
set(CMAKE_AUTOMOC   ON)
set(CMAKE_AUTOUIC   ON)
set(CMAKE_AUTORCC   ON)

# 3. Пути к заголовкам
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}       # здесь будут генерироваться ui_*.h
)

# 4. Внешние зависимости

## 4.1 libpqxx (PostgreSQL C++ API)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

## 4.2 Qt6 Widgets (замена Qt5 на Qt6 для доступа к QPalette::Accent и др.)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# 5. Database-модуль
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

# 6. UI-модуль
add_library(ui
    src/ui/auth_window.cpp
    src/ui/mainwindow.cpp
    src/ui/reg_window.cpp
    src/ui/ui_main.cpp
    src/ui/auth_window.ui
    src/ui/mainwindow.ui
    src/ui/reg_window.ui
)

target_link_libraries(ui PUBLIC
    Qt6::Widgets
)

# 7. Client-модуль (HTTP-клиент, JSON-парсер берёт json.hpp из include)
add_library(client
    src/client/http_client.cpp
)
target_include_directories(client PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# 8. Utils-модуль (JSON-парсер)
add_library(utils
    src/utils/json_parser.cpp
)
target_link_libraries(utils PUBLIC Qt6::Widgets)

target_include_directories(utils PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/ui
)

# 9. Server-модуль (HTTP-сервер на базе Poco)
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


# 10. Основное приложение
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



