cmake_minimum_required(VERSION 3.13)
project(GROmGameTemplate)

set(GAME_MODULE_NAME GameTemplate)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_definitions(DEBUG)
endif()

include_directories(
        ./
        GROmEngine
)

add_subdirectory(GROmEngine)
add_subdirectory(GameSources)

add_dependencies(${GAME_MODULE_NAME} Engine)

print_all_variables()