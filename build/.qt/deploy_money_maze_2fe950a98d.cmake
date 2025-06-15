include("/mnt/d/uni/MoneyMazeProject/main/MoneyMaze/build/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/money_maze-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /mnt/d/uni/MoneyMazeProject/main/MoneyMaze/build/Desktop/money_maze
    GENERATE_QT_CONF
)
