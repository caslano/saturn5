/* Proposed SG14 status_code
(C) 2018 - 2020 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
File Created: Feb 2018


Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License in the accompanying file
Licence.txt or at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Distributed under the Boost Software License, Version 1.0.
(See accompanying file Licence.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_CONFIG_HPP
#define BOOST_OUTCOME_SYSTEM_ERROR2_CONFIG_HPP

// < 0.1 each
#include <cassert>
#include <cstddef>  // for size_t
#include <cstdlib>  // for free

// 0.22
#include <type_traits>

// 0.29
#include <atomic>

// 0.28 (0.15 of which is exception_ptr)
#include <exception>  // for std::exception
// <new> includes <exception>, <exception> includes <new>
#include <new>

// 0.01
#include <initializer_list>

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14
#if defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE) || __cplusplus >= 201400 || _MSC_VER >= 1910 /* VS2017 */
//! Defined to be `constexpr` when on C++ 14 or better compilers. Usually automatic, can be overriden.
#define BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 constexpr
#else
#define BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14
#endif
#endif

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN
#if defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE) || (_HAS_CXX17 && _MSC_VER >= 1911 /* VS2017.3 */)
#define BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN [[noreturn]]
#endif
#endif
#if !defined(BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN)
#ifdef __has_cpp_attribute
#if __has_cpp_attribute(noreturn)
#define BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN [[noreturn]]
#endif
#endif
#endif
#if !defined(BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN)
#if defined(_MSC_VER)
#define BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN __declspec(noreturn)
#elif defined(__GNUC__)
#define BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN __attribute__((__noreturn__))
#else
#define BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN
#endif
#endif
// GCCs before 7 don't grok [[noreturn]] virtual functions, and warn annoyingly
#if defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 7
#undef BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN
#define BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN
#endif

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_NODISCARD
#if defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE) || (_HAS_CXX17 && _MSC_VER >= 1911 /* VS2017.3 */)
#define BOOST_OUTCOME_SYSTEM_ERROR2_NODISCARD [[nodiscard]]
#endif
#endif
#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_NODISCARD
#ifdef __has_cpp_attribute
#if __has_cpp_attribute(nodiscard)
#define BOOST_OUTCOME_SYSTEM_ERROR2_NODISCARD [[nodiscard]]
#endif
#elif defined(__clang__)
#define BOOST_OUTCOME_SYSTEM_ERROR2_NODISCARD __attribute__((warn_unused_result))
#elif defined(_MSC_VER)
// _Must_inspect_result_ expands into this
#define BOOST_OUTCOME_SYSTEM_ERROR2_NODISCARD                                                                                                                                                                                                                                                                                                \
  __declspec("SAL_name"                                                                                                                                                                                                                                                                                                        \
             "("                                                                                                                                                                                                                                                                                                               \
             "\"_Must_inspect_result_\""                                                                                                                                                                                                                                                                                       \
             ","                                                                                                                                                                                                                                                                                                               \
             "\"\""                                                                                                                                                                                                                                                                                                            \
             ","                                                                                                                                                                                                                                                                                                               \
             "\"2\""                                                                                                                                                                                                                                                                                                           \
             ")") __declspec("SAL_begin") __declspec("SAL_post") __declspec("SAL_mustInspect") __declspec("SAL_post") __declspec("SAL_checkReturn") __declspec("SAL_end")
