cmake_minimum_required(VERSION 3.12)
project(s21_containers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги компиляции (строгие и педантичные)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} \
    -Wall \
    -Wextra \
    -Werror \
    -Wpedantic")

# Header-only библиотека
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/detail>)

option(BUILD_TEST "Build tests" OFF)

if(BUILD_TEST)
  find_package(GTest REQUIRED)

  set(TEST_SOURCES
      test/main_test.cpp
      test/src/test_array.cpp
      test/src/test_list.cpp
      test/src/test_map.cpp
      test/src/test_multiset.cpp
      test/src/test_queue.cpp
      test/src/test_rb_tree.cpp
      test/src/test_set.cpp
      test/src/test_stack.cpp
      test/src/test_vector.cpp)

  add_executable(
    ${PROJECT_NAME}_tests
    # main
    test/main_test.cpp
    # tests
    ${TEST_SOURCES})
  target_link_libraries(${PROJECT_NAME}_tests
                        PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
  add_test(NAME containers_tests COMMAND tests)

  include(GoogleTest)
  gtest_discover_tests(${PROJECT_NAME}_tests)
endif()

# Пример программы
add_executable(simple_example main.cpp)
target_link_libraries(simple_example PRIVATE ${PROJECT_NAME})
