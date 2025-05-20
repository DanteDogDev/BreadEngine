project(App)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_executable(App ${SRC})

target_precompile_headers(App PRIVATE ${PCH_DIR})
target_link_libraries(App PRIVATE
  Toast
)
