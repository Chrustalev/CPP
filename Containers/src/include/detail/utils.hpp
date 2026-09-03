#pragma once

#include <iostream>

// см. /CPP2_s21_containers/materials/instructions_for_testing_rus.md
// см. https://en.cppreference.com/w/cpp/iterator/iterator.html

#ifndef NDEBUG
#define _CUSTOM_ASSERT(expr, msg)                                          \
  do {                                                                     \
    if (!(expr)) {                                                         \
      std::cerr << "Assertion failed: " << #expr << ", " << msg << "\n";   \
      std::cerr << "File: " << __FILE__ << ", line: " << __LINE__ << "\n"; \
      std::abort();                                                        \
    }                                                                      \
  } while (false)
#else
#define _CUSTOM_ASSERT(expr, msg) ((void)0)
#endif

#define DEFAULTED_FIVE(ClassName)                       \
  ClassName(const ClassName&) = default;                \
  ClassName(ClassName&&) noexcept = default;            \
  ClassName& operator=(const ClassName&) = default;     \
  ClassName& operator=(ClassName&&) noexcept = default; \
  ~ClassName() = default