#endif
#endif
#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_NODISCARD
#define BOOST_OUTCOME_SYSTEM_ERROR2_NODISCARD
#endif

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_TRIVIAL_ABI
#if defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE) || (__clang_major__ >= 7 && !defined(__APPLE__))
//! Defined to be `[[clang::trivial_abi]]` when on a new enough clang compiler. Usually automatic, can be overriden.
#define BOOST_OUTCOME_SYSTEM_ERROR2_TRIVIAL_ABI [[clang::trivial_abi]]
#else
#define BOOST_OUTCOME_SYSTEM_ERROR2_TRIVIAL_ABI
#endif
#endif

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE
//! The system_error2 namespace name.
#define BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE system_error2
//! Begins the system_error2 namespace.
#define BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN                                                                                                                                                                                                                                                                                          \
  namespace system_error2                                                                                                                                                                                                                                                                                                      \
  {
//! Ends the system_error2 namespace.
#define BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END }
#endif

//! Namespace for the library
BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN

//! Namespace for user specialised traits
namespace traits
{
  /*! Specialise to true if you guarantee that a type is move bitcopying (i.e.
  its move constructor equals copying bits from old to new, old is left in a
  default constructed state, and calling the destructor on a default constructed
  instance is trivial). All trivially copyable types are move bitcopying by
  definition, and that is the unspecialised implementation.
  */
  template <class T> struct is_move_bitcopying
  {
    static constexpr bool value = std::is_trivially_copyable<T>::value;
  };
}  // namespace traits

namespace detail
{
  inline BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 size_t cstrlen(const char *str)
  {
    const char *end = nullptr;
    for(end = str; *end != 0; ++end)  // NOLINT
      ;
    return end - str;
  }

  /* A partially compliant implementation of C++20's std::bit_cast function contributed
  by Jesse Towner. TODO FIXME Replace with C++ 20 bit_cast when available.

  Our bit_cast is only guaranteed to be constexpr when both the input and output
  arguments are either integrals or enums. However, this covers most use cases
  since the vast majority of status_codes have an underlying type that is either
  an integral or enum. We still attempt a constexpr union-based type pun for non-array
  input types, which some compilers accept. For array inputs, we fall back to
  non-constexpr memmove.
  */

  template <class T> using is_integral_or_enum = std::integral_constant<bool, std::is_integral<T>::value || std::is_enum<T>::value>;

  template <class To, class From> using is_static_castable = std::integral_constant<bool, is_integral_or_enum<To>::value && is_integral_or_enum<From>::value>;

  template <class To, class From> using is_union_castable = std::integral_constant<bool, !is_static_castable<To, From>::value && !std::is_array<To>::value && !std::is_array<From>::value>;

  template <class To, class From> using is_bit_castable = std::integral_constant<bool, sizeof(To) == sizeof(From) && traits::is_move_bitcopying<To>::value && traits::is_move_bitcopying<From>::value>;

  template <class To, class From> union bit_cast_union {
    From source;
    To target;
  };

  template <class To, class From,
            typename std::enable_if<                 //
            is_bit_castable<To, From>::value         //
            && is_static_castable<To, From>::value   //
            && !is_union_castable<To, From>::value,  //
            bool>::type = true>                      //
  constexpr To bit_cast(const From &from) noexcept
  {
    return static_cast<To>(from);
  }

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
  template <class To, class From,
            typename std::enable_if<                 //
            is_bit_castable<To, From>::value         //
            && !is_static_castable<To, From>::value  //
            && is_union_castable<To, From>::value,   //
            bool>::type = true>                      //
  constexpr To bit_cast(const From &from) noexcept
  {
    return bit_cast_union<To, From>{from}.target;
  }
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

  template <class To, class From,
            typename std::enable_if<                 //
            is_bit_castable<To, From>::value         //
            && !is_static_castable<To, From>::value  //
            && !is_union_castable<To, From>::value,  //
            bool>::type = true>                      //
  To bit_cast(const From &from) noexcept
  {
    bit_cast_union<To, From> ret;
    memmove(&ret.source, &from, sizeof(ret.source));
    return ret.target;
  }

  /* erasure_cast performs a bit_cast with additional rules to handle types
  of differing sizes. For integral & enum types, it may perform a narrowing
  or widing conversion with static_cast if necessary, before doing the final
  conversion with bit_cast. When casting to or from non-integral, non-enum
  types it may insert the value into another object with extra padding bytes
  to satisfy bit_cast's preconditions that both types have the same size. */

  template <class To, class From> using is_erasure_castable = std::integral_constant<bool, traits::is_move_bitcopying<To>::value && traits::is_move_bitcopying<From>::value>;

  template <class T, bool = std::is_enum<T>::value> struct identity_or_underlying_type
  {
    using type = T;
  };
  template <class T> struct identity_or_underlying_type<T, true>
  {
    using type = typename std::underlying_type<T>::type;
  };

  template <class OfSize, class OfSign>
  using erasure_integer_type = typename std::conditional<std::is_signed<typename identity_or_underlying_type<OfSign>::type>::value, typename std::make_signed<typename identity_or_underlying_type<OfSize>::type>::type, typename std::make_unsigned<typename identity_or_underlying_type<OfSize>::type>::type>::type;

  template <class ErasedType, std::size_t N> struct padded_erasure_object
  {
    static_assert(traits::is_move_bitcopying<ErasedType>::value, "ErasedType must be TriviallyCopyable or MoveBitcopying");
    static_assert(alignof(ErasedType) <= sizeof(ErasedType), "ErasedType must not be over-aligned");
    ErasedType value;
    char padding[N];
    constexpr explicit padded_erasure_object(const ErasedType &v) noexcept
        : value(v)
        , padding{}
    {
    }
  };

  template <class To, class From, typename std::enable_if<is_erasure_castable<To, From>::value && (sizeof(To) == sizeof(From)), bool>::type = true> constexpr To erasure_cast(const From &from) noexcept { return bit_cast<To>(from); }

  template <class To, class From, typename std::enable_if<is_erasure_castable<To, From>::value && is_static_castable<To, From>::value && (sizeof(To) < sizeof(From)), bool>::type = true> constexpr To erasure_cast(const From &from) noexcept { return static_cast<To>(bit_cast<erasure_integer_type<From, To>>(from)); }

  template <class To, class From, typename std::enable_if<is_erasure_castable<To, From>::value && is_static_castable<To, From>::value && (sizeof(To) > sizeof(From)), bool>::type = true> constexpr To erasure_cast(const From &from) noexcept { return bit_cast<To>(static_cast<erasure_integer_type<To, From>>(from)); }

  template <class To, class From, typename std::enable_if<is_erasure_castable<To, From>::value && !is_static_castable<To, From>::value && (sizeof(To) < sizeof(From)), bool>::type = true> constexpr To erasure_cast(const From &from) noexcept
  {
    return bit_cast<padded_erasure_object<To, sizeof(From) - sizeof(To)>>(from).value;
  }

  template <class To, class From, typename std::enable_if<is_erasure_castable<To, From>::value && !is_static_castable<To, From>::value && (sizeof(To) > sizeof(From)), bool>::type = true> constexpr To erasure_cast(const From &from) noexcept
  {
    return bit_cast<To>(padded_erasure_object<From, sizeof(To) - sizeof(From)>{from});
  }
}  // namespace detail
BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_FATAL
#ifdef BOOST_OUTCOME_SYSTEM_ERROR2_NOT_POSIX
#error If BOOST_OUTCOME_SYSTEM_ERROR2_NOT_POSIX is defined, you must define your own BOOST_OUTCOME_SYSTEM_ERROR2_FATAL implementation!
#endif
#include <cstdlib>  // for abort
#ifdef __APPLE__
#include <unistd.h>  // for write
#endif

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN
namespace detail
{
  namespace avoid_stdio_include
  {
#if !defined(__APPLE__) && !defined(_MSC_VER)
    extern "C" ptrdiff_t write(int, const void *, size_t);
#elif defined(_MSC_VER)
    extern ptrdiff_t write(int, const void *, size_t);
#if defined(_WIN64)
#pragma comment(linker, "/alternatename:?write@avoid_stdio_include@detail@system_error2@@YA_JHPEBX_K@Z=write")
#else
#pragma comment(linker, "/alternatename:?write@avoid_stdio_include@detail@system_error2@@YAHHPBXI@Z=_write")
#endif
#endif
  }  // namespace avoid_stdio_include
  inline void do_fatal_exit(const char *msg)
  {
    using namespace avoid_stdio_include;
    write(2 /*stderr*/, msg, cstrlen(msg));
    write(2 /*stderr*/, "\n", 1);
    abort();
  }
}  // namespace detail
BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END
//! Prints msg to stderr, and calls `std::terminate()`. Can be overriden via predefinition.
#define BOOST_OUTCOME_SYSTEM_ERROR2_FATAL(msg) ::BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE::detail::do_fatal_exit(msg)
#endif

#endif

/* config.hpp
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
*/