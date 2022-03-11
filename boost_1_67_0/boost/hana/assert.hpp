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