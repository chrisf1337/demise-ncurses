cmake_minimum_required (VERSION 2.6)
project(demise-ncurses)
add_subdirectory(src)
add_subdirectory(tests)

install(FILES ${CMAKE_BINARY_DIR}/compile_commands.json
    DESTINATION ${CMAKE_SOURCE_DIR})
