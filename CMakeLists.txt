cmake_minimum_required(VERSION 3.20)
project(6502_Emulator LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(6502_Emulator
        main.cpp
        src/bus.cpp
        src/cpu.cpp
        include/types.h
)
target_include_directories(6502_Emulator PRIVATE include)
target_compile_features(6502_Emulator PRIVATE cxx_std_20)
target_link_libraries(6502_Emulator PRIVATE  GTest::gtest_main)