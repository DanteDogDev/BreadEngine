project(EventSystem)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_library(EventSystem SHARED ${SRC})
target_precompile_headers(EventSystem PRIVATE ${PCH_DIR})
target_include_directories(EventSystem PUBLIC ${GLOBAL_SRC})

target_link_libraries(EventSystem PRIVATE
  Utils
)
