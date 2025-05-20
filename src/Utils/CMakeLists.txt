project(Utils)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_library(Utils SHARED ${SRC})
target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_precompile_headers(Utils PRIVATE ${PCH_DIR})
target_link_libraries(Utils PUBLIC
  spdlog
  TracyClient
)
