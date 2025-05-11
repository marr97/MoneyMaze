cmake_minimum_required(VERSION 3.19)
project(money_maze LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

## 4.2 Qt6 Widgets (замена Qt5 на Qt6 для доступа к QPalette::Accent и др.)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt_standard_project_setup()

qt_add_executable(money_maze
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    auth_window.h auth_window.cpp auth_window.ui
    reg_window.h reg_window.cpp reg_window.ui
    home_screen.h home_screen.cpp home_screen.ui


)

target_link_libraries(money_maze
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS money_maze
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET money_maze
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
