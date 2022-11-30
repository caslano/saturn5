/*!
@file
Defines macros to perform different kinds of assertions.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ASSERT_HPP
#define BOOST_HANA_ASSERT_HPP

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/preprocessor.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/value.hpp>

#include <cstdio>
#include <cstdlib>


#if defined(BOOST_HANA_DOXYGEN_INVOKED)
    //! @ingroup group-assertions
    //! Expands to a runtime assertion.
    //!
    //! Given a condition known at runtime, this macro expands to a runtime
    //! assertion similar to the `assert` macro. The provided condition must
    //! be explicitly convertible to a `bool`, and it must not be a model of
    //! the `Constant` concept. If the condition is a `Constant`, a static
    //! assertion will be triggered, asking you to use the
    //! `BOOST_HANA_CONSTANT_ASSERT` macro instead.
    //!
    //! @note
    //! This macro may only be used at function scope.
#   define BOOST_HANA_RUNTIME_ASSERT(condition) unspecified

    //! @ingroup group-assertions
    //! Equivalent to `BOOST_HANA_RUNTIME_ASSERT`, but allows providing a
    //! custom failure message.
    //!
    //! @warning
    //! Conditions that contain multiple comma-separated elements should be
    //! parenthesized.
#   define BOOST_HANA_RUNTIME_ASSERT_MSG(condition, message) unspecified

    //! @ingroup group-assertions
    //! Compile-time assertion for `Constant`s.
    //!
    //! Given a condition known at compile-time in the form of a `Constant`,
    //! this macro expands to a compile-time assertion similar to a `static_assert`.
    //! The provided condition must be a model of the `Constant` concept, in
    //! which case its value is retrieved using `hana::value` and then converted
    //! to a `bool`. If the condition is not a `Constant`, a static assertion
    //! will be triggered, asking you to use the `BOOST_HANA_RUNTIME_ASSERT`
    //! macro instead.
    //!
    //! This macro may be used at global/namespace scope and function scope
    //! only; it may not be used at class scope. Note that the condition may
    //! never be evaluated at runtime. Hence, any side effect may not take
    //! place (but you shouldn't rely on side effects inside assertions anyway).
#   define BOOST_HANA_CONSTANT_ASSERT(condition) unspecified

    //! @ingroup group-assertions
    //! Equivalent to `BOOST_HANA_CONSTANT_ASSERT`, but allows providing a
    //! custom failure message.
    //!
    //! @warning
    //! Conditions that contain multiple comma-separated elements should be
    //! parenthesized.
#   define BOOST_HANA_CONSTANT_ASSERT_MSG(condition, message) unspecified

    //! @ingroup group-assertions
    //! Expands to the strongest form of assertion possible for the given
    //! condition.
    //!
    //! Given a condition, `BOOST_HANA_ASSERT` expands either to a compile-time
    //! or to a runtime assertion, depending on whether the value of the
    //! condition is known at compile-time or at runtime. Compile-time
    //! assertions are always preferred over runtime assertions. If the
    //! condition is a model of the `Constant` concept, its value (retrievable
    //! with `hana::value`) is assumed to be explicitly convertible to `bool`,
    //! and a compile-time assertion is performed on it. Otherwise, the
    //! condition itself is assumed to be explicitly convertible to `bool`,
    //! and a runtime assertion is performed on it.
    //!
    //! If the assertion can be carried out at compile-time, the condition
    //! is not guaranteed to be evaluated at runtime at all (but it may).
    //! Hence, in general, you shouldn't rely on side effects that take place
    //! inside an assertion.
    //!
    //! @note
    //! This macro may only be used at function scope.
#   define BOOST_HANA_ASSERT(condition) unspecified

    //! @ingroup group-assertions
    //! Equivalent to `BOOST_HANA_ASSERT`, but allows providing a custom
    //! failure message.
    //!
    //! @warning
    //! Conditions that contain multiple comma-separated elements should be
    //! parenthesized.
#   define BOOST_HANA_ASSERT_MSG(condition, message) unspecified

    //! @ingroup group-assertions
    //! Expands to a static assertion or a runtime assertion, depending on
    //! whether `constexpr` lambdas are supported.
    //!
    //! This macro is used to assert on a condition that would be a constant
    //! expression if constexpr lambdas were supported. Right now, constexpr
    //! lambdas are not supported, and this is always a runtime assertion.
    //! Specifically, this is equivalent to `BOOST_HANA_RUNTIME_ASSERT`.
#   define BOOST_HANA_CONSTEXPR_ASSERT(condition) unspecified

    //! @ingroup group-assertions
    //! Equivalent to `BOOST_HANA_CONSTEXPR_ASSERT`, but allows providing a
    //! custom failure message.
#   define BOOST_HANA_CONSTEXPR_ASSERT_MSG(condition, message) unspecified

#elif defined(BOOST_HANA_CONFIG_DISABLE_ASSERTIONS)

#   define BOOST_HANA_CONSTANT_ASSERT(...)                      /* nothing */
#   define BOOST_HANA_CONSTANT_ASSERT_MSG(condition, message)   /* nothing */

