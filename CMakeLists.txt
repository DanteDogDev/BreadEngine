cmake_minimum_required(VERSION 3.25)
project(engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CSS_STANDARD_REQUIRED ON)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PCH_DIR ${ROOT_DIR}/src/pch.h)
set(GLOBAL_SRC ${ROOT_DIR}/src)
set(GLOBAL_INC ${ROOT_DIR}/inc)
set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/modules)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_library(glad STATIC ${GLOBAL_INC}/glad/src/gl.c)
target_include_directories(glad PUBLIC ${GLOBAL_INC}/glad/include)

add_subdirectory(${GLOBAL_INC}/glfw)
add_subdirectory(${GLOBAL_INC}/glm)
add_subdirectory(${GLOBAL_INC}/spdlog)
add_subdirectory(${GLOBAL_INC}/tracy)

set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(TracyClient PROPERTIES POSITION_INDEPENDENT_CODE ON)

option(TRACY_ENABLE "" ON)

add_subdirectory(${GLOBAL_SRC}/App)
add_subdirectory(${GLOBAL_SRC}/Toast)
add_subdirectory(${GLOBAL_SRC}/Renderer)
add_subdirectory(${GLOBAL_SRC}/Interface)
add_subdirectory(${GLOBAL_SRC}/Utils)
