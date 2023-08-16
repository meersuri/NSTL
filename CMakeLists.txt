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
    vector_runner
    src/vector_runner.cc
    )

add_executable(
    vector_test
    src/vector_test.cc
    )

target_include_directories(
    vector_runner PUBLIC
    include/
    )

target_include_directories(
    vector_test PUBLIC
    include/
    )

target_link_libraries(
    vector_test
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(vector_test)