#   define BOOST_HANA_RUNTIME_ASSERT(...)                       /* nothing */
#   define BOOST_HANA_RUNTIME_ASSERT_MSG(condition, message)    /* nothing */

#   define BOOST_HANA_ASSERT(...)                               /* nothing */
#   define BOOST_HANA_ASSERT_MSG(condition, message)            /* nothing */

#   define BOOST_HANA_CONSTEXPR_ASSERT(...)                     /* nothing */
#   define BOOST_HANA_CONSTEXPR_ASSERT_MSG(condition, message)  /* nothing */

#else

//////////////////////////////////////////////////////////////////////////////
// BOOST_HANA_RUNTIME_ASSERT and BOOST_HANA_RUNTIME_ASSERT_MSG
//////////////////////////////////////////////////////////////////////////////
#   define BOOST_HANA_RUNTIME_ASSERT_MSG(condition, message)                \
        BOOST_HANA_RUNTIME_CHECK_MSG(condition, message)                    \
/**/

#   define BOOST_HANA_RUNTIME_ASSERT(...)                                   \
        BOOST_HANA_RUNTIME_CHECK(__VA_ARGS__)                               \
/**/

//////////////////////////////////////////////////////////////////////////////
// BOOST_HANA_CONSTANT_ASSERT and BOOST_HANA_CONSTANT_ASSERT_MSG
//////////////////////////////////////////////////////////////////////////////
#   define BOOST_HANA_CONSTANT_ASSERT_MSG(condition, message)               \
    BOOST_HANA_CONSTANT_CHECK_MSG(condition, message)                       \
/**/

#   define BOOST_HANA_CONSTANT_ASSERT(...)                                  \
        BOOST_HANA_CONSTANT_CHECK(__VA_ARGS__)                              \
/**/

//////////////////////////////////////////////////////////////////////////////
// BOOST_HANA_ASSERT and BOOST_HANA_ASSERT_MSG
//////////////////////////////////////////////////////////////////////////////
#   define BOOST_HANA_ASSERT_MSG(condition, message)                        \
        BOOST_HANA_CHECK_MSG(condition, message)                            \
/**/

#   define BOOST_HANA_ASSERT(...)                                           \
        BOOST_HANA_CHECK(__VA_ARGS__)                                       \
/**/

//////////////////////////////////////////////////////////////////////////////
// BOOST_HANA_CONSTEXPR_ASSERT and BOOST_HANA_CONSTEXPR_ASSERT_MSG
//////////////////////////////////////////////////////////////////////////////
#   define BOOST_HANA_CONSTEXPR_ASSERT_MSG(condition, message)              \
        BOOST_HANA_CONSTEXPR_CHECK_MSG(condition, message)                  \
/**/

