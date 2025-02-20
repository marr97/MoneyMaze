add_library(database_manager DatabaseManager.cpp)
target_link_libraries(database_manager ${PQXX_LIBRARIES})