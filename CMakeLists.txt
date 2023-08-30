cmake_minimum_required(VERSION 3.6.2)
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-function -Werror")

project(atl)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
  IF (NOT CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    message("Enabling LeakSanitizer")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fno-omit-frame-pointer -fsanitize=leak")
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -g -fno-omit-frame-pointer -fsanitize=leak")
  ENDIF (NOT CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
ENDIF (CMAKE_BUILD_TYPE MATCHES Debug)

# Code Coverage Configuration
option(CODE_COVERAGE "Enable coverage reporting" OFF)
IF (CODE_COVERAGE)
  message("Enabling Code Coverage")
  add_library(coverage_config INTERFACE)

  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g --coverage")
  set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -O0 -g --coverage")
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
ENDIF (CODE_COVERAGE)

# Don't Install Google Test if its already installed.
IF(NOT GTEST_INSTALLED MATCHES TRUE)
  include(GoogleTest)
  
  find_package(Threads REQUIRED)
  
  # Enable ExternalProject CMake module
  include(ExternalProject)
  
  # Download and install GoogleTest
  ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
  )
  
  # Get GTest source and binary directories from CMake project
  ExternalProject_Get_Property(gtest source_dir binary_dir)
  
  # Create a libgtest target to be used as a dependency by test programs
  add_library(libgtest IMPORTED STATIC GLOBAL)
  add_dependencies(libgtest gtest)
  
  # Set libgtest properties
  set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
  )
  
  # Create a libgmock target to be used as a dependency by test programs
  add_library(libgmock IMPORTED STATIC GLOBAL)
  add_dependencies(libgmock gtest)
  
  # Set libgmock properties
  set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
  )
ENDIF(NOT GTEST_INSTALLED MATCHES TRUE)

enable_testing()
add_subdirectory(test)

install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/include
  DESTINATION include
)
