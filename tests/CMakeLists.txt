cmake_minimum_required(VERSION 3.13)

find_package(GTest REQUIRED)

add_executable(tests tests.cpp ../src/game/logic.cpp)
target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)

