cmake_minimum_required(VERSION 3.10)

# variables
set(PROJECT_NAME NetworkToolTest)

# add tests source files
set(SOURCES
    AlgorithmTest.cpp
)

# executable for the tests
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC
    gtest_main
    core
)

# linking tests
add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)