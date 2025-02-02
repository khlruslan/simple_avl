cmake_minimum_required(VERSION 3.14)

project(simple_avl)

if (MSVC)
  # warning level 4
  add_compile_options(/W4)
else()
  # additional warnings
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add sanitizer flags for C++ compiler for "Debug" configuration
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include_directories( ${CMAKE_SOURCE_DIR}/inc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(tests)

