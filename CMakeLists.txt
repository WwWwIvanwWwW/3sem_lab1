cmake_minimum_required(VERSION 3.14)
project(Lab1_Sem3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(binarytree_lib INTERFACE)

target_include_directories(binarytree_lib INTERFACE
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE binarytree_lib)

enable_testing()
find_package(GTest REQUIRED)

function(add_lab_test TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE 
        GTest::gtest_main 
        binarytree_lib
    )
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_lab_test(test_BinaryTree tests/test_BinaryTree.cpp)