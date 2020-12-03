cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
  SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)


project(parser)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

# hunter_add_package(GTest)
add_subdirectory(third_party/gtest)
# find_package(GTest CONFIG REQUIRED)
hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

add_library(parser_printer STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/parser_printer.cpp)
target_include_directories(parser_printer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(parser_printer PUBLIC nlohmann_json::nlohmann_json)

add_library(print_any STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/print_any.cpp)
target_include_directories(print_any PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(parser_printer PUBLIC print_any)

add_executable(tests
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
)
add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)


target_link_libraries(tests gtest_main parser_printer)


target_link_libraries(main PUBLIC parser_printer)



enable_testing()
add_test(NAME unit_tests COMMAND tests)

if(BUILD_COVERAGE)
  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)

  add_coverage(parser_printer)
  add_coverage(tests)
  add_coverage(main)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif()
