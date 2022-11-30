//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_CONFIG_HPP
#define BOOST_JSON_DETAIL_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <cstdint>
#include <type_traits>
#include <utility>

// detect 32/64 bit
#if UINTPTR_MAX == UINT64_MAX
# define BOOST_JSON_ARCH 64
#elif UINTPTR_MAX == UINT32_MAX
# define BOOST_JSON_ARCH 32
#else
# error Unknown or unsupported architecture, please open an issue
#endif

// VFALCO Copied from Boost.Config
//        This is a derivative work.
#ifndef BOOST_JSON_NODISCARD
# ifdef __has_cpp_attribute
// clang-6 accepts [[nodiscard]] with -std=c++14, but warns about it -pedantic
#  if __has_cpp_attribute(nodiscard) && !(defined(__clang__) && (__cplusplus < 201703L))
#   define BOOST_JSON_NODISCARD [[nodiscard]]
#  else
#   define BOOST_JSON_NODISCARD
#  endif
# else
#  define BOOST_JSON_NODISCARD
# endif
#endif

#ifndef BOOST_JSON_REQUIRE_CONST_INIT
# define BOOST_JSON_REQUIRE_CONST_INIT
# if __cpp_constinit >= 201907L
#  undef BOOST_JSON_REQUIRE_CONST_INIT
#  define BOOST_JSON_REQUIRE_CONST_INIT constinit
# elif defined(__clang__) && defined(__has_cpp_attribute)
#  if __has_cpp_attribute(clang::require_constant_initialization)
#   undef BOOST_JSON_REQUIRE_CONST_INIT
#   define BOOST_JSON_REQUIRE_CONST_INIT [[clang::require_constant_initialization]]
#  endif
# endif
#endif

#ifndef BOOST_JSON_NO_DESTROY
# if defined(__clang__) && defined(__has_cpp_attribute)
#  if __has_cpp_attribute(clang::no_destroy)
#   define BOOST_JSON_NO_DESTROY [[clang::no_destroy]]
#  endif
# endif
#endif

// BOOST_NORETURN ---------------------------------------------//
// Macro to use before a function declaration/definition to designate
// the function as not returning normally (i.e. with a return statement
// or by leaving the function scope, if the function return type is void).
#if !defined(BOOST_NORETURN)
#  if defined(_MSC_VER)
#    define BOOST_NORETURN __declspec(noreturn)
#  elif defined(__GNUC__)
#    define BOOST_NORETURN __attribute__ ((__noreturn__))
#  elif defined(__has_attribute) && defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x5130)
#    if __has_attribute(noreturn)
#      define BOOST_NORETURN [[noreturn]]
#    endif
#  elif defined(__has_cpp_attribute)
#    if __has_cpp_attribute(noreturn)
#      define BOOST_NORETURN [[noreturn]]
#    endif
#  endif
#endif

#ifndef BOOST_ASSERT
#define BOOST_ASSERT assert
#endif

#ifndef BOOST_STATIC_ASSERT
#define BOOST_STATIC_ASSERT( ... ) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif

#ifndef BOOST_FALLTHROUGH
#define BOOST_FALLTHROUGH [[fallthrough]]
#endif

#ifndef BOOST_FORCEINLINE
# ifdef _MSC_VER
#  define BOOST_FORCEINLINE __forceinline
# elif defined(__GNUC__) || defined(__clang__)
#  define BOOST_FORCEINLINE inline __attribute__((always_inline))
# else
#  define BOOST_FORCEINLINE inline
# endif
#endif

#ifndef BOOST_NOINLINE
# ifdef _MSC_VER
#  define BOOST_NOINLINE __declspec(noinline)
# elif defined(__GNUC__) || defined(__clang__)
#  define BOOST_NOINLINE __attribute__((noinline))
# else
#  define BOOST_NOINLINE
# endif
#endif

#ifndef BOOST_THROW_EXCEPTION
# ifndef BOOST_NO_EXCEPTIONS
#  define BOOST_THROW_EXCEPTION(x) throw(x)
# else
#  define BOOST_THROW_EXCEPTION(x) do{}while(0)
# endif
#endif

#if ! defined(BOOST_JSON_NO_SSE2) && \
    ! defined(BOOST_JSON_USE_SSE2)
# if (defined(_M_IX86) && _M_IX86_FP == 2) || \
      defined(_M_X64) || defined(__SSE2__)
#  define BOOST_JSON_USE_SSE2
# endif
#endif

#ifndef BOOST_SYMBOL_VISIBLE
#define BOOST_SYMBOL_VISIBLE
#endif

