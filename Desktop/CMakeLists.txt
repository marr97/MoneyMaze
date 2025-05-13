cmake_minimum_required(VERSION 3.19)
project(money_maze LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui Network)

## Qt6 Widgets (замена Qt5 на Qt6 для доступа к QPalette::Accent и др.)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Poco REQUIRED COMPONENTS Net Util Foundation)

qt_standard_project_setup()

file(GLOB_RECURSE MAZE_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui")

file(GLOB_RECURSE MAZE_HEADERS CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

qt_add_executable(money_maze
    WIN32 MACOSX_BUNDLE
    ${MAZE_SOURCES}
    ${MAZE_HEADERS}
)

target_include_directories(money_maze
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann
)

target_link_libraries(money_maze
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Network
)

target_link_libraries(money_maze
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Poco::Net
        Poco::Util
        Poco::Foundation
)

include(GNUInstallDirs)

install(TARGETS money_maze
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_generate_deploy_app_script(
    TARGET money_maze
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
