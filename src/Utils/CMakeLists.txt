project(Utils)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_library(Utils SHARED ${SRC})
target_precompile_headers(Utils PRIVATE ${PCH_DIR})
target_include_directories(Utils PUBLIC ${GLOBAL_SRC})

target_link_libraries(Utils PUBLIC
  spdlog
  TracyClient
)