#   define BOOST_HANA_CONSTEXPR_ASSERT(...)                                 \
        BOOST_HANA_CONSTEXPR_CHECK(__VA_ARGS__)                             \
/**/

#endif

//////////////////////////////////////////////////////////////////////////////
// BOOST_HANA_RUNTIME_CHECK and BOOST_HANA_RUNTIME_CHECK_MSG
//////////////////////////////////////////////////////////////////////////////

//! @ingroup group-assertions
//! Equivalent to `BOOST_HANA_RUNTIME_ASSERT_MSG`, but not influenced by the
//! `BOOST_HANA_CONFIG_DISABLE_ASSERTIONS` config macro. For internal use only.
#   define BOOST_HANA_RUNTIME_CHECK_MSG(condition, message)                 \
    do {                                                                    \
        auto __hana_tmp = condition;                                        \
        static_assert(!::boost::hana::Constant<decltype(__hana_tmp)>::value,\
        "the expression (" # condition ") yields a Constant; "              \
        "use BOOST_HANA_CONSTANT_ASSERT instead");                          \
                                                                            \
        if (!static_cast<bool>(__hana_tmp)) {                               \
            ::std::fprintf(stderr, "Assertion failed: "                     \
                "(%s), function %s, file %s, line %i.\n",                   \
                message, __func__, __FILE__, __LINE__);                     \
            ::std::abort();                                                 \
        }                                                                   \
    } while (false);                                                        \
    static_assert(true, "force trailing semicolon")                         \
/**/

//! @ingroup group-assertions
//! Equivalent to `BOOST_HANA_RUNTIME_ASSERT`, but not influenced by the
//! `BOOST_HANA_CONFIG_DISABLE_ASSERTIONS` config macro. For internal use only.
#   define BOOST_HANA_RUNTIME_CHECK(...)                                    \
        BOOST_HANA_RUNTIME_CHECK_MSG(                                       \
            (__VA_ARGS__),                                                  \
            BOOST_HANA_PP_STRINGIZE(__VA_ARGS__)                            \
        )                                                                   \
/**/

//////////////////////////////////////////////////////////////////////////////
// BOOST_HANA_CONSTANT_CHECK and BOOST_HANA_CONSTANT_CHECK_MSG
//////////////////////////////////////////////////////////////////////////////

//! @ingroup group-assertions
//! Equivalent to `BOOST_HANA_CONSTANT_ASSERT_MSG`, but not influenced by the
//! `BOOST_HANA_CONFIG_DISABLE_ASSERTIONS` config macro. For internal use only.
#   define BOOST_HANA_CONSTANT_CHECK_MSG(condition, message)                \
        auto BOOST_HANA_PP_CONCAT(__hana_tmp_, __LINE__) = condition;       \
        static_assert(::boost::hana::Constant<                              \
            decltype(BOOST_HANA_PP_CONCAT(__hana_tmp_, __LINE__))           \
        >::value,                                                           \
        "the expression " # condition " does not yield a Constant; "        \
        "use BOOST_HANA_RUNTIME_ASSERT instead");                           \
        static_assert(::boost::hana::value<                                 \
            decltype(BOOST_HANA_PP_CONCAT(__hana_tmp_, __LINE__))           \
        >(), message);                                                      \
        static_assert(true, "force trailing semicolon")                     \
/**/

//! @ingroup group-assertions
//! Equivalent to `BOOST_HANA_CONSTANT_ASSERT`, but not influenced by the
//! `BOOST_HANA_CONFIG_DISABLE_ASSERTIONS` config macro. For internal use only.
#   define BOOST_HANA_CONSTANT_CHECK(...)                                   \
        BOOST_HANA_CONSTANT_CHECK_MSG(                                      \
            (__VA_ARGS__),                                                  \
            BOOST_HANA_PP_STRINGIZE(__VA_ARGS__)                            \
        )                                                                   \
/**/

//////////////////////////////////////////////////////////////////////////////
// BOOST_HANA_CHECK and BOOST_HANA_CHECK_MSG
//////////////////////////////////////////////////////////////////////////////

