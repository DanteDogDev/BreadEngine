project(Interface)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_library(Interface SHARED ${SRC})
target_include_directories(Interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_precompile_headers(Interface PRIVATE ${PCH_DIR})
target_link_libraries(Interface PRIVATE
  Utils
  glfw
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
