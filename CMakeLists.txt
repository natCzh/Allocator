cmake_minimum_required(VERSION 3.0)

OPTION (TESTINCLUDE "Including utest " OFF)

project(les3Allocator)

include_directories(${PROJECT_SOURCE_DIR}/)
add_definitions(-D_USE_MATH_DEFINES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#TODO переделать это!!
set(HEADERS src/AllocatorFixed.h src/MyList.h src/factorial.h)
set(SOURCES src/main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")


source_group ("Source Files" FILES ${SOURCES})
source_group ("Header Files" FILES ${HEADERS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
#add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14
                                      CXX_STANDARD_REQUIRED ON)
#target_include_directories(${PROJECT_NAME} PRIVATE)
#target_link_libraries(${PROJECT_NAME} PRIVATE)

if (TESTINCLUDE)
	add_library(${PROJECT_NAME}_STATIC STATIC ${SOURCES} ${HEADERS})
	set_target_properties(${PROJECT_NAME}_STATIC PROPERTIES CXX_STANDARD 14
                                      CXX_STANDARD_REQUIRED ON)
endif()

if (TESTINCLUDE)
	add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif()

#message(STATUS "root prefix path = ${CMAKE_INSTALL_PREFIX}")
#install(TARGETS ${PROJECT_NAME} DESTINATION .)
 
      
