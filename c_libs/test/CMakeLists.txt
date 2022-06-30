# ================================================================================
# ================================================================================
# - File:    CMakeLists.txt
# - Purpose: Primary CMake file for C++ build system
#
# Source Metadata
# - Author:  Jillian Epstein 
# - Date:    June 29, 2022
# - Version: 1.0
# - Copyright: Copyright 2022, Jillian Epstein Inc.
# ================================================================================
# ================================================================================
# Set minimum cmake version
cmake_minimum_required(VERSION 3.22.2)

enable_testing()

add_executable(
  unit_tests
  test.cpp
)
target_link_libraries(
  unit_tests
  gtest_main
  include
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
# ================================================================================
# ================================================================================
# eof
