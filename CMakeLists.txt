cmake_minimum_required (VERSION 2.6)
project(demise-ncurses)
add_subdirectory(demise-core)
add_subdirectory(src)
add_subdirectory(tests)

install(FILES ${demise-ncurses_BINARY_DIR}/compile_commands.json
    DESTINATION ${demise-ncurses_SOURCE_DIR})
