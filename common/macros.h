#ifndef INCLUDE_MACROS_H_
#define INCLUDE_MACROS_H_

#include <iostream>

#include "debug.h"

// clang-format off
#define NO_COPY_CTOR(TypeName) TypeName(const TypeName&) = delete;

#define NO_COPY_OPERATOR(TypeName) void operator=(const TypeName&) = delete

#define NO_COPY_SEMANTIC(TypeName) \
  NO_COPY_CTOR(TypeName)           \
  NO_COPY_OPERATOR(TypeName)

#define NO_MOVE_CTOR(TypeName) TypeName(TypeName&&) = delete;

#define NO_MOVE_OPERATOR(TypeName) TypeName& operator=(TypeName&&) = delete

#define NO_MOVE_SEMANTIC(TypeName) \
  NO_MOVE_CTOR(TypeName)           \
  NO_MOVE_OPERATOR(TypeName)

#define DEFAULT_MOVE_CTOR(TypeName) TypeName(TypeName&&) = default;

#define DEFAULT_MOVE_OPERATOR(TypeName) TypeName& operator=(TypeName&&) = default

#define DEFAULT_MOVE_SEMANTIC(TypeName) \
  DEFAULT_MOVE_CTOR(TypeName)           \
  DEFAULT_MOVE_OPERATOR(TypeName)

#define DEFAULT_COPY_CTOR(TypeName) TypeName(const TypeName&) = default;

#define DEFAULT_COPY_OPERATOR(TypeName) TypeName& operator=(const TypeName&) = default

#define DEFAULT_COPY_SEMANTIC(TypeName) \
  DEFAULT_COPY_CTOR(TypeName)           \
  DEFAULT_COPY_OPERATOR(TypeName)

#if !defined(NDEBUG)

#define LIKELY(exp) (__builtin_expect((exp) != 0, true))
#define UNLIKELY(exp) (__builtin_expect((exp) != 0, false))

#define ASSERT_FAIL(expr) mipt_vm::AssertionFail(expr, __FILE__, __LINE__, __FUNCTION__)

#define ASSERT(cond)       \
  if (UNLIKELY(!(cond))) { \
    ASSERT_FAIL(#cond);    \
  }

#define ASSERT_PRINT(cond, message)                    \
  do {                                                 \
    if (auto cond_val = cond; UNLIKELY(!(cond_val))) { \
      std::cerr << message << std::endl;               \
      ASSERT_FAIL(#cond);                              \
    }                                                  \
  } while (0)

#define UNREACHABLE()                                       \
  do {                                                      \
    ASSERT_PRINT(false, "This line should be unreachable"); \
    __builtin_unreachable();                                \
  } while (0)

#define LOG(message)                 \
  std::cout << message << std::endl;
#else  // NDEBUG
#define LOG(message)
#define ASSERT(cond) static_cast<void>(0)
#define ASSERT_PRINT(cond, message) static_cast<void>(0)
#define UNREACHABLE __builtin_unreachable
#endif  // !NDEBUG
// clang-format on

#endif  // INCLUDE_MACROS_H_
