# cmake_minimum_required(VERSION 3.0)
# project(PostgreSQLExample)

find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)

include_directories(${PostgreSQL_INCLUDE_DIRS})
include_directories(${LIBPQXX_INCLUDE_DIRS})

# Add executable target
# add_executable(postgresql_example main.cpp)

target_link_libraries(${PostgreSQL_LIBRARIES} ${LIBPQXX_LIBRARIES})
