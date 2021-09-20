cmake_minimum_required(VERSION 3.10)
project(jet_brains_counter)

find_package(Threads REQUIRED)

macro(add_unit_test target target_test)
    add_executable(${target} ${HEADERS} ${SOURCES})
    target_compile_definitions(${target} PRIVATE ${target_test}=1)
    target_link_libraries(${target} PRIVATE Threads::Threads)
    set(UNIT_TESTS "${UNIT_TESTS} ${target}")
    add_test(${target} ${CMAKE_CURRENT_BINARY_DIR}/${target_test})
    set_tests_properties(${target} PROPERTIES PASS_REGULAR_EXPRESSION "true")
endmacro(add_unit_test)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(HEADERS counter.h)
set(SOURCES test.c)

enable_testing()

add_unit_test(SERIAL_TEST SERIAL_TEST)
add_unit_test(CONCURRENT_INC_TEST CONCURRENT_INC_TEST)
add_unit_test(CONCURRENT_INC_AND_GET_TEST CONCURRENT_INC_AND_GET_TEST)
