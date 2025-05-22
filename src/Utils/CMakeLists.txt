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

set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(TracyClient PROPERTIES POSITION_INDEPENDENT_CODE ON)

option(TRACY_ENABLE "" ON)
option(TRACY_ON_DEMAND "" ON)
