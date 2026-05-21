cmake_minimum_required(VERSION 3.20)

# ---------------------------------------------------------------------------
# Project: Axion Game Engine
# ---------------------------------------------------------------------------
project(Axion
    VERSION 0.1.0
    DESCRIPTION "Axion Game Engine"
    LANGUAGES CXX
)

# ---------------------------------------------------------------------------
# Global settings
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Put all binaries in /bin/<Config>/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)

# Default to Debug if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Enable folder grouping in IDEs (Visual Studio)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4 /permissive- /MP)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Platform defines
if(WIN32)
    add_compile_definitions(AX_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    add_compile_definitions(AX_PLATFORM_LINUX)
elseif(APPLE)
    add_compile_definitions(AX_PLATFORM_MACOS)
endif()

# Debug define
add_compile_definitions($<$<CONFIG:Debug>:AX_DEBUG>)
add_compile_definitions($<$<CONFIG:Release>:AX_RELEASE>)

# ---------------------------------------------------------------------------
# Dependencies (via vcpkg)
# ---------------------------------------------------------------------------
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Stb REQUIRED)
# find_package(assimp CONFIG REQUIRED)  # enable when needed
# find_package(EnTT CONFIG REQUIRED)    # enable when adding ECS

# ---------------------------------------------------------------------------
# Subprojects
# ---------------------------------------------------------------------------
add_subdirectory(Axion)
add_subdirectory(Sandbox)

# Make Sandbox the Visual Studio startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
