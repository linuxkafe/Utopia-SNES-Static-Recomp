cmake_minimum_required(VERSION 3.20)
project(utopia-static-recomp-tests C)

set(UTOPIA_TEST_ROM "" CACHE FILEPATH
    "Optional exact Utopia USA ROM used only by local integration tests")

# WRAM write contract test
add_executable(utopia-wram-write
    tests/test_wram_write.c)
target_link_libraries(utopia-wram-write PRIVATE utopia-static-recomp)
target_include_directories(utopia-wram-write PRIVATE
    "${CMAKE_SOURCE_DIR}/static-recomp/include")
target_compile_options(utopia-wram-write PRIVATE
    -Wall -Wextra -Wpedantic -Werror)
add_test(NAME utopia-wram-write
    COMMAND utopia-wram-write "${UTOPIA_TEST_ROM}")

# Headless smoke test
add_executable(utopia-headless-smoke
    ../frontend/linux/headless-test.c)
target_link_libraries(utopia-headless-smoke PRIVATE utopia-static-recomp)
target_compile_options(utopia-headless-smoke PRIVATE
    -Wall -Wextra -Wpedantic -Werror)
if(UTOPIA_TEST_ROM)
    add_test(NAME utopia-headless-smoke
        COMMAND utopia-headless-smoke "${UTOPIA_TEST_ROM}" "300")
endif()