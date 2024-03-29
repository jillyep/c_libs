# ================================================================================
# ================================================================================
# - File:    CMakeLists.txt
# - Purpose: Primary CMake file for C build system
#
# Source Metadata
# - Author:  Jillian Epstein 
# - Date:    June 29, 2022
# - Version: 1.0
# - Copyright: Copyright 2022, Jillian Epstein Inc.
# ================================================================================
# ================================================================================
# Set generic terms

# CMake version
cmake_minimum_required(VERSION 3.22.1)
project(c_libs)

# Set the compiler, for some reason this does not work with clang++ or g++
set(CMAKE_CXX_COMPILER "/usr/bin/c++")
set(CMAKE_CC_COMPILER "usr/bin/gcc")
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# --------------------------------------------------------------------------------
# Set executable terms

# Specify directory where the executable is stored
# set(CMAKE_CURRENT_BINARY_DIR "bin")

# Add subdirectories
add_subdirectory(include)

# Create name for executable
add_executable(${PROJECT_NAME} main.c)

# Add target libraries if necessary
target_link_libraries(${PROJECT_NAME} PUBLIC include)
# --------------------------------------------------------------------------------
# Set test terms

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(test)
# ================================================================================
# ================================================================================
# eof
