cmake_minimum_required(VERSION 3.20)
project(utopia-static-recomp-tests C)

# WRAM write contract test
add_executable(utopia-wram-write
    ../tests/test_wram_write.c)
target_link_libraries(utopia-wram-write PRIVATE utopia-static-recomp)
target_include_directories(utopia-wram-write PRIVATE
    "${CMAKE_SOURCE_DIR}/static-recomp/include")
target_compile_options(utopia-wram-write PRIVATE
    -Wall -Wextra -Wpedantic -Werror)
add_test(NAME utopia-wram-write
    COMMAND utopia-wram-write "${UTOPIA_TEST_ROM}")

# Headless smoke test (without ROM - tests basic API)
add_executable(utopia-headless-smoke
    ../../frontend/linux/headless-test.c)
target_link_libraries(utopia-headless-smoke PRIVATE utopia-static-recomp)
target_include_directories(utopia-headless-smoke PRIVATE
    "${CMAKE_SOURCE_DIR}/static-recomp/include")
target_compile_options(utopia-headless-smoke PRIVATE
    -Wall -Wextra -Wpedantic -Werror)

# Full headless integration test (with ROM)
add_executable(utopia-headless-integration
    ../../frontend/linux/headless-test.c)
target_link_libraries(utopia-headless-integration PRIVATE utopia-static-recomp)
target_include_directories(utopia-headless-integration PRIVATE
    "${CMAKE_SOURCE_DIR}/static-recomp/include")
target_compile_options(utopia-headless-integration PRIVATE
    -Wall -Wextra -Wpedantic -Werror)
add_test(NAME utopia-headless-integration
    COMMAND utopia-headless-integration "${UTOPIA_TEST_ROM}" "300")