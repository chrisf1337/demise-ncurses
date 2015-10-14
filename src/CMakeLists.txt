set(SRCS editor_view.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")

message(STATUS "DEMISE-CORE_LIB_DIR ${DEMISE-CORE_LIB_DIR}")

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
    ${DEMISE-CORE_LIB_DIR}
    ${demise-ncurses_SOURCE_DIR}/demise-core/lib/static
    NO_DEFAULT_PATH)

find_package(Boost 1.55.0)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
else ()
    message(FATAL_ERROR "Unable to find Boost")
endif ()

message(STATUS "demise-core lib path ${DEMISE-CORE}")

include_directories(${NCURSES_INCLUDE_DIR} ${demise-ncurses_SOURCE_DIR}/demise-core/src)

add_definitions(-std=c++14)

add_executable(demise demise.cpp ${SRCS})
target_link_libraries(demise ${NCURSES_LIBRARY} ${DEMISE-CORE} ${Boost_LIBRARIES})

install(TARGETS demise
    RUNTIME DESTINATION ${demise-ncurses_SOURCE_DIR}/bin
    LIBRARY DESTINATION ${demise-ncurses_SOURCE_DIR}/lib
    ARCHIVE DESTINATION ${demise-ncurses_SOURCE_DIR}/lib/static)
