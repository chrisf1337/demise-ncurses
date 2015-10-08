set(SRCS )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")

find_path(NCURSES_INCLUDE_DIR
    NAMES
    ncurses.h
    PATHS
    /usr/local/opt/ncurses/include
    /usr/include
    NO_DEFAULT_PATH)
find_library(NCURSES_LIBRARY
    NAMES
    ncurses
    PATHS
    /usr/local/opt/ncurses/lib
    /usr/lib/x86_64-linux-gnu
    NO_DEFAULT_PATH)
find_library(DEMISE-CORE
    NAMES
    demise-core
    PATHS
    ${demise-ncurses_SOURCE_DIR}/demise-core/lib/static
    NO_DEFAULT_PATH)

include_directories(${NCURSES_INCLUDE_DIR} ${demise-ncurses_SOURCE_DIR}/demise-core/src)

add_definitions(-std=c++14)

add_executable(demise demise.cpp)
target_link_libraries(demise ${NCURSES_LIBRARY} ${DEMISE-CORE})

install(TARGETS demise
    RUNTIME DESTINATION ${demise-ncurses_SOURCE_DIR}/bin
    LIBRARY DESTINATION ${demise-ncurses_SOURCE_DIR}/lib
    ARCHIVE DESTINATION ${demise-ncurses_SOURCE_DIR}/lib/static)
