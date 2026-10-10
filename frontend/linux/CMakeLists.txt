cmake_minimum_required(VERSION 3.20)
project(utopia-linux-frontend C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

add_executable(utopia-linux
    main.c)

target_include_directories(utopia-linux PRIVATE
    "${CMAKE_SOURCE_DIR}/static-recomp/include"
    ${SDL2_INCLUDE_DIRS})

target_link_libraries(utopia-linux PRIVATE
    utopia-static-recomp
    ${SDL2_LIBRARIES})

target_compile_options(utopia-linux PRIVATE
    -Wall -Wextra -Wpedantic -Werror)

install(TARGETS utopia-linux RUNTIME DESTINATION bin)