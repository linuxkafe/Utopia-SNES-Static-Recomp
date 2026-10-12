# Use non-system dependency files on GCC/Clang. The inherited large generated
# dispatcher otherwise spends most of a clean build enumerating irrelevant
# system-header dependencies.
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_DEPFILE_FLAGS_C "-MMD -MT <DEP_TARGET> -MF <DEP_FILE>")
endif()

# Source files will be added incrementally as the project develops.
set(UTOPIA_STATIC_RECOMP_SOURCES
    src/utopia_static_recomp.c
    src/ut_v11_runtime.c
    src/ut_v11_support.c
    src/ut_machine.c
    src/ut_v11_scheduler.c
    src/ut_v11_bus.c
    src/ut_v11_cpu.c
    src/ut_v11_smp.c
    src/ut_audio_transport.c
    src/ut_v28_video.c
    src/ut_static_apu.c
    generated/ut_audio_epoch_manifest.c
    generated/ut_audio_scpu_access_manifest.c
    generated/ut_v11_bootstrap_dispatch.c
    generated/ut_v11_cpu_dispatch_index.c
    generated/ut_v23_static_dispatch.c
    static-audio/utopia-project-dsp/utopia_dsp.c
    static-audio/snes9x-bapu-aot/ut_static_apu.cpp
)

# Generated sources — populated when generate target is run.
set(UTOPIA_GENERATED_SOURCES
    generated/ut_v11_bootstrap_dispatch.c
    generated/ut_v11_cpu_dispatch_index.c
    generated/ut_v23_static_dispatch.c
)

# Helper header for static dispatch
set(UTOPIA_GENERATED_HEADERS
    generated/ut_static_helpers.h
)

file(GLOB UTOPIA_V11_SHARD_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/generated/v11-shards/*.c")

file(GLOB UTOPIA_V34_SHARD_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/generated/v34-shards/*.c")

file(GLOB UTOPIA_V35_SHARD_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/generated/v35-shards/*.c")

file(GLOB UTOPIA_V36_SHARD_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/generated/*.c")

set(UTOPIA_STATIC_RECOMP_SOURCES
    ${UTOPIA_STATIC_RECOMP_SOURCES}
    ${UTOPIA_V11_SHARD_SOURCES}
    ${UTOPIA_V34_SHARD_SOURCES}
    ${UTOPIA_V35_SHARD_SOURCES}
    ${UTOPIA_V36_SHARD_SOURCES}
)

add_library(utopia-static-recomp STATIC ${UTOPIA_STATIC_RECOMP_SOURCES})

target_include_directories(utopia-static-recomp
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/internal/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/generated"
        "${CMAKE_CURRENT_SOURCE_DIR}/static-audio/snes9x-bapu-aot"
        "${CMAKE_CURRENT_SOURCE_DIR}/static-audio/utopia-project-dsp/include"
)

if(MSVC)
    target_compile_options(utopia-static-recomp PRIVATE /W4)
    target_compile_definitions(utopia-static-recomp PRIVATE _CRT_SECURE_NO_WARNINGS)
    set_source_files_properties(
        generated/ut_v11_bootstrap_dispatch.c
        generated/ut_v11_cpu_dispatch_index.c
        generated/ut_v23_static_dispatch.c
        PROPERTIES COMPILE_OPTIONS "/W0"
    )
else()
    set_source_files_properties(
        generated/ut_v11_bootstrap_dispatch.c
        generated/ut_v11_cpu_dispatch_index.c
        generated/ut_v23_static_dispatch.c
        ${UTOPIA_V11_SHARD_SOURCES}
        ${UTOPIA_V34_SHARD_SOURCES}
        ${UTOPIA_V35_SHARD_SOURCES}
        ${UTOPIA_V36_SHARD_SOURCES}
        PROPERTIES COMPILE_OPTIONS "-w"
    )
endif()

if(BUILD_TESTING)
    add_executable(utopia-static-audio-purity
        tests/test_audio_purity.c)
    target_link_libraries(utopia-static-audio-purity PRIVATE utopia-static-recomp)
    if(MSVC)
        target_compile_options(utopia-static-audio-purity PRIVATE /W4 /WX)
    else()
        target_compile_options(utopia-static-audio-purity PRIVATE
            -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME utopia-static-audio-purity COMMAND utopia-static-audio-purity)

    set(UTOPIA_TEST_ROM "" CACHE FILEPATH
        "Optional exact Utopia USA ROM used only by local integration tests")
    # Auto-detect the locally-extracted ROM so integration tests actually run
    # when the (gitignored) ROM is present in this checkout.
    if(NOT UTOPIA_TEST_ROM AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../rom/extracted/Utopia - The Creation of a Nation (USA).sfc")
        set(UTOPIA_TEST_ROM "${CMAKE_CURRENT_SOURCE_DIR}/../rom/extracted/Utopia - The Creation of a Nation (USA).sfc")
    endif()

    add_subdirectory(tests)
endif()

target_compile_definitions(utopia-static-recomp PRIVATE UT_SMP_AOT)

set_source_files_properties(
    static-audio/snes9x-bapu-aot/smp/smp.cpp
    static-audio/snes9x-bapu-aot/dsp/sdsp.cpp
    static-audio/snes9x-bapu-aot/ut_static_apu.cpp
    PROPERTIES COMPILE_DEFINITIONS "UT_STATIC_SDSP_PRIMITIVES"
)

set_source_files_properties(
    static-audio/snes9x-bapu-aot/smp/smp.cpp
    static-audio/snes9x-bapu-aot/dsp/sdsp.cpp
    static-audio/snes9x-bapu-aot/ut_static_apu.cpp
    PROPERTIES COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/W0>$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-w>"
)

set_target_properties(utopia-static-recomp PROPERTIES
    OUTPUT_NAME "utopia-static-recomp")

# Generated dispatcher scale makes global warning analysis prohibitively expensive.
# Handwritten frontends and tools retain their own warning flags.
if(MSVC)
    set_source_files_properties(
        generated/ut_v11_cpu_dispatch_index.c
        ${UTOPIA_V11_SHARD_SOURCES}
        PROPERTIES COMPILE_OPTIONS "/W0;/O1"
    )
else()
    set_source_files_properties(
        generated/ut_v11_cpu_dispatch_index.c
        ${UTOPIA_V11_SHARD_SOURCES}
        PROPERTIES COMPILE_OPTIONS "-w;-O1"
    )
endif()