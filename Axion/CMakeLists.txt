cmake_minimum_required(VERSION 3.20)

# ---------------------------------------------------------------------------
# Axion Engine (static library)
# ---------------------------------------------------------------------------
file(GLOB_RECURSE AXION_SOURCES
    CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
    "include/*.h"
    "include/*.hpp"
)

add_library(Axion STATIC ${AXION_SOURCES} "src/Axion/Time/Time.h" "src/Axion/Time/Time.cpp" "src/Axion/Core/KeyCodes.h" "src/Axion/Core/MouseCodes.h" "src/Axion/Event/Event.h"  "src/Axion/Event/AplicationEvent.h" "src/Axion/Event/KeyEvent.h" "src/Axion/Event/MouseEvent.h" "src/Axion/Core/Input.h" "src/Axion/Core/Input.cpp")

target_include_directories(Axion
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Stb_INCLUDE_DIR}
)

target_link_libraries(Axion
    PUBLIC
        glfw
        glad::glad
        glm::glm
        spdlog::spdlog
        imgui::imgui
)

# Precompiled header
target_precompile_headers(Axion PRIVATE src/axpch.h)

# IDE source grouping
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${AXION_SOURCES})