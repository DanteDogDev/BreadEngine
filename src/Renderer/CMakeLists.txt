project(Renderer)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_library(Renderer SHARED ${SRC})
target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
target_precompile_headers(Renderer PRIVATE ${PCH_DIR})
target_include_directories(Renderer PRIVATE ${GLOBAL_SRC}/glad/include)
target_link_libraries(Renderer PRIVATE
  Utils
  Interface
  glad
)
