cmake_minimum_required(VERSION 3.14)

add_library(nstd
    ../include/vector.h
    ../include/list.h
    ../include/node.h
    ../include/uptr.h
    ../include/sptr.h)

target_include_directories(nstd PUBLIC ../include)

set_target_properties(nstd PROPERTIES LINKER_LANGUAGE CXX)