//! @ingroup group-assertions
//! Equivalent to `BOOST_HANA_ASSERT_MSG`, but not influenced by the
//! `BOOST_HANA_CONFIG_DISABLE_ASSERTIONS` config macro. For internal use only.
#   define BOOST_HANA_CHECK_MSG(condition, message)                         \
    do {                                                                    \
        auto __hana_tmp = condition;                                        \
        ::boost::hana::if_(::boost::hana::bool_c<                           \
            ::boost::hana::Constant<decltype(__hana_tmp)>::value>,          \
            [](auto expr) {                                                 \
                static_assert(::boost::hana::value<decltype(expr)>(),       \
                message);                                                   \
            },                                                              \
            [](auto expr) {                                                 \
                if (!static_cast<bool>(expr)) {                             \
                    ::std::fprintf(stderr, "Assertion failed: "             \
                        "(%s), function %s, file %s, line %i.\n",           \
                        message, __func__, __FILE__, __LINE__);             \
                    ::std::abort();                                         \
                }                                                           \
            }                                                               \
        )(__hana_tmp);                                                      \
    } while (false);                                                        \
    static_assert(true, "force trailing semicolon")                         \
/**/

//! @ingroup group-assertions
//! Equivalent to `BOOST_HANA__ASSERT`, but not influenced by the
//! `BOOST_HANA_CONFIG_DISABLE_ASSERTIONS` config macro. For internal use only.
#   define BOOST_HANA_CHECK(...)                                            \
        BOOST_HANA_CHECK_MSG(                                               \
            (__VA_ARGS__),                                                  \
            BOOST_HANA_PP_STRINGIZE(__VA_ARGS__)                            \
        )                                                                   \
/**/

//////////////////////////////////////////////////////////////////////////////
// BOOST_HANA_CONSTEXPR_CHECK and BOOST_HANA_CONSTEXPR_CHECK_MSG
//////////////////////////////////////////////////////////////////////////////

#if defined(BOOST_HANA_DOXYGEN_INVOKED)
    //! @ingroup group-assertions
    //! Equivalent to `BOOST_HANA_CONSTEXPR_ASSERT_MSG`, but not influenced by
    //! the `BOOST_HANA_CONFIG_DISABLE_ASSERTIONS` config macro.
    //! For internal use only.
#   define BOOST_HANA_CONSTEXPR_CHECK_MSG(condition, message) implementation-defined

    //! @ingroup group-assertions
    //! Equivalent to `BOOST_HANA_CONSTEXPR_ASSERT`, but not influenced by the
    //! `BOOST_HANA_CONFIG_DISABLE_ASSERTIONS` config macro.
    //! For internal use only.
#   define BOOST_HANA_CONSTEXPR_CHECK(...) implementation-defined

#elif defined(BOOST_HANA_CONFIG_HAS_CONSTEXPR_LAMBDA)

#   define BOOST_HANA_CONSTEXPR_CHECK_MSG(condition, message)               \
        static_assert(condition, message)                                   \
/**/

#   define BOOST_HANA_CONSTEXPR_CHECK(...)                                  \
        static_assert((__VA_ARGS__), BOOST_HANA_PP_STRINGIZE(__VA_ARGS__))  \
/**/

#else

#   define BOOST_HANA_CONSTEXPR_CHECK_MSG(condition, message)               \
        BOOST_HANA_RUNTIME_CHECK_MSG(condition, message)                    \
/**/

#   define BOOST_HANA_CONSTEXPR_CHECK(...)                                  \
        BOOST_HANA_CONSTEXPR_CHECK_MSG(                                     \
            (__VA_ARGS__),                                                  \
            BOOST_HANA_PP_STRINGIZE(__VA_ARGS__)                            \
        )                                                                   \
/**/

#endif

#endif // !BOOST_HANA_ASSERT_HPP

/* assert.hpp
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
*/