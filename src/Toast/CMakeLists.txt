project(Toast)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_library(Toast SHARED ${SRC})
target_precompile_headers(Toast PRIVATE ${PCH_DIR})
target_include_directories(Toast PUBLIC ${GLOBAL_SRC})

target_link_libraries(Toast PUBLIC 
  EventSystem
  Interface
  Renderer
)
