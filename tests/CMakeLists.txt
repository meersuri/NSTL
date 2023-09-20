cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
  googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

include_directories(
    ../include
    )

link_libraries(
    GTest::gtest_main
    )

add_executable(vector_test vector_test.cc)
add_executable(list_test list_test.cc)
add_executable(node_test node_test.cc)
add_executable(sptr_test sptr_test.cc)
add_executable(uptr_test uptr_test.cc)

include(GoogleTest)
gtest_discover_tests(vector_test)
gtest_discover_tests(list_test)
gtest_discover_tests(node_test)
gtest_discover_tests(uptr_test)
gtest_discover_tests(sptr_test)
