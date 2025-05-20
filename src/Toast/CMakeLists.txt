project(Toast)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_library(Toast SHARED ${SRC})
target_precompile_headers(Toast PRIVATE ${PCH_DIR})
target_include_directories(Toast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Toast PUBLIC
  Utils
  Interface
  Renderer
)
