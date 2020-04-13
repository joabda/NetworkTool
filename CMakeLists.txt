cmake_minimum_required(VERSION 3.10)

# variables
set(PROJECT_NAME NetworkTool)
set(HEADER_PATH src/header/)
set(SOURCE_PATH src/source/)

# seting the project's settings
project(${PROJECT_NAME} CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -D_FORTIFY_SOURCE=2 -g -O2 -Werror=format-security")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# adding testing
enable_testing()
add_subdirectory(googletest)

# add header files
set( HEADERS
    ${HEADER_PATH}Algorithm.h
    ${HEADER_PATH}DataBase.h
    ${HEADER_PATH}Host.h
    ${HEADER_PATH}LinuxNotification.h
    ${HEADER_PATH}Network.h
    ${HEADER_PATH}Port.h
)

# add source files
set( SOURCES
    ${SOURCE_PATH}Algorithm.cpp
    ${SOURCE_PATH}DataBase.cpp
    ${SOURCE_PATH}Host.cpp
    ${SOURCE_PATH}LinuxNotification.cpp
    ${SOURCE_PATH}Network.cpp
    ${SOURCE_PATH}Port.cpp
)

add_library(core ${SOURCES} ${HEADERS})
target_include_directories( core PUBLIC /src/source)

# add exernal libraries
add_library( SQLITE3 SHARED IMPORTED )
set_target_properties( SQLITE3 PROPERTIES IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libsqlite3.so )


# executable
add_executable(${PROJECT_NAME} ${SOURCE_PATH}main.cpp) 
target_link_libraries(${PROJECT_NAME} core)
target_link_libraries(${PROJECT_NAME} SQLITE3)

# adding tests
add_subdirectory(tests)
