cmake_minimum_required(VERSION 3.6)
project(cpp_clion_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_NAME "cpp_clion_test")

set(SOURCE_FILES main.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Needed for clion autocomplete on mac
include_directories(/usr/bin/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
