cmake_minimum_required(VERSION 3.10)

# variables
set(PROJECT_NAME NetworkTool)

# set the project name and language standardds
project(${PROJECT_NAME} C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# add header files
set(HEADERS
    main.cpp
    Algorithm.h
    DataBase.h
    Host.h
    LinuxNotification.h
    Network.h
    Port.h
)

# add source files
set(SOURCES
    Algorithm.cpp
    DataBase.cpp
    Host.cpp
    LinuxNotification.cpp
    Network.cpp
    Port.cpp
)

# add exernal libraries
add_library( SQLITE3 SHARED IMPORTED )
set_target_properties(SQLITE3 PROPERTIES IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libsqlite3.so)
#target_link_libraries(${PROJECT_NAME} SHARED /usr/lib/x86_64-linux-gnu/libsqlite3.so)


# executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS}) 
target_link_libraries(${PROJECT_NAME} SQLITE3)
