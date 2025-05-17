project(App)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_executable(App
    ${SRC}
)

target_precompile_headers(App PRIVATE ${PCH_DIR})
target_include_directories(App PUBLIC ${GLOBAL_SRC})

target_link_libraries(App PUBLIC 
  Toast
  EventSystem
  Interface
  Renderer
)
