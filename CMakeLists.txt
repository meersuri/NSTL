cmake_minimum_required(VERSION 3.14)
project(non_standard_template_library)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    vector_test
    src/vector_test.cc
    )

add_executable(
    node_test
    src/node_test.cc
    )

add_executable(
    list_test
    src/list_test.cc
    )

add_executable(
    sptr_test
    src/sptr_test.cc
    )

target_include_directories(
    vector_test PUBLIC
    include/
    )

target_include_directories(
    node_test PUBLIC
    include/
    )

target_include_directories(
    list_test PUBLIC
    include/
    )

target_include_directories(
    sptr_test PUBLIC
    include/
    )

target_link_libraries(
    vector_test
    GTest::gtest_main
    )

target_link_libraries(
    node_test
    GTest::gtest_main
    )

target_link_libraries(
    list_test
    GTest::gtest_main
    )

target_link_libraries(
    sptr_test
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(vector_test)
gtest_discover_tests(node_test)
gtest_discover_tests(list_test)
gtest_discover_tests(sptr_test)