#if ! defined(BOOST_JSON_DOCS)
# define BOOST_JSON_NS_BEGIN \
    namespace boost { \
    namespace json {
# define BOOST_JSON_NS_END } }
#endif

#if defined(BOOST_JSON_DOCS)
# define BOOST_JSON_DECL
#else
# if (defined(BOOST_JSON_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_JSON_STATIC_LINK)
#  if defined(BOOST_JSON_SOURCE)
#   define BOOST_JSON_DECL        BOOST_SYMBOL_EXPORT
#   define BOOST_JSON_CLASS_DECL  BOOST_SYMBOL_EXPORT
#   define BOOST_JSON_BUILD_DLL
#  else
#   define BOOST_JSON_DECL        BOOST_SYMBOL_IMPORT
#   define BOOST_JSON_CLASS_DECL  BOOST_SYMBOL_IMPORT
#  endif
# endif // shared lib
# ifndef  BOOST_JSON_DECL
#  define BOOST_JSON_DECL
# endif
# if !defined(BOOST_JSON_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_JSON_NO_LIB)
#  define BOOST_LIB_NAME boost_json
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_JSON_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
# endif
#endif

#ifndef BOOST_JSON_DECL
#define BOOST_JSON_DECL
#endif
#ifndef BOOST_JSON_CLASS_DECL
#define BOOST_JSON_CLASS_DECL
#endif

#ifndef BOOST_JSON_LIKELY
# if defined(__GNUC__) || defined(__clang__)
#  define BOOST_JSON_LIKELY(x) __builtin_expect(!!(x), 1)
# else
#  define BOOST_JSON_LIKELY(x) x
# endif
#endif

#ifndef BOOST_JSON_UNLIKELY
# if defined(__GNUC__) || defined(__clang__)
#  define BOOST_JSON_UNLIKELY(x) __builtin_expect(!!(x), 0)
# else
#  define BOOST_JSON_UNLIKELY(x) x
# endif
#endif

#ifndef BOOST_JSON_UNREACHABLE
# define BOOST_JSON_UNREACHABLE() static_cast<void>(0)
# ifdef _MSC_VER
#  undef BOOST_JSON_UNREACHABLE
#  define BOOST_JSON_UNREACHABLE() __assume(0)
# elif defined(__has_builtin)
#  if __has_builtin(__builtin_unreachable)
#   undef BOOST_JSON_UNREACHABLE
#   define BOOST_JSON_UNREACHABLE() __builtin_unreachable()
#  endif
# endif
#endif

#ifndef BOOST_JSON_ASSUME
# define BOOST_JSON_ASSUME(x) (!!(x) ? void() : BOOST_JSON_UNREACHABLE())
# ifdef _MSC_VER
#  undef BOOST_JSON_ASSUME
#  define BOOST_JSON_ASSUME(x) __assume(!!(x))
# elif defined(__has_builtin)
#  if __has_builtin(__builtin_assume)
#   undef BOOST_JSON_ASSUME
#   define BOOST_JSON_ASSUME(x) __builtin_assume(!!(x))
#  endif
# endif
#endif

// older versions of msvc and clang don't always
// constant initialize when they are supposed to
#ifndef BOOST_JSON_WEAK_CONSTINIT
# if defined(_MSC_VER) && ! defined(__clang__) && _MSC_VER < 1920
#  define BOOST_JSON_WEAK_CONSTINIT
# elif defined(__clang__) && __clang_major__ < 4
#  define BOOST_JSON_WEAK_CONSTINIT
# endif
#endif

// These macros are private, for tests, do not change
// them or else previously built libraries won't match.
#ifndef  BOOST_JSON_MAX_STRING_SIZE
# define BOOST_JSON_NO_MAX_STRING_SIZE
# define BOOST_JSON_MAX_STRING_SIZE  0x7ffffffe
#endif
#ifndef  BOOST_JSON_MAX_STRUCTURED_SIZE
# define BOOST_JSON_NO_MAX_STRUCTURED_SIZE
# define BOOST_JSON_MAX_STRUCTURED_SIZE  0x7ffffffe
#endif
#ifndef  BOOST_JSON_STACK_BUFFER_SIZE
# define BOOST_JSON_NO_STACK_BUFFER_SIZE
# if defined(__i386__) || defined(__x86_64__) || \
     defined(_M_IX86)  || defined(_M_X64)
#  define BOOST_JSON_STACK_BUFFER_SIZE 4096
# else
// If we are not on Intel, then assume we are on
// embedded and use a smaller stack size. If this
// is not suitable, the user can define the macro
// themselves when building the library or including
// src.hpp.
#  define BOOST_JSON_STACK_BUFFER_SIZE 256
# endif
#endif

BOOST_JSON_NS_BEGIN
namespace detail {

template<class...>
struct make_void
{
    using type =void;
};

template<class... Ts>
using void_t = typename
    make_void<Ts...>::type;

template<class T>
using remove_cvref = typename
    std::remove_cv<typename
        std::remove_reference<T>::type>::type;

template<class T, class U>
T exchange(T& t, U u) noexcept
{
    T v = std::move(t);
    t = std::move(u);
    return v;
}

/*  This is a derivative work, original copyright:

    Copyright Eric Niebler 2013-present

    Use, modification and distribution is subject to the
    Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)

    Project home: https://github.com/ericniebler/range-v3
*/
template<typename T>
struct static_const
{
    static constexpr T value {};
};
template<typename T>
constexpr T static_const<T>::value;

#define BOOST_JSON_INLINE_VARIABLE(name, type) \
    namespace { constexpr auto& name = \
        ::boost::json::detail::static_const<type>::value; \
    } struct _unused_ ## name ## _semicolon_bait_

} // detail
BOOST_JSON_NS_END

#endif

/* config.hpp
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
*/