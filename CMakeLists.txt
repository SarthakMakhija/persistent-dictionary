cmake_minimum_required(VERSION 3.14)
project(persistent_dictionary)

project(persistent_dictionary)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include append-only-kv and dependencies
add_subdirectory(src/append-only-kv)

# Enable unit/integration testing
add_executable(append_only_kv_integration_tests "")

target_sources(append_only_kv_integration_tests
        PRIVATE
        test/append-only-kv/AppendOnlyKv_integration_test.cpp
        test/append-only-kv/AppendOnlyKvFixture.h)

find_package(GTest CONFIG REQUIRED)

find_path(LIBPMEMOBJ_INCLUDE_DIR libpmemobj.h)
find_path(LIBPMEM_INCLUDE_DIR libpmem.h)

find_library(LIBPMEM_LIBRARY NAMES pmem libpmem)
find_library(LIBPMEMOBJ_LIBRARY NAMES pmemobj libpmemobj)

enable_testing()

target_include_directories(append_only_kv_integration_tests
        PRIVATE
        ${LIBPMEMOBJ_INCLUDE_DIR}
        ${LIBPMEM_INCLUDE_DIR})

target_link_libraries(append_only_kv_integration_tests
        PRIVATE
        AppendOnlyKv
        GTest::gtest
        GTest::gtest_main
        ${LIBPMEM_LIBRARY} ${LIBPMEMOBJ_LIBRARY})

add_test(
        NAME append_only_kv_integration_tests
        COMMAND $<TARGET_FILE:append_only_kv_integration_tests>
)