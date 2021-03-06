cmake_minimum_required(VERSION 3.6)
project(cpp_clion_test)

set(IMGUI_SFML_BUILD_EXAMPLES 0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_NAME "sfml-base")
set(IMGUI_ROOT "${CMAKE_SOURCE_DIR}/imgui")

set(SOURCE_FILES
        src/Main.cpp
        src/logger/Logger.cpp
        src/logger/Logger.h
        src/ui/UIWindow.h src/ui/UIGroup.h src/ui/UIElement.h src/ui/UIConsoleWindow.h)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

add_subdirectory("${CMAKE_SOURCE_DIR}/imgui-sfml")

add_executable(${EXECUTABLE_NAME} ${IMGUI_SOURCES} ${IMGUI_SFML_SOURCES} ${SOURCE_FILES})

# Needed for clion autocomplete on mac
include_directories(/usr/bin/include)

# SFML
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR} ${IMGUI_SFML_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${IMGUI_SFML_DEPENDENCIES})
endif()

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
  # or: target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARY})
  target_link_libraries(${EXECUTABLE_NAME} m)  # if you use maths.h
endif()