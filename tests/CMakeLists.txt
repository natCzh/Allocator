cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(utestAlloc)

include_directories(${PROJECT_SOURCE_DIR})

set(TESTS_PROJECT_FILES TestAlloc.cpp
                            utest.cpp)

source_group ("Test Files" FILES ${TESTS_PROJECT_FILES})

# GTest
add_subdirectory(${PROJECT_SOURCE_DIR}/gtest-1.10)
enable_testing()

add_executable(${PROJECT_NAME} ${TESTS_PROJECT_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE les3Allocator_STATIC)
target_link_libraries(${PROJECT_NAME} PRIVATE gmock gtest)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../src 
												   ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} 
												   ${PROJECT_SOURCE_DIR}/gtest-1.10/googletest/include ${PROJECT_SOURCE_DIR}/gtest-1.10/googlemock/include
												   ${PROJECT_SOURCE_DIR}/gtest-1.10/googletest/googletest/include)
                                                   
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)
