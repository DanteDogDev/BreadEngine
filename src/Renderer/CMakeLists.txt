project(Renderer)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "*.cpp"
    "*.hpp"
    "*.c"
    "*.h"
)

add_library(Renderer SHARED ${SRC})

target_precompile_headers(Renderer PRIVATE ${PCH_DIR})
target_include_directories(Renderer PUBLIC ${GLOBAL_SRC})
target_include_directories(Renderer PUBLIC ${GLOBAL_INC}/glad/include)

find_package(OpenGL REQUIRED)
target_link_libraries(Renderer PUBLIC 
  Utils
)
