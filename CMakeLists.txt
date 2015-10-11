cmake_minimum_required (VERSION 2.6)
project(demise-ncurses)

if (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Debug")
endif()

include_directories(spdlog)

add_subdirectory(demise-core)
message(STATUS ${DEMISE-CORE_LIB_DIR})
add_subdirectory(src)
add_subdirectory(tests)

install(FILES ${demise-ncurses_BINARY_DIR}/compile_commands.json
    DESTINATION ${demise-ncurses_SOURCE_DIR})
