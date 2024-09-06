cmake_minimum_required(VERSION 3.10)

# Project name
project(TronGame)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Find the ncurses library
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Add the executable
add_executable(tron_game
    main.c
    init.c
    ai.c
    display.c
    game.c
    color.c
)

# Link the ncurses library
target_link_libraries(tron_game ${CURSES_LIBRARIES})

# Custom clean target
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -f tron_game
    COMMAND ${CMAKE_COMMAND} -E rm -f CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E rm -rf CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E rm -f Makefile
    COMMAND ${CMAKE_COMMAND} -E rm -f cmake_install.cmake
)
