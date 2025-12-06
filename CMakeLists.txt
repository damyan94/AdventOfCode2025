cmake_minimum_required(VERSION 3.20)
project(AOC2025)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(BASE_DIR ${CMAKE_SOURCE_DIR})
set(SOURCE_DIR ${BASE_DIR}/Source)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/Bin/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)

file(GLOB_RECURSE SYSTEM_SRC CONFIGURE_DEPENDS
    ${SOURCE_DIR}/System/*.cpp
    ${SOURCE_DIR}/System/*.h
)

file(GLOB_RECURSE APP_SRC CONFIGURE_DEPENDS
    ${SOURCE_DIR}/Application/*.cpp
    ${SOURCE_DIR}/Application/*.h
)

# System (static lib)
add_library(System STATIC ${SYSTEM_SRC})

target_include_directories(System PUBLIC
    ${SOURCE_DIR}
    ${SOURCE_DIR}/System
)

target_precompile_headers(System PRIVATE ${SOURCE_DIR}/System/stdafx.h)

# Application (exe)
add_executable(Application ${APP_SRC})

target_include_directories(Application PRIVATE
    ${SOURCE_DIR}
    ${SOURCE_DIR}/System
    ${SOURCE_DIR}/Application
)

target_link_libraries(Application PRIVATE System)

target_precompile_headers(Application PRIVATE ${SOURCE_DIR}/Application/stdafx.h)

# Platform-specific includes and links
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(System PUBLIC __linux__ LINUX _LINUX)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(System PUBLIC WIN32 WIN64 _WIN32 _WIN64 _WINDOWS WINDOWS)

endif()

# Configuration-specific defines
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

target_compile_options(System PUBLIC
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU,Clang>>:-g -O0>
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU,Clang>>:-g -O3>

    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Zi /Od>
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 /DNDEBUG>
)

target_compile_definitions(System PUBLIC
    "$<$<CONFIG:Debug>:DEBUG;_DEBUG>"
    "$<$<CONFIG:Release>:RELEASE;_RELEASE;_NDEBUG>"
)

#set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")