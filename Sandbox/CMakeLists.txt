cmake_minimum_required(VERSION 3.20)

# ---------------------------------------------------------------------------
# Sandbox - test application linking against Axion
# ---------------------------------------------------------------------------
file(GLOB_RECURSE SANDBOX_SOURCES
    CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.h"
)

add_executable(Sandbox ${SANDBOX_SOURCES})

target_link_libraries(Sandbox PRIVATE Axion)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SANDBOX_SOURCES})
