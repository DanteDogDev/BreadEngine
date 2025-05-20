project(Interface)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_library(Interface SHARED ${SRC})

target_precompile_headers(Interface PRIVATE ${PCH_DIR})
target_include_directories(Interface PUBLIC ${GLOBAL_SRC})

target_link_libraries(Interface PRIVATE
  Utils
  glfw
)
